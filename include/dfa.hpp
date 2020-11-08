#pragma once

#include <vector>
#include <array>
#include <iostream>

#include <nfa.hpp>

class dfa
{
	struct state
	{
		std::array<int, 2> transitions;
		bool accepting = false;
	};

	int initial;
	std::vector<state> states;

	friend std::istream& operator>>(std::istream& is, dfa& _dfa);
	friend std::ostream& operator<<(std::ostream& os, const dfa& _dfa);

	friend class nfa;

public:
	nfa reverse_edges();
	dfa brzozowski();
	void stateEquivalence();
};

std::istream& operator>>(std::istream& is, dfa& _dfa);
std::ostream& operator<<(std::ostream& os, const dfa& _dfa);
