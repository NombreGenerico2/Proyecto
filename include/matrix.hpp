#pragma once

#include <vector>

class matrix
{
	std::vector<bool> v;
	size_t length;

public:
	matrix(size_t size):
		v(size*size),
		length(size)
	{};

	std::vector<bool>::reference operator()(size_t p, size_t q);
};
