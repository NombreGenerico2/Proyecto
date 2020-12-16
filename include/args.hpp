#pragma once

#include <array>

enum class action_t
{
	all,
	brzozowski,
	stateEquivalence,
	stateEquivalence2,
	huffman,
	hopcroft
};

struct args
{
	void parse(int argc, char *argv[]);

	action_t action = action_t::all;
};
