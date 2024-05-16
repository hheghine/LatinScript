#include "LatinScript.hpp"

using namespace ls;

/********************
*	GLOBAL VARIABLE
*********************/
std::unordered_map<std::string, Object *> ls::vars;

LatinScript::LatinScript()
	: _output(false)
	, _chainedOperations(false)
	, _isAssignment(false)
	, _is_if(false)
	, _is_elseif(false)
	, __if(false)
	, __elseif(false)
	, __else(false)
	, _ignore(false)
{}

void	LatinScript::handleOutput(const svector& vec, const std::string& line)
{
	if (vec.begin() + 1 == vec.end() || *(vec.begin() + 1) != "<<")
		throw std::invalid_argument("invalid input or nothing to output: " + *(line.begin() + 1));

	std::string output;
	std::string::const_iterator it1 = utils::search(line.begin(), line.end(), "<<");
	std::string::const_iterator it2;

	while (it1 != line.end())
	{
		it2 = utils::search(it1 + 1, line.end(), "<<");
		if (it2 == line.end() && it2 - 1 != line.end() && *(it2 - 1) == '<')
			throw std::invalid_argument("wrong syntax");

		if (utils::search(it1, it2, '*') != it2)
			output += utils::extractString(it1, it2, '*');
		else
		{
			std::string var = utils::extractString(it1, it2);
			if (!var.empty() && vars.find(var) != vars.end())
				output += vars[var]->__string();
			else
				throw std::invalid_argument("invalid input or nothing to output: " + var);
		}
		it1 = it2;
	}
	displayOutput(true, output);
	_output = true;
}

void	LatinScript::handleLoop(std::ifstream& file, const std::string& condition)
{
	svector condition_vec = utils::splitLine(condition);
	condition_vec.erase(condition_vec.begin());

	std::string line;
	svector vec;

	while (std::getline(file, line))
	{
		if (line[0] != '\t')
			break ;
		vec.push_back(line);
	}
	auto it = vec.begin();

	while (1)
	{
		handleCondition(condition_vec);
		if (!__if)
			break;
		mainLoop(file, *it);
		++it;
		if (it == vec.end())
			it = vec.begin();
		__if = false;
	}
}

void	LatinScript::createVariable(const std::vector<std::string>& vec)
{
	if (vec.size() < 2)
		throw std::invalid_argument("syntax error");
	if (!utils::varNameCheck(vec[1]))
		throw std::invalid_argument("invalid variable name: " + vec[1]);
	if (vars.find(vec[1]) != vars.end())
			throw std::invalid_argument("redefinition: " + vec[1]);
	if (vec[0] == "numerus")
	{
		vars[vec[1]] = new Numerus();
		objects.insert(vars[vec[1]]);
	}
	else if (vec[0] == "filum")
	{
		vars[vec[1]] = new Filum();
		objects.insert(vars[vec[1]]);
	}
	else if (vec[0] == "duplus")
	{
		vars[vec[1]] = new Duplus();
		objects.insert(vars[vec[1]]);
	}
}

void	LatinScript::handleStatement(const svector& vec, const_iterator it)
{
	if (utils::isOperator(*it))
		handleOperator(vec, it - 1, it);
}

void	LatinScript::handleAddition(const svector& vec, const_iterator lhs, const_iterator& it)
{
	if (it == vec.end())
		throw std::invalid_argument("wrong operation: " + *(it - 1));

	if (_isAssignment)
	{
		std::string toChange = _chainedOperations ? "tmp" : *lhs;

		if (vars.find(*it) != vars.end())
			vars[toChange]->addition(vars[*it]);
		else
		{
			if (vars[toChange]->type == "filum")
				vars[toChange]->addition(extractString(vec, it));
			else
				vars[toChange]->addition(*it);
		}
	}
}

std::string	LatinScript::extractString(const svector& vec, const_iterator& it)
{
	bool closed = false;

	for(; it != vec.end(); ++it)
	{
		if (*((*it).end() - 1) == '*')
		{
			closed = true;
			break ;
		}
	}

	if (!closed)
		throw std::invalid_argument("wrong syntax: bracket '*' not closed");

	std::string str(_line.begin(), _line.end());

	return utils::extractString(_line, str.begin(), str.end(), '*');
}

void	LatinScript::handleSubstraction(const svector& vec, const_iterator lhs, const_iterator& it)
{
	if (it == vec.end())
		throw std::invalid_argument("wrong operation: " + *(it - 1));

	if (_isAssignment)
	{
		std::string toChange = _chainedOperations ? "tmp" : *lhs;

		if (vars.find(*it) != vars.end())
			vars[toChange]->substraction(vars[*it]);
		else
			vars[toChange]->substraction(*it);
	}
}

