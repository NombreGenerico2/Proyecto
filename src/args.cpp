#include <cstdio>
#include <cstdlib>
#include <unistd.h>

#include <args.hpp>

void args::parse(int argc, char *argv[])
{
	char* file = nullptr;

	int c;
	while((c = getopt(argc, argv, "abmMhH12345")) != -1)
	{
		switch(c)
		{
			case 'a':
				action = action_t::all;
				break;

			case 'b':
			case '1':
				action = action_t::brzozowski;
				break;

			case 'm':
			case '2':
				action = action_t::stateEquivalence;
				break;

			case 'M':
			case '3':
				action = action_t::stateEquivalence2;
				break;

			case 'h':
			case '4':
				action = action_t::huffman;
				break;

			case 'H':
			case '5':
				action = action_t::hopcroft;
				break;
		}
	}

	while(optind < argc)
	{
		file = argv[optind++];
	}

	if(file != nullptr)
	{
		if(!freopen(file, "r", stdin))
		{
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
	}
}
