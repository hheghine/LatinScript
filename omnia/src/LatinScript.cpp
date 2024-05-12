#include "LatinScript.hpp"

using namespace ls;

LatinScript::LatinScript(const std::string& filename)
	: _output(false)
	, _chainedOperations(false)
	, _isAssignment(false)
	, _is_if(false)
	, _is_elseif(false)
	, __if(false)
	, __elseif(false)
	, __else(false)
	, _ignore(false)
{
	try {
		letsGo(filename);
	} catch (const std::exception& e) {
		std::cout << ls::RED << "[ ✘\t\t\t]" << "\terror: " \
		<< e.what() << ls::CRST << std::endl;
	}
}

LatinScript::~LatinScript()
{
	for (auto it = objects.begin(); it != objects.end(); ++it)
		delete *it;
	objects.clear();
}

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

void	LatinScript::letsGo(const std::string& filename)
{
	/* file extension check */
	std::filesystem::path p(filename);
	if (p.extension() != ".ls")
		throw std::invalid_argument("wrong file format");

	/* file content check */
	std::ifstream file(filename);
	if (!file.good())
		throw std::invalid_argument("bad file");

	std::string	line;

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string first_word;

		ss >> first_word;

		if (first_word == "dum")
			handleLoop(file, line);
		else
			mainLoop(file, line);
	}
}

void	LatinScript::mainLoop(std::ifstream& file, const std::string& line)
{
	_output = false;
	if (_ignore && line[0] == '\t')
		return ;
	_ignore = false;
	svector vec = utils::splitLine(line);
	if (vec.empty())
		return ;
	if ((vec[0] == "<<" && __if) || \
		(vec[0] == "<<" && _is_elseif && __elseif) || \
		(vec[0] == "<<<" && (__if || __elseif)))
		_ignore = true;

	if (_ignore && (line[0] == '\t' || utils::isCondition(vec[0])))
		return ;
	if (line[0] == '#')
		return ;

	displayInput(vec);

	auto it = vec.begin();
	if(utils::isType(vec[0]))
	{
		createVariable(vec);

		if (vec.begin() + 2 == vec.end())
		{
			displayOutput(false, "");
			return ;
		}

		it += 2;

		if (vec[2] != "=")
			throw std::invalid_argument("wrong operation: " + vec[2]);
	}
	else if (vars.find(vec[0]) != vars.end())
		it += 1;
	else if (utils::isCondition(vec[0]))
	{
		handleCondition(vec);
		if (!conditionBlockTrue(vec[0]))
		{
			displayOutput(true, "false");
			_output = true;
			_ignore = true;
			return ;
		}
		else
		{
			displayOutput(true, "true");
			_output = true;
		}
	}
	else if (utils::isLoop(vec[0]))
		handleLoop(file, line);
	else if (vec[0] == "scribere")
		handleOutput(vec, line);
	else if (vec[0] == "functio")
		handleFunction(file, line);
	else
		throw std::invalid_argument("bad start statement: " + vec[0]);
	handleStatement(vec, it);
	if (!_output)
		displayOutput(false, "");
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
	// __if = true;
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

void	LatinScript::handleFunction(std::ifstream& file, const std::string& declaration)
{
	(void) file;

	// std::cout << declaration << std::endl;
	
	Functio* func = new Functio(declaration);

	std::cout << " func name: " << func->_name \
	<< " func ret-type: " << func->_return_type \
	<< " return ptr: " << (void *)func->_return << std::endl;

	for (auto it = func->vars.begin(); it != func->vars.end(); ++it)
	{
		std::cout << " name: " << it->first << " obj type: " << it->second->type << std::endl;
	} 

	delete func;

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
}

void	LatinScript::handleStatement(const svector& vec, const_iterator it)
{
	if (utils::isOperator(*it))
		handleOperator(vec, it - 1, it);
}

void	LatinScript::handleOperator(const svector& vec, const_iterator lhs, const_iterator& it)
{
	if (vars.find(*(it - 1)) == vars.end())
		throw std::invalid_argument("invalid assignment: " + *(it - 1));

	_chainedOperations = false;
	_isAssignment = false;
	const_iterator final_lhs;

	for (auto iter = it; iter != vec.end(); ++iter)
	{
		auto op = operator_map.find(*iter);
		if (op == operator_map.end())
			throw std::invalid_argument("unknown operator: " + *iter);

		switch(op->second)
		{
			case operators::ASSIGNMENT :
				_isAssignment = true;
				/* if there's a chain of operations, creating a temporary object to
				store the non-final value and then assigning the final value to actual lhs */
				if (iter + 1 != vec.end() && iter + 2 != vec.end()
				&& vars.find(*(iter - 1)) != vars.end())
				{
					Object* tmp = vars[*(iter - 1)]->clone();
					objects.insert(tmp);
					vars["tmp"] = tmp;
					final_lhs = lhs;
					_chainedOperations = true;
				}
				handleAssignment(vec, lhs, ++iter);
				break ;
			case operators::PLUS :
				handleAddition(vec, lhs, ++iter);
				break ;
			case operators::MINUS :
				handleSubstraction(vec, lhs, ++iter);
				break ;
			case operators::MULTIPLY :
				handleMultiplication(vec, lhs, ++iter);
				break ;
			case operators::DIVIDE :
				handleDivision(vec, lhs, ++iter);
				break ;
		}
	}
	/* assigning the final value to actual lhs */
	if (_chainedOperations)
	{
		vars[*final_lhs]->setValue(vars["tmp"]);
		objects.erase(vars["tmp"]);
		delete vars["tmp"];
		_chainedOperations = false;
	}
}

void	LatinScript::handleAssignment(const svector& vec, const_iterator lhs, const_iterator& it)
{
	if (it == vec.end())
		throw std::invalid_argument("invalid assignment operation");

	std::string toChange = _chainedOperations ? "tmp" : *lhs;

	/* another (valid?) object => set the pointer to point that object */
	if (vars.find(*it) != vars.end() && \
		vars[toChange]->type == vars[*it]->type)
	{
		if (_chainedOperations)
		{
			vars[toChange]->setValue(vars[*it]);
		}
		else
		{
			if (vars[toChange]->links == 1)
			{
				objects.erase(vars[toChange]);
				delete vars[toChange];
			}
			vars[toChange] = vars[*it];
			vars[*it]->links ++;
		}
	}
	/* literal value */
	else
		vars[toChange]->setValue(*it);
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
			vars[toChange]->addition(*it);
	}
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
