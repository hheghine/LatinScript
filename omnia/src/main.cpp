#include "LatinScript.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		ls::usage();
		return 0;
	}

	try {
		ls::LatinScript{av[1]};
	} catch (const std::exception& e) {
		std::cout << ls::MAIN << "[ " << ls::RED << "✘" \
		<< ls::MAIN << " ] " << "exeption: " << e.what() \
		<< ls::CRST << std::endl;
	}

}