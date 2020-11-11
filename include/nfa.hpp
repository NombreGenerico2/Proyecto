#pragma once

#include <iostream>
#include <map>
#include <vector>

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
	dfa powerset();
};
