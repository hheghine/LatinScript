#include "LatinScript.hpp"

using namespace ls;

static bool _output;
static bool _chainedOperations;
static bool _isAssignment;

LatinScript::LatinScript(const std::string& filename)
{
	try {
		letsGo(filename);
	} catch (const std::exception& e) {
		std::cout << ls::MAIN << "[ " << ls::RED << "✘" \
		<< ls::MAIN << " ]" << "\t\texception: " << e.what() \
		<< ls::CRST << std::endl;
	}
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
	std::string	buffer;

	while (std::getline(file, line))
	{
		_output = false;
		svector vec = splitLine(line);
		if (vec.empty())
			continue ;
		if (line[0] == '#')
			continue ;

		displayInput(vec);

		auto it = vec.begin();
		if(isType(vec[0]))
		{
			createVariable(vec);

			if (vec.begin() + 2 == vec.end())
			{
				displayOutput(false, "");
				continue ;
			}

			it += 2;

			if (vec[2] != "=")
				throw std::invalid_argument("wrong operation: " + vec[2]);
		}
		else if (vars.find(vec[0]) != vars.end())
			it += 1;
		else if (isCondition(vec[0]))
			std::cout << ls::GRY << "\t\tCONDITION!" << std::endl;
		else if (isLoop(vec[0]))
			std::cout << ls::GRY <<"\t\tLOOP!" << std::endl;
		else if (vec[0] == "scribere")
			handleOutput(vec, line);
		else
			throw std::invalid_argument("bad start statement: " + vec[0]);
		handleStatement(vec, it);
		if (!_output)
			displayOutput(false, "");
	}

}

void	LatinScript::createVariable(const std::vector<std::string>& vec)
{
	if (vec.size() < 2)
		throw std::invalid_argument("syntax error");
	if (!varNameCheck(vec[1]))
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
	if (isOperator(*it))
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
				break ;
			case operators::MULTIPLY :
				break ;
			case operators::DIVIDE :
				break ;
		}
	}
	/* assigning the final value to actual lhs */
	if (_chainedOperations)
	{
		vars[*final_lhs]->setValue(vars["tmp"]);
		delete vars["tmp"];
		vars.erase("tmp");
		_chainedOperations = false;
	}
}

void	LatinScript::handleAssignment(const svector& vec, const_iterator lhs, const_iterator& it)
{
	if (it == vec.end())
		throw std::invalid_argument("invalid assignment operation");

	std::string toChange = _chainedOperations ? "tmp" : *lhs;

	if (vars.find(*it) != vars.end() && \
		vars[toChange]->type == vars[*it]->type)
	{
		if (vars[toChange]->links == 1)
		{
			objects.erase(vars[toChange]);
			delete vars[toChange];
		}
		vars[toChange] = vars[*it];
		vars[*it]->links ++;
	}
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

void	LatinScript::handleOutput(const svector& vec, const std::string& line)
{
	if (vec.begin() + 1 == vec.end() || *(vec.begin() + 1) != "<<")
		throw std::invalid_argument("invalid input or nothing to output: " + *(line.begin() + 1));

	std::string output;
	std::string::const_iterator it1 = ls::search(line.begin(), line.end(), "<<");
	std::string::const_iterator it2;

	while (it1 != line.end())
	{
		it2 = ls::search(it1 + 1, line.end(), "<<");
		if (it2 == line.end() && it2 - 1 != line.end() && *(it2 - 1) == '<')
			throw std::invalid_argument("wrong syntax");

		if (ls::search(it1, it2, '*') != it2)
			output += extractString(it1, it2, '*');
		else
		{
			std::string var = extractString(it1, it2);
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

LatinScript::~LatinScript()
{
	for (auto it = objects.begin(); it != objects.end(); ++it)
		delete *it;
	objects.clear();
}