#include <dfa.hpp>
#include <iostream>

int main()
{
	dfa d;
	std::cout
		<< "Ingrese input de afd:\n";

	std::cin >> d;

	std::cout
		<< "Pregunta 1:\n"
		<< d.brzozowski() << '\n'
	;
	//Pregunta2
	std::cout
		<< "Pregunta 2:\n"
	;
		d.stateEquivalence();

	return 0;
}
