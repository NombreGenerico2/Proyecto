#include <cstdio>
#include <iostream>

#include <dfa.hpp>
#include <args.hpp>

int main(int argc, char *argv[])
{
	if(argc > 1)
		if(!freopen(argv[argc-1], "r", stdin))
		{
			perror(argv[0]);
			return EXIT_FAILURE;
		}

	dfa d;
	std::cin >> d;

	std::cout
		<< "Pregunta 1:\n"
		<< d.brzozowski() << '\n'
		<< "Pregunta 2:\n"
		<< d.stateEquivalence() << '\n'
		<< "Pregunta 3:\n"
		<< d.stateEquivalence2() << '\n'
		<< "Pregunta 4:\n"
		<< d.huffman() << '\n'
		<< "Pregunta 5:\n"
		<< d.huffman(partition_t::hopcroft) << '\n'
	;

	return 0;
}
