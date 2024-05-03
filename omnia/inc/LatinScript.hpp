#ifndef LATINSCRIPT_HPP
# define LATINSCRIPT_HPP

# include <iostream>
# include <vector>
# include <string>
# include <unordered_map>
# include <unordered_set>
# include <filesystem>
# include <fstream>
# include <exception>

# include "Numerus.hpp"

namespace ls
{

/*------------COLOR CONSTANTS------------*/
const char* const WHT = "\033[0;37m";
const char* const GRN = "\033[0;32m";
const char* const CYN = "\033[0;36m";
const char* const GRY = "\033[0;90m";
const char* const RED = "\033[0;31m";

const char* const BWHT = "\033[1;37m";
const char* const BGRN = "\033[1;32m";
const char* const BCYN = "\033[1;36m";
const char* const BGRY = "\033[1;90m";

const char* const MAIN = "\033[38;2;153;1;102m";

const char* const CRST = "\033[0m";

/*-----------------ALIASES-----------------*/

using svector = std::vector<std::string>;
using iterator = svector::iterator;
using const_iterator = svector::const_iterator;

/*---------------ENUM CLASS---------------*/

enum class operators : char {
	ASSIGNMENT	= '=',
	PLUS		= '+',
	MINUS		= '-',
	MULTIPLY	= '*',
	DIVIDE		= '/'
};

/*--------------OPERATOR MAP--------------*/

const std::unordered_map<std::string, operators> operator_map = {
	{"=", operators::ASSIGNMENT},
	{"+", operators::PLUS},
	{"-", operators::MINUS},
	{"*", operators::MULTIPLY},
	{"/", operators::DIVIDE}
};

/*----------------MESSAGES----------------*/

inline static void	usage()
{
	std::cout << ls::BGRY << "+-------------------------------------------------------+\n" << "|" \
	<< ls::GRY << "\tUsage: " << ls::MAIN << "./latins-cript <*******.ls>" \
	<< ls::BGRY << "\t\t|\n" << "+-------------------------------------------------------+" \
	<< ls::CRST << std::endl;
}

inline static void	displayInput(const svector& vec)
{
	std::cout << BGRY << "[ INPUT  ]\t" << WHT;

	for (auto it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << CRST << std::endl;
}

inline static void	displayOutput(bool flag, const std::string& message)
{
	std::cout << BGRY << "[ OUTPUT ]\t" << \
	(flag ? MAIN : GRY) << message << CRST << std::endl;
}

/*------------------UTILS------------------*/

svector	splitLine(const std::string& line);

bool		isAssignment(const std::string& key);
bool		isOperator(const std::string& key);
bool		isType(const std::string& statement);
bool		isLoop(const std::string& statement);
bool		isCondition(const std::string& statement);

/*-----------LATIN-SCRIPT CLASS-----------*/

class LatinScript {
	public:
		std::unordered_map<std::string, Object *> vars;
		std::unordered_set<Object *> objects;

		LatinScript(const std::string& filename);
		~LatinScript();

		void	letsGo(const std::string& filename);
		bool	createVariable(const svector& vec);
		void	handleManipulation(const svector& vec, const_iterator it);
};


};


#endif