#include "LatinScript.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		ls::usage();
		return 0;
	}

	ls::LatinScript script(av[1]);

	return 0;
}
