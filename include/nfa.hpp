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

	std::vector<int> initials;
	std::vector<state> states;

	friend class dfa;

public:
	operator dfa();
};
