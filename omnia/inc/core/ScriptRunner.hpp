#ifndef SCRIPT_RUNNER
# define SCRIPT_RUNNER

# include "LatinScript.hpp"
# include "Functio.hpp"

# include <stack>

using namespace ls;
class Functio;

/*---------------------GLOBAL VARIABLE---------------------*/

extern std::unordered_map<std::string, Functio *>	g_functions;
extern std::stack<svector>							g_function_args;
extern std::unordered_map<std::string, Ordinata *>	g_arrays;

/*----------------------SCRIPT RUNNER----------------------*/

class ScriptRunner : public LatinScript {
	public:
		explicit ScriptRunner(const std::string& filename);
		~ScriptRunner();

	public:
		svector tmp_arr;

		static void	handleFunction(const svector& vec, const_iterator lhs, const_iterator& name);
	private:
		void	letsGo(const std::string& filename);
		void	mainLoop(std::ifstream& file, const std::string& line);
		void	handleOperator(const svector& vec, const_iterator lhs, const_iterator& it);
		void	handleAssignment(const svector& vec, const_iterator lhs, const_iterator& it);
		void	handleOutput(const svector& vec, const std::string& line);
		void	handleArray(svector& vec, iterator& it);

		void	parseFunction(std::ifstream& file, const std::string& declaration);

		Object* createVar(const std::string& type);

};

#endif