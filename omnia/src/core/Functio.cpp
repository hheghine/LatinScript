#include "Functio.hpp"

Functio::Functio(const std::string& declaration)
	: LatinScript()
	, _name("")
	, _return_type("")
	, _return (nullptr)
{
	try {
		letsGo(declaration);
	} catch (const std::exception& e) {
		std::cout << RED << "[ ✘\t\t\t]" << "\terror: " \
		<< e.what() << CRST << std::endl;
	}
}

Functio::~Functio()
{
	if (_return)
		delete _return;

	for (auto it = objects.begin(); it != objects.end(); ++it)
		delete *it;
	objects.clear();
}

void	Functio::letsGo(const std::string& declaration)
{
	svector decl_vec = utils::splitLine(declaration);

	if (!utils::varNameCheck(decl_vec.at(1)))
		throw std::invalid_argument("wrong function name: " + decl_vec.at(1));

	_name = decl_vec[1];

	if (decl_vec.at(2) != "<")
		throw std::invalid_argument("wrong function syntax");

	bool closed = false;


	auto it = decl_vec.begin() + 3;
	for (; it != decl_vec.end(); ++it)
	{
		if (*it == ">")
		{
			closed = true;
			break ;
		}
		if (!utils::isType(*it))
			throw std::invalid_argument("wrong function syntax");
		it ++;
		if (((*it).at((*it).size() - 1) != ',' && it + 1 != decl_vec.end() && *(it + 1) != ">"))
			throw std::invalid_argument("wrong function syntax");

		std::string var_name = *it;
		if (var_name[var_name.size() - 1] == ',')
			var_name.erase(var_name.end() - 1);
		vars[var_name] = createVar(*(it - 1));
		objects.insert(vars[var_name]);
	}

	if (!closed)
		throw std::invalid_argument("wrong function syntax: bracket not closed");

	it ++;

	if (it != decl_vec.end())
	{
		if (*it != ":")
			throw std::invalid_argument("wrong function syntax: invalid characters: " + *it);
		it ++;
		_return_type = *it;
		_return = createVar(_return_type);

		it ++;

		if (it != decl_vec.end())
			throw std::invalid_argument("wrong function syntax: " + *it);
	}
}

Object*	Functio::createVar(const std::string& type)
{
	if (type == "numerus")
		return new Numerus();
	throw std::invalid_argument("unknown return type: " + type);
}

void	Functio::setBody(const svector& body)
{
	for (auto it = body.begin(); it != body.end(); ++it)
		_body.push_back(*it);
}

void	Functio::main_loop()
{
	for (auto iter = _body.begin(); iter != _body.end(); ++iter)
	{
		std::string line = *iter;

		_output = false;
		if (_ignore && line[0] == '\t' && line[1] == '\t')
			return ;
		_ignore = false;
		svector vec = utils::splitLine(line);
		if (vec.empty())
			return ;
		if ((vec[0] == "<<" && __if) || \
			(vec[0] == "<<" && _is_elseif && __elseif) || \
			(vec[0] == "<<<" && (__if || __elseif)))
			_ignore = true;

		if (_ignore && ((line[0] == '\t' && line[1] == '\t') || utils::isCondition(vec[0])))
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
		// else if (utils::isLoop(vec[0]))
		// 	handleLoop(file, line);
		else if (vec[0] == "scribere")
			handleOutput(vec, line);
		else if (vec[0] =="redire")
		{
			handleReturn(vec);
			break ;
		}
		else
			throw std::invalid_argument("bad start statement: " + vec[0]);
		handleStatement(vec, it);
		if (!_output)
			displayOutput(false, "");
	}
}

void	Functio::handleReturn(const svector& vec)
{
	vars["_"] = createVar(_return->type);

	svector vec1;

	vec1.push_back("_");
	vec1.push_back("=");

	for (auto it = vec.begin() + 1; it != vec.end(); ++it)
		vec1.push_back(*it);

	const_iterator iter = vec1.begin() + 1;
	handleOperator(vec1, vec1.begin(), iter);

	_return->setValue(vars["_"]->value);
	vars["_"]->value = nullptr;
	delete vars["_"];
	vars.erase("_");
}


void	Functio::handleAssignment(const svector& vec, const_iterator lhs, const_iterator& it)
{
	if (it == vec.end())
		throw std::invalid_argument("invalid assignment operation");

	std::string toChange = _chainedOperations ? "tmp" : *lhs;

	if (g_functions.find(*it) != g_functions.end())
	{
		if (g_functions[*it]->_return_type != vars[toChange]->type)
			throw std::invalid_argument("blabla");
		g_functions[*it]->main_loop();
	}
	/* another (valid?) object => set the pointer to point that object */
	else if (vars.find(*it) != vars.end() && \
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
