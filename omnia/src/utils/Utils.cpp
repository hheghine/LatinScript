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

bool	ls::varNameCheck(const std::string& name)
{
	for (auto it = ls::reserved.begin(); it != ls::reserved.end(); ++it)
		if (name == *it)
			return false;

	if ((name[0] >= 65 && name[0] <= 90) || \
		(name[0] >= 97 && name[0] <= 122) || \
		name[0] == '_')
		return true;

	return false;
}

int	ls::toInt(const std::string& str)
{
	std::stringstream ss(str);
	int val = 0;
	char remaining;

	if (!(ss >> val) || ss.get(remaining))
		throw std::invalid_argument("invalid assignment operation: " + str);
	return val;
}

std::string ls::extractString(const std::string& line, char key)
{
	std::string extracted;
	bool opened = false;

	for (auto it = line.begin(); it != line.end(); ++it)
	{
		if (*it == key && !opened)
		{
			opened = true;
			continue;
		}
		if (*it == key)
			return extracted;
		if (opened)
		{
			if (*it == '\\')
			{
				++it;
				if (it == line.end())
					throw std::invalid_argument("wrong syntax: " + line);
				switch (*it)
				{
					case 'n':
						extracted += '\n';
						break;
					case '\t':
						extracted += '\t';
						break;
					default:
						extracted += *it;
						break;
				}
			}
			else
			{
				extracted += *it;
			}
		}
	}
	throw std::invalid_argument("wrong syntax: " + line);
}

std::string::const_iterator	ls::search(std::string::const_iterator start, \
										std::string::const_iterator end, char key)
{
	std::string::const_iterator it;

	for (it = start; it != end; ++it)
		if (*it == key)
			return it;
	return end;
}