#pragma once

#include <array>
#include <iostream>
#include <set>
#include <vector>

#include <matrix.hpp>
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

	std::vector<bool> closure(int state) const;
	std::set<std::set<int>> make_partition();

public:
	nfa reverse_edges();
	dfa brzozowski();
	matrix stateEquivalence();

	matrix stateEquivalence2();
	dfa huffman();
	dfa hopcroft();
};

std::istream& operator>>(std::istream& is, dfa& _dfa);
std::ostream& operator<<(std::ostream& os, const dfa& _dfa);
