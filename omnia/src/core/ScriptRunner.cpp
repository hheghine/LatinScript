#include "ScriptRunner.hpp"

using namespace ls;

/********************
*	GLOBAL VARIABLE
*********************/
std::unordered_map<std::string, Functio *>	g_functions;
std::stack<svector>							g_function_args;
std::unordered_map<std::string, Ordinata *>	g_arrays;


ScriptRunner::ScriptRunner(const std::string& filename)
	: ls::LatinScript()
{
	try {
		letsGo(filename);
	} catch (const std::exception& e) {
		std::cout << RED << "[ ";
		displayTime();
		std::cout << " |    ✘   ]" << "\terror: " \
		<< e.what() << CRST << std::endl;
	}
}

ScriptRunner::~ScriptRunner()
{
	// for (auto it = tmp_arr.begin(); it != tmp_arr.end(); ++it)
	// {
		// vars[*it]->value = nullptr;
		// objects.erase(vars[*it]);
		// delete vars[*it];
	// }
	for (auto it = objects.begin(); it != objects.end(); ++it)
		delete *it;
	objects.clear();

	for (auto it = g_functions.begin(); it != g_functions.end(); ++it)
		delete it->second;
	g_functions.clear();

	for (auto it = g_arrays.begin(); it != g_arrays.end(); ++it)
		delete it->second;
	g_arrays.clear();
}

void	ScriptRunner::letsGo(const std::string& filename)
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
		_line = line;
		std::stringstream ss(line);
		std::string first_word;

		ss >> first_word;

		if (first_word == "dum")
			handleLoop(file, line);
		else
			mainLoop(file, line);
	}
}

void	ScriptRunner::mainLoop(std::ifstream& file, const std::string& line)
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

	if (g_arrays.find(vec[0]) != g_arrays.end())
		handleArray(vec, it);

	if(utils::isType(vec[0]))
	{
		if (vec[0] == "ordinata")
		{
			Ordinata* arr = new Ordinata(line);
			g_arrays[arr->_name] = arr;
			return ;
		}

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
		parseFunction(file, line);
	else
		throw std::invalid_argument("bad start statement: " + vec[0]);
	handleStatement(vec, it);
	if (!_output)
		displayOutput(false, "");

	for (auto it = tmp_arr.begin(); it != tmp_arr.end(); ++it)
	{
		vars[*it] = nullptr;
		delete vars[*it];
	}
}

Object*	ScriptRunner::createVar(const std::string& type)
{
	if (type == "numerus")
		return new Numerus();
	if (type == "filum")
		return new Filum();
	if (type == "duplus")
		return new Duplus();
	return nullptr;
}

void	ScriptRunner::handleArray(svector& vec, iterator& it)
{
	std::string name;
	int			idx;

	if (vec.size() < 4 || vec.at(1) != "<" || vec.at(3) != ">")
		throw std::invalid_argument("wrong statement");

	if (vars.find(vec.at(2)) != vars.end() && vars[vec.at(2)]->type == "numerus")
		idx = *((int *)vars[vec.at(2)]->value);
	else
		idx = utils::toInt(vec.at(2));

	name = *it + "+" + std::to_string(idx);

	vars[name] = g_arrays[*it]->getValue(idx);
	tmp_arr.push_back(name);

	*it = name;

	vec.erase(it + 1);
	vec.erase(it + 1);
	vec.erase(it + 1);
}

void	ScriptRunner::handleOutput(const svector& vec, const std::string& line)
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
			else if (!var.empty() && g_arrays.find(var) != g_arrays.end())
				output += g_arrays[var]->__string();
			else
				throw std::invalid_argument("invalid input or nothing to output: " + var);
		}
		it1 = it2;
	}
	displayOutput(true, output);
	_output = true;
}

void	ScriptRunner::parseFunction(std::ifstream& file, const std::string& declaration)
{
	Functio* func = new Functio(declaration);

	svector		body;
	std::string	line;

	while(std::getline(file, line))
	{
		if (line[0] != '\t')
			break ;
		body.push_back(line);
	}

	func->setBody(body);

	if (g_functions.find(func->_name) != g_functions.end())
	{
		delete func;
		throw std::invalid_argument("function redefinition");
	}
	g_functions[func->_name] = func;
}

void	ScriptRunner::handleAssignment(const svector& vec, const_iterator lhs, const_iterator& it)
{
	if (it == vec.end())
		throw std::invalid_argument("invalid assignment operation");

	std::string toChange = _chainedOperations ? "tmp" : *lhs;

	if (g_functions.find(*it) != g_functions.end())
	{
		if (g_functions[*it]->_return_type != vars[toChange]->type)
			throw std::invalid_argument("type conflict: " + g_functions[*it]->_return_type \
			+ " vs " +  vars[toChange]->type);
		handleFunction(vec, lhs, it);
	}
	/* another (valid?) object => set the pointer to point that object
	else if (vars.find(*it) != vars.end() && \
	vars[toChange]->type == vars[*it]->type) */
	else if (vars.find(*it) != vars.end())
	{
		if (_chainedOperations)
			vars[toChange]->setValue(vars[*it]);
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
	{
		if (vars[toChange]->type == "filum")
			vars[toChange]->setValue(extractString(vec, it));
		else
			vars[toChange]->setValue(*it);
	}
}

void	ScriptRunner::handleFunction(const svector& vec, const_iterator lhs, const_iterator& it)
{
	auto name = it;

	it ++;
	if (it == vec.end() || *it != "<")
		throw std::invalid_argument("wrong syntax: opening bracket '<' not found");

	bool closed = false;

	/* handle void function later*/

	svector args;

	it ++;

	for (; it != vec.end(); ++it)
	{
		if (*it == ">")
		{
			closed = true;
			break ;
		}
		std::string temp = *it;
		if (temp.find(',') != std::string::npos)
			temp.erase(temp.end() - 1);
		else if (*(it + 1) != ">")
			throw std::invalid_argument("wrong syntax: use ',' to separate arguments");
		args.push_back(temp);
	}
	if (!closed || it + 1 != vec.end())
		throw std::invalid_argument("wrong syntax: bracket not closed");

	g_function_args.push(args);
	g_functions[*name]->exec();

	vars[*lhs]->setValue(g_functions[*name]->_return->value);
	g_functions[*name]->_return->value = nullptr;
}

void	ScriptRunner::handleOperator(const svector& vec, const_iterator lhs, const_iterator& it)
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
				&& vars.find(*(iter - 1)) != vars.end() \
				&& g_functions.find(*(iter + 1)) == g_functions.end())
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
