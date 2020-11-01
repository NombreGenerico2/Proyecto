#pragma once

#include <vector>
#include <array>
#include <iostream>

class afd
{
	struct state
	{
		std::array<int, 2> transitions;
	};

	int initial;
	std::vector<bool> finals;
	std::vector<state> states;

	friend std::istream& operator>>(std::istream& is, afd& _afd);
	friend std::ostream& operator<<(std::ostream& is, const afd& _afd);
};

std::istream& operator>>(std::istream& is, afd& _afd);
std::ostream& operator<<(std::ostream& os, const afd& _afd);
