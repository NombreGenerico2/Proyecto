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

	size_t size() const
	{
		return length;
	};

	std::vector<bool>::reference operator()(size_t p, size_t q);
	std::vector<bool>::const_reference operator()(size_t p, size_t q) const;

	friend std::ostream& operator<<(std::ostream& os, const matrix& m);
};

std::ostream& operator<<(std::ostream& os, const matrix& m);
