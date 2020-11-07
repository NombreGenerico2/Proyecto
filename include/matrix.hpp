#pragma once

#include <vector>

#define equivalent      true
#define distinguishable false

class matrix
{
	/// true  = equivalent      = ' '
	/// false = distinguishable = 'x'
	std::vector<bool> v;
	size_t length;

public:
	matrix(size_t size):
		v(size*size, equivalent),
		length(size)
	{};

	std::vector<bool>::reference operator()(size_t p, size_t q);
};
