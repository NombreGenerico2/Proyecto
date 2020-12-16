#include <iostream>

#include <dfa.hpp>
#include <args.hpp>

int main(int argc, char *argv[])
{
	args a;
	a.parse(argc, argv);

	dfa d;
	std::cin >> d;

	switch(a.action)
	{
		case action_t::all:
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
			break;

		case action_t::brzozowski:
			std::cout
				<< "Pregunta 1:\n"
				<< d.brzozowski() << '\n'
			;
			break;

		case action_t::stateEquivalence:
			std::cout
				<< "Pregunta 2:\n"
				<< d.stateEquivalence() << '\n'
			;
			break;

		case action_t::stateEquivalence2:
			std::cout
				<< "Pregunta 3:\n"
				<< d.stateEquivalence2() << '\n'
			;
			break;

		case action_t::huffman:
			std::cout
				<< "Pregunta 4:\n"
				<< d.huffman() << '\n'
			;
			break;

		case action_t::hopcroft:
			std::cout
				<< "Pregunta 5:\n"
				<< d.huffman(partition_t::hopcroft) << '\n'
			;
			break;
	}


	return 0;
}
