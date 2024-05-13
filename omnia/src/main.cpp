#include "ScriptRunner.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		ls::usage();
		return 0;
	}

	ScriptRunner script(av[1]);

	return 0;
}
