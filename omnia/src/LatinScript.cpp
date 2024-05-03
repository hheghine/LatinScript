#include "LatinScript.hpp"

using namespace ls;

LatinScript::LatinScript(const std::string& filename)
{
	letsGo(filename);
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
		std::vector<std::string> vec = splitLine(line);
		if (vec.empty())
			continue;

		bool is_type = typeIdentifier(vec);

		if(is_type)
			std::cout << "{ " << vec[0] << " } it's a type => gotta handle the operation" << std::endl;
		else
			std::cout << "not a type => loop/function/invalid" << std::endl;
	}

}

bool	LatinScript::typeIdentifier(const std::vector<std::string>& vec)
{
	if (vec.size() < 2)
		throw std::invalid_argument("syntax error");
	if (vec[0] == "numerus")
	{
		vars[vec[1]] = new Numerus();
		objects.insert(vars[vec[1]]);
		return true;
	}
	return false;
}

LatinScript::~LatinScript()
{
	for (auto it = objects.begin(); it != objects.end(); ++it)
		delete *it;
	objects.clear();
}