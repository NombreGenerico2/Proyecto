#include <dfa.hpp>
#include <iostream>

int main()
{
	dfa d;
	std::cout
		<< "Ingrese input de afd:\n";

	std::cin >> d;

	// Pregunta 1
	std::cout
		<< "Pregunta 1:\n"
		<< d.brzozowski() << '\n\n'
	;
	//Pregunta2
	std::cout
		<< "Pregunta 2:\n"
	;
	d.stateEquivalence();
	// TODO

	return 0;
}
