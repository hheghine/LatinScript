#include "LatinScript.hpp"

using namespace ls;

static bool _output;

LatinScript::LatinScript(const std::string& filename)
{
	try {
		letsGo(filename);
	} catch (const std::exception& e) {
		std::cout << ls::MAIN << "[ " << ls::RED << "✘" \
		<< ls::MAIN << " ]" << "\t\texeption: " << e.what() \
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
			continue;

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
	if (std::isdigit(vec[1][0])) // ADD PROPER VARIABLE NAME CHECK
		throw std::invalid_argument("invalid variable name: " + vec[1]);
	if (vec[0] == "numerus")
	{
		if (vars.find(vec[1]) == vars.end())
		{
			vars[vec[1]] = new Numerus();
			objects.insert(vars[vec[1]]);
		}
		else
			throw std::invalid_argument("variable redefinition: " + vec[1]);
	}
}

void	LatinScript::handleStatement(const svector& vec, const_iterator it)
{
	if (isOperator(*it))
		handleOperator(vec, it);
}

void	LatinScript::handleOperator(const svector& vec, const_iterator it)
{
	auto op = operator_map.find(*it);

	switch(op->second)
	{
		case operators::ASSIGNMENT:
			handleAssignment(vec, it + 1);
			break ;
		case operators::PLUS:
			break ;
		case operators::MINUS:
			break ;
		case operators::MULTIPLY:
			break ;
		case operators::DIVIDE:
			break ;
	}
}

void	LatinScript::handleAssignment(const svector& vec, const_iterator it)
{
	if (it == vec.end())
		throw std::invalid_argument("invalid assignment operation");

	if (std::isdigit((*it)[0]) || (*it)[0] == '-' || (*it)[0] == '+')
	{
		delete (int *)vars[*(it - 2)]->value; // HARDCODE!! FIX!!!
		vars[*(it - 2)]->value = new int(toInt(*it));
	}
	else if (vars.find(*it) != vars.end() && \
		vars[*(it - 2)]->type == vars[*it]->type)
	{
		if (vars[*(it - 2)]->links == 1)
		{
			objects.erase(vars[*(it - 2)]);
			delete vars[*(it - 2)];
		}
		vars[*(it - 2)] = vars[*it];
		vars[*it]->links ++;
	}

}

void	LatinScript::handleOutput(const svector& vec, const std::string& line)
{
	auto it = vec.begin();

	if (*it == "scribere" && *(it + 1) == "<<")
	{
		if (search(line.begin(), line.end(), '*') != line.end())
		{
			std::string output = extractString(line, '*');
			displayOutput(true, output);
			_output = true;
			return ;
		}
		else if (vars.find(vec[2]) != vars.end())
		{
			displayOutput(true, vars[vec[2]]->__string());
			_output = true;
		}
		else
			throw std::invalid_argument("invalid input or nothing to output: " + vec[2]);
	}
}

LatinScript::~LatinScript()
{
	for (auto it = objects.begin(); it != objects.end(); ++it)
		delete *it;
	objects.clear();
}