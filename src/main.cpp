#include <dfa.hpp>
#include <iostream>

int main()
{
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
