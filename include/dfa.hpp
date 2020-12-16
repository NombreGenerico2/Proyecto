#pragma once

#include <array>
#include <iostream>
#include <set>
#include <vector>

#include <matrix.hpp>
#include <nfa.hpp>

enum class partition_t
{
	matrix1,
	matrix2,
	hopcroft
};

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
	std::set<std::set<int>> make_partition() const;

public:
	nfa reverse_edges() const;
	dfa brzozowski() const;
	matrix stateEquivalence() const;

	matrix stateEquivalence2() const;
	dfa huffman(partition_t p = partition_t::matrix1) const;
	std::set<std::set<int>> hopcroft() const;
};

std::istream& operator>>(std::istream& is, dfa& _dfa);
std::ostream& operator<<(std::ostream& os, const dfa& _dfa);
