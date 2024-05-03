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

// # include "Object.hpp"
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

/*----------------MESSAGES----------------*/

inline static void	usage()
{
	std::cout << ls::BGRY << "+-------------------------------------------------------+\n" << "|" \
	<< ls::GRY << "\tUsage: " << ls::MAIN << "./latins-cript <*******.ls>" \
	<< ls::BGRY << "\t\t|\n" << "+-------------------------------------------------------+" \
	<< ls::CRST << std::endl;
}

/*------------------UTILS------------------*/

std::vector<std::string>	splitLine(const std::string& line);

/*-----------LATIN-SCRIPT CLASS-----------*/

class LatinScript {
	public:
		std::unordered_map<std::string, Object *> vars;
		std::unordered_set<Object *> objects;

		LatinScript(const std::string& filename);
		~LatinScript();

		void	letsGo(const std::string& filename);
		bool	typeIdentifier(const std::vector<std::string>& vec);
};


};


#endif