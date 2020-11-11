#include <cstdio>
#include <iostream>

#include <dfa.hpp>

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
	;

	std::cout << "Pregunta 2:\n";
	d.stateEquivalence();

	return 0;
}