void	LatinScript::handleMultiplication(const svector& vec, const_iterator lhs, const_iterator& it)
{
	if (it == vec.end())
		throw std::invalid_argument("wrong operation: " + *(it - 1));

	if (_isAssignment)
	{
		std::string toChange = _chainedOperations ? "tmp" : *lhs;

		if (vars.find(*it) != vars.end())
			vars[toChange]->multiplication(vars[*it]);
		else
			vars[toChange]->multiplication(*it);
	}
}

void	LatinScript::handleDivision(const svector& vec, const_iterator lhs, const_iterator& it)
{
	if (it == vec.end())
		throw std::invalid_argument("wrong operation: " + *(it - 1));

	if (_isAssignment)
	{
		std::string toChange = _chainedOperations ? "tmp" : *lhs;

		if (vars.find(*it) != vars.end())
			vars[toChange]->division(vars[*it]);
		else
			vars[toChange]->division(*it);
	}
}

void	LatinScript::handleCondition(const svector& vec)
{
	if (vec.at(0) == "<")
		_is_if = true;
	else if (vec.at(0) == "<<")
	{
		if (!_is_if)
			throw std::invalid_argument("<< > else if without if condition");
		_is_if = false;
		_is_elseif = true;
	}
	else if (vec.at(0) == "<<<")
	{
		if (!_is_if)
			throw std::invalid_argument("<<< > else without if condition");
		_is_if = false;
		_is_elseif = false;
		_is_else = true;
	}

	__if = false;
	__elseif = false;
	__else = true;

	if (((_is_if || _is_elseif) && vec.size() != 5 && !utils::isConditionOperator(vec.at(2))) || \
		*(vec.end() - 1) != ">")
		throw std::invalid_argument("wrong condition syntax");

	if (_is_if)
	{
		if (isConditionTrue(vec.at(2), vec.at(1), vec.at(3)))
		{
			__if = true;
			__elseif = false;
			__else = false;
		}
	}
	else if (_is_elseif && !__if)
	{
		if (isConditionTrue(vec.at(2), vec.at(1), vec.at(3)))
		{
			__elseif = true;
			__else = false;
		}
	}
	else if (__else)
	{
		__if = false;
		__elseif = false;
		__else = true;
	}
}

bool	LatinScript::isConditionTrue(const std::string& op, const std::string& lhs, const std::string& rhs)
{
	auto opr = condition_map.find(op);
	if (opr == condition_map.end())
		throw std::invalid_argument("wrong condition operator: " + op);

	switch(opr->second)
	{
		case conditions::EQUAL :
			return handleIsEqual(lhs, rhs);
		case conditions::GREATER :
			return handleIsGreater(lhs, rhs);
		case conditions::LESS :
			return handleIsLess(lhs, rhs);
		case conditions::GREATER_EQ :
			return handleIsGreaterOrEq(lhs, rhs);
		case conditions::LESS_EQ :
			return handleIsLessOrEq(lhs, rhs);
	}
	return false;
}

bool	LatinScript::conditionBlockTrue(const std::string& block)
{
	return ((block == "<" && __if) || \
			(block == "<<" && __elseif) || \
			(block == "<<<" && __else));
}

bool	LatinScript::handleIsEqual(const std::string& lhs, const std::string& rhs)
{
	if (vars.find(lhs) == vars.end())
		throw std::invalid_argument("wrong condition");

	if (vars.find(rhs) != vars.end())
		return vars[lhs]->isEqual(vars[rhs]);
	return vars[lhs]->isEqual(rhs);
}

bool	LatinScript::handleIsGreater(const std::string& lhs, const std::string& rhs)
{
	if (vars.find(lhs) == vars.end())
		throw std::invalid_argument("wrong condition");

	if (vars.find(rhs) != vars.end())
		return vars[lhs]->isGreater(vars[rhs]);
	return vars[lhs]->isGreater(rhs);
}

bool	LatinScript::handleIsLess(const std::string& lhs, const std::string& rhs)
{
	if (vars.find(lhs) == vars.end())
		throw std::invalid_argument("wrong condition");

	if (vars.find(rhs) != vars.end())
		return vars[lhs]->isLess(vars[rhs]);
	return vars[lhs]->isLess(rhs);
}

bool	LatinScript::handleIsGreaterOrEq(const std::string& lhs, const std::string& rhs)
{
	if (vars.find(lhs) == vars.end())
		throw std::invalid_argument("wrong condition");

	if (vars.find(rhs) != vars.end())
		return vars[lhs]->isGreaterOrEq(vars[rhs]);
	return vars[lhs]->isGreaterOrEq(rhs);
}

bool	LatinScript::handleIsLessOrEq(const std::string& lhs, const std::string& rhs)
{
	if (vars.find(lhs) == vars.end())
		throw std::invalid_argument("wrong condition");

	if (vars.find(rhs) != vars.end())
		return vars[lhs]->isGreaterOrEq(vars[rhs]);
	return vars[lhs]->isGreaterOrEq(rhs);
}
