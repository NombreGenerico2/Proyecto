#pragma once

#include <vector>
#include <map>

class dfa;

class nfa
{
	struct state
	{
		std::multimap<int, int> transitions;
		bool accepting = false;
	};

	int initial;
	std::vector<state> states;

	friend class dfa;

public:
	operator dfa();
};
