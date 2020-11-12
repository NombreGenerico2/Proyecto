#pragma once

#include <iostream>
#include <vector>


#define equivalent      false
#define distinguishable true

class matrix
{
	std::vector<bool> v;
	size_t length;

public:
	matrix(size_t size):
		v(size*size, false),
		length(size)
	{};

	std::vector<bool>::reference operator()(size_t p, size_t q);

	friend std::ostream& operator<<(std::ostream& os, const matrix& m);
};

std::ostream& operator<<(std::ostream& os, const matrix& m);
