#ifndef SCRIPT_RUNNER
# define SCRIPT_RUNNER

# include "LatinScript.hpp"
# include "Functio.hpp"

using namespace ls;

class ScriptRunner : public LatinScript {
	public:
		explicit ScriptRunner(const std::string& filename);
		~ScriptRunner();

	public:
		std::unordered_map<std::string, Functio *> functions;

	private:
		void	letsGo(const std::string& filename);
		void	mainLoop(std::ifstream& file, const std::string& line);

		void	createVariable(const std::vector<std::string>& vec);
		void	handleFunction(std::ifstream& file, const std::string& declaration);
};

#endif