#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <vector>
# include <string>
# include <sstream>
# include <algorithm>

namespace utils
{

/*-----------------ALIASES-----------------*/

using svector = std::vector<std::string>;
using iterator = svector::iterator;
using const_iterator = svector::const_iterator;

/*-------------RESERVED NAMES-------------*/

const svector reserved = {
	{"numerus"},	/* int		*/
	{"filum"},		/* string	*/
	{"verum"},		/* bool		*/
	{"duplus"},		/* double	*/
	{"dum"},		/* while	*/
	{"scribere"},	/* cout		*/
	{"ordinata"},	/* array	*/
	{"tmp"},
	{"_"}
};

/*----------------FUNCTIONS----------------*/

svector		splitLine(const std::string& line);
int			toInt(const std::string& str);
double		toDouble(const std::string& str);


bool		varNameCheck(const std::string& name);
bool		isAssignment(const std::string& key);
bool		isOperator(const std::string& key);
bool		isType(const std::string& statement);
bool		isLoop(const std::string& statement);
bool		isCondition(const std::string& statement);
bool		isConditionOperator(const std::string& statement);

std::string::const_iterator	search(std::string::const_iterator start, \
									std::string::const_iterator end, \
									char key);
std::string::const_iterator	search(std::string::const_iterator start, \
									std::string::const_iterator end, \
									const std::string& key);

std::string	extractString(std::string::const_iterator start, \
							std::string::const_iterator end, char key);
std::string	extractString(std::string& line, std::string::const_iterator start, \
							std::string::const_iterator end, char key);
std::string	extractString(std::string::const_iterator start, \
							std::string::const_iterator end);


}

#endif