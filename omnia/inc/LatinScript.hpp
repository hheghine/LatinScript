#ifndef LATINSCRIPT_HPP
# define LATINSCRIPT_HPP

# include <iostream>
# include <algorithm>
# include <vector>
# include <string>
# include <unordered_map>
# include <unordered_set>
# include <filesystem>
# include <fstream>
# include <exception>
# include <ctime>
# include <iomanip>
# include <chrono>

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

const char* const MAIN = "\033[38;2;63;0;191m";

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
	DIVIDE		= '/',
};

/*-------------ENUM CONDITION-------------*/

enum class conditions : char {
	EQUAL		= '0',
	GREATER		= '1',
	LESS		= '2',
	GREATER_EQ	= '3',
	LESS_EQ		= '4'
};

/*--------------OPERATOR MAP--------------*/

const std::unordered_map<std::string, operators> operator_map = {
	{"=", operators::ASSIGNMENT},
	{"+", operators::PLUS},
	{"-", operators::MINUS},
	{"*", operators::MULTIPLY},
	{"/", operators::DIVIDE},
};

/*--------------CONDITION MAP--------------*/

const std::unordered_map<std::string, conditions> condition_map = {
	{"==", conditions::EQUAL},
	{">", conditions::GREATER},
	{"<", conditions::LESS},
	{">=", conditions::GREATER_EQ},
	{"<=", conditions::LESS_EQ}
};

/*-------------RESERVED NAMES-------------*/

const svector reserved = {
	{"numerus"},	/* int		*/
	{"filum"},		/* string	*/
	{"verum"},		/* bool		*/
	{"duplus"},		/* double	*/
	{"dum"},		/* while	*/
	{"scribere"},	/* cout		*/
	{"arredo"},		/* array	*/
	{"tmp"},
	{"__lhs"},
	{"__rhs"}
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
	auto now = std::chrono::system_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(\
											now.time_since_epoch()) % 1000;
	std::time_t t = std::chrono::system_clock::to_time_t(now);
	std::tm tm = *std::localtime(&t);

	std::cout << BGRY << "[ " << std::put_time(&tm, "%H:%M:%S") \
		<< "." << std::setfill('0') << std::setw(3) << ms.count() \
		<< " | INPUT  ]\t" << GRY;

	for (auto it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << CRST << std::endl;
}

inline static void	displayOutput(bool flag, const std::string& message)
{
	auto now = std::chrono::system_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(\
											now.time_since_epoch()) % 1000;
	std::time_t t = std::chrono::system_clock::to_time_t(now);
	std::tm tm = *std::localtime(&t);

	std::cout << MAIN << "[ " << std::put_time(&tm, "%H:%M:%S") \
		<< "." << std::setfill('0') << std::setw(3) << ms.count() << " | OUTPUT ]\t";

	flag ? std::cout << MAIN << message : std::cout << GRY << "-";

	std::cout << CRST << std::endl;
}

/*------------------UTILS------------------*/

svector		splitLine(const std::string& line);

bool		isAssignment(const std::string& key);
bool		isOperator(const std::string& key);
bool		isType(const std::string& statement);
bool		isLoop(const std::string& statement);
bool		isCondition(const std::string& statement);
bool		isConditionOperator(const std::string& statement);
bool		varNameCheck(const std::string& name);

int			toInt(const std::string& str);


std::string::const_iterator	search(std::string::const_iterator start, \
									std::string::const_iterator end, \
									char key);
std::string::const_iterator	search(std::string::const_iterator start, \
									std::string::const_iterator end, \
									const std::string& key);

std::string	extractString(std::string::const_iterator start, \
							std::string::const_iterator end, char key);
std::string	extractString(std::string::const_iterator start, \
							std::string::const_iterator end);

/*-----------LATIN-SCRIPT CLASS-----------*/

class LatinScript {

	public:
		LatinScript(const std::string& filename);
		~LatinScript();

	private:
		std::unordered_map<std::string, Object *> vars;
		std::unordered_set<Object *> objects;
	
	private:
		bool _output;
		bool _chainedOperations;
		bool _isAssignment;

		bool _is_if;
		bool _is_elseif;
		bool _is_else;

		bool __if;
		bool __elseif;
		bool __else;

		bool _ignore;

	private:
		void	letsGo(const std::string& filename);
		void	createVariable(const svector& vec);
		void	handleStatement(const svector& vec, const_iterator it);
		void	handleOperator(const svector& vec, const_iterator lhs, const_iterator& it);
		void	handleAssignment(const svector& vec, const_iterator lhs, const_iterator& it);
		void	handleAddition(const svector& vec, const_iterator lhs, const_iterator& it);
		void	handleSubstraction(const svector& vec, const_iterator lhs, const_iterator& it);
		void	handleMultiplication(const svector& vec, const_iterator lhs, const_iterator& it);
		void	handleDivision(const svector& vec, const_iterator lhs, const_iterator& it);
		void	handleCondition(const svector& vec);
		void	handleOutput(const svector& vec, const std::string& line);

		bool	handleIsEqual(const std::string& lhs, const std::string& rhs);
		bool	handleIsGreater(const std::string& lhs, const std::string& rhs);
		bool	handleIsLess(const std::string& lhs, const std::string& rhs);
		bool	handleIsGreaterOrEq(const std::string& lhs, const std::string& rhs);
		bool	handleIsLessOrEq(const std::string& lhs, const std::string& rhs);
		bool	isConditionTrue(const std::string& op, const std::string& lhs, const std::string& rhs);
		bool	conditionBlockTrue(const std::string& block);

};


};


#endif