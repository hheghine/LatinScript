#ifndef SCRIPT_RUNNER
# define SCRIPT_RUNNER

# include "LatinScript.hpp"
# include "Functio.hpp"

using namespace ls;
class Functio;

/*---------------------GLOBAL VARIABLE---------------------*/

extern std::unordered_map<std::string, Functio *> functions;


/*----------------------SCRIPT RUNNER----------------------*/

class ScriptRunner : public LatinScript {
	public:
		explicit ScriptRunner(const std::string& filename);
		~ScriptRunner();

	private:
		void	letsGo(const std::string& filename);
		void	mainLoop(std::ifstream& file, const std::string& line);
		void	handleAssignment(const svector& vec, const_iterator lhs, const_iterator& it);

		void	createVariable(const std::vector<std::string>& vec);
		void	parseFunction(std::ifstream& file, const std::string& declaration);
};

#endif