#include <matrix.hpp>

std::vector<bool>::reference matrix::operator[] (std::pair<int, int> pq)
{
	return v[pq.first*length + pq.second];
}
