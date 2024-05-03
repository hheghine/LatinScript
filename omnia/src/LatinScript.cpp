#include "LatinScript.hpp"

using namespace ls;

LatinScript::LatinScript(const std::string& filename)
{
	try {
		letsGo(filename);
	} catch (const std::exception& e) {
		std::cout << ls::MAIN << "[ " << ls::RED << "✘" \
		<< ls::MAIN << " ] " << "exeption: " << e.what() \
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
				displayOutput(false, "NONE ( " + vec[1] + " declaration )");
				continue ;
			}

			it += 2;

			if (vec[2] != "=")
				throw std::invalid_argument("wrong operation: " + vec[2]);
		}
		else if (vars.find(vec[0]) != vars.end())
			it += 1;
		else if (isCondition(vec[0]))
			std::cout << "CONDITION !!" << std::endl;
		else if (isLoop(vec[0]))
			std::cout << "LOOP !!" << std::endl;
		else
			throw std::invalid_argument("bad start statement: " + vec[0]);
		handleStatement(vec, vec.begin() + 2);
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
	(void) vec;
	(void) it;
}

LatinScript::~LatinScript()
{
	for (auto it = objects.begin(); it != objects.end(); ++it)
		delete *it;
	objects.clear();
}