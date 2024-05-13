#ifndef SCRIPT_RUNNER
# define SCRIPT_RUNNER

# include "LatinScript.hpp"

using namespace ls;

class ScriptRunner : public LatinScript {
	public:
		explicit ScriptRunner(const std::string& filename);
		~ScriptRunner();

	private:
		std::unordered_map<std::string, Functio *> functions;

	private:
		void	letsGo(const std::string& filename);
		void	mainLoop(std::ifstream& file, const std::string& line);
};

#endif