#include <dfa.hpp>
#include <iostream>

int main()
{
	dfa d;

	std::cin >> d;

	// Pregunta 1
	std::cout
		<< "Pregunta 1:\n"
		<< d.brzozowski() << '\n'
	;

	// Pregunta 2
	// TODO

	return 0;
}
