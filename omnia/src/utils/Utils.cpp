#include "LatinScript.hpp"

ls::svector	ls::splitLine(const std::string& line)
{
	std::stringstream ss(line);

	std::vector<std::string> vec;
	std::string	word;

	while (ss >> word)
		vec.push_back(word);
	return vec;
}

bool	ls::isOperator(const std::string& key)
{
	return (key == "=" || key == "+" || key == "-" \
			|| key == "*" || key == "/");
}