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
# include "Filum.hpp"
# include "Utils.hpp"


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

const char* const MAIN = "\033[38;2;56;0;198m";

const char* const CRST = "\033[0m";

/*-----------------ALIASES-----------------*/

using svector = std::vector<std::string>;
using iterator = svector::iterator;
using const_iterator = svector::const_iterator;

/*------------GLOBAL VARIABLES------------*/

extern std::unordered_map<std::string, Object *> vars;

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

/*----------------MESSAGES----------------*/

inline static void	usage()
{
	std::cout << ls::BGRY << "+-------------------------------------------------------+\n" << "|" \
	<< ls::GRY << "\tUsage: " << ls::MAIN << "./latins-cript <*******.ls>" \
	<< ls::BGRY << "\t\t|\n" << "+-------------------------------------------------------+" \
	<< ls::CRST << std::endl;
}

inline static void	displayTime()
{
	auto now = std::chrono::system_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(\
											now.time_since_epoch()) % 1000;
	std::time_t t = std::chrono::system_clock::to_time_t(now);
	std::tm tm = *std::localtime(&t);

	std::cout << std::put_time(&tm, "%H:%M:%S") \
		<< "." << std::setfill('0') << std::setw(3) << ms.count();
}

inline static void	displayInput(const svector& vec)
{
	std::cout << BGRY << "[ ";
	displayTime();
	std::cout << " | INPUT  ]\t" << GRY;

	for (auto it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << CRST << std::endl;
}

inline static void	displayOutput(bool flag, const std::string& message)
{
	std::cout << MAIN << "[ ";
	displayTime();
	std::cout << " | OUTPUT ]\t";

	flag ? std::cout << MAIN << message : std::cout << GRY << "-";

	std::cout << CRST << std::endl;
}

/*-----------LATIN-SCRIPT CLASS-----------*/

class LatinScript {

	public:
		LatinScript();
		virtual ~LatinScript() {}

	public:
		std::unordered_set<Object *> objects;
	
	protected:
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

		std::string _line;

	protected:
		virtual void	letsGo(const std::string& filename) = 0;
		virtual void	handleOperator(const svector& vec, const_iterator lhs, const_iterator& it) = 0;

		virtual void	mainLoop(std::ifstream& file, const std::string& line) { (void)file; (void)line; }
		virtual void	handleAssignment(const svector& vec, const_iterator lhs, const_iterator& it) = 0;

		void	createVariable(const svector& vec);
		void	handleStatement(const svector& vec, const_iterator it);
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

		void	handleLoop(std::ifstream& file, const std::string& condition);

		std::string	extractString(const svector& vec, const_iterator& it);
};


};


#endif