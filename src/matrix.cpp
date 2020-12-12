#include <matrix.hpp>

std::vector<bool>::reference matrix::operator()(size_t p, size_t q)
{
	return v[p*length + q];
}

std::vector<bool>::const_reference matrix::operator()(size_t p, size_t q) const
{
	return v[p*length + q];
}

std::ostream& operator<<(std::ostream& os, const matrix& m)
{
	size_t i = 0;

	for(auto cell: m.v)
	{
		os << ((i % (m.length+1) == 0)? '-' : (cell? '0' : '1'));
		os << ((++i % m.length == 0)? '\n': ' ');
	}
	return os;
}
