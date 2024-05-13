#include "ScriptRunner.hpp"

ScriptRunner::ScriptRunner(const std::string& filename)
	: ls::LatinScript()
{
	try {
		letsGo(filename);
	} catch (const std::exception& e) {
		std::cout << ls::RED << "[ ✘\t\t\t]" << "\terror: " \
		<< e.what() << ls::CRST << std::endl;
	}
}

ScriptRunner::~ScriptRunner()
{
	for (auto it = objects.begin(); it != objects.end(); ++it)
		delete *it;
	objects.clear();
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
		handleFunction(file, line);
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

void	ScriptRunner::handleFunction(std::ifstream& file, const std::string& declaration)
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