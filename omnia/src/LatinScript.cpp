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

		// auto it = vec.begin();
		bool is_type = isType(vec[0]);

		if(is_type)
		{
			createVariable(vec);
			// std::cout << "{ " << vec[0] << " } it's a declaration => gotta handle the operation" << std::endl;
			if (vec.begin() + 2 == vec.end())
			{
				displayOutput(false, "NONE ( " + vec[1] + " declaration )");
				continue ;
			}
			if (vec[2] != "=")
				throw std::invalid_argument("wrong operation: " + vec[2]);
		}
		handleManipulation(vec, vec.begin() + 2);
		// else
			// existing var/loop/function/invalid
	}



}

bool	LatinScript::createVariable(const std::vector<std::string>& vec)
{
	if (vec.size() < 2)
		throw std::invalid_argument("syntax error");
	if (vec[0] == "numerus")
	{
		if (vars.find(vec[1]) == vars.end())
		{
			vars[vec[1]] = new Numerus();
			objects.insert(vars[vec[1]]);
			return true;
		}
		else
			throw std::invalid_argument("variable redefinition: " + vec[1]);
	}
	
	return false;
}

void	LatinScript::handleManipulation(const svector& vec, const_iterator it)
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