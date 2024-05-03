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

// statement == "arredo" || statement == "functio"
bool	ls::isType(const std::string& statement)
{
	return (statement == "numerus" || statement == "filum" \
		|| statement == "verum" || statement == "duplus");
}

bool	ls::isLoop(const std::string& statement)
{
	return statement == "dum";
}

bool	ls::isCondition(const std::string& statement)
{
	return statement == "<";
}

bool	ls::isAssignment(const std::string& key)
{
	return key == "=";
}

bool	ls::isOperator(const std::string& key)
{
	return (key == "=" || key == "+" || key == "-" \
			|| key == "*" || key == "/");
}