#include "ScriptRunner.hpp"

using namespace ls;

std::unordered_map<std::string, Functio *> functions;

ScriptRunner::ScriptRunner(const std::string& filename)
	: ls::LatinScript()
{
	try {
		letsGo(filename);
	} catch (const std::exception& e) {
		std::cout << RED << "[ ✘\t\t\t]" << "\terror: " \
		<< e.what() << CRST << std::endl;
	}
}

ScriptRunner::~ScriptRunner()
{
	for (auto it = objects.begin(); it != objects.end(); ++it)
		delete *it;
	objects.clear();

	for (auto it = functions.begin(); it != functions.end(); ++it)
		delete it->second;
	functions.clear();
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
		parseFunction(file, line);
	else
		throw std::invalid_argument("bad start statement: " + vec[0]);
	handleStatement(vec, it);
	if (!_output)
		displayOutput(false, "");
}

void	ScriptRunner::createVariable(const std::vector<std::string>& vec)
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

	func->vars["a"]->setValue(new int(4));
	func->vars["b"]->setValue(new int(5));

	if (functions.find(func->_name) != functions.end())
	{
		delete func;
		throw std::invalid_argument("function redefinition");
	}
	functions[func->_name] = func;
}

void	ScriptRunner::handleAssignment(const svector& vec, const_iterator lhs, const_iterator& it)
{
	if (it == vec.end())
		throw std::invalid_argument("invalid assignment operation");

	std::string toChange = _chainedOperations ? "tmp" : *lhs;

	if (functions.find(*it) != functions.end())
	{
		if (functions[*it]->_return_type != vars[toChange]->type)
			throw std::invalid_argument("blabla");
		functions[*it]->main_loop();
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