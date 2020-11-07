#include <matrix.hpp>

std::vector<bool>::reference matrix::operator()(size_t p, size_t q)
{
	return v[p*length + q];
}
