#pragma once

#include <vector>

class matrix
{
	std::vector<bool> v;

public:
	matrix(size_t size):
		v(size*size)
	{};
};
