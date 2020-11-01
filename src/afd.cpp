#include <afd.hpp>
#include <experimental/iterator>
#include <algorithm>

std::istream& operator>>(std::istream& is, afd& _afd)
{
	int n, initial, finals_n;
	is >> n >> initial >> finals_n;

	_afd.states = std::vector<afd::state>(n);
	_afd.initial = initial;
	_afd.finals = std::vector<int>(finals_n);

	for(int i = 0; i < finals_n; ++i)
	{
		int _final;
		is >> _final;

		_afd.finals[i] = _final;
	}

	for(int i = 0; i < n*2; ++i)
	{
		int p, a, q;
		is >> p >> a >> q;

		_afd.states[p].transitions[a] = q;
	}

	return is;
}

std::ostream& operator<<(std::ostream& os, const afd& _afd)
{
	os
		<< _afd.states.size() << ' '
		<< _afd.initial << ' '
		<< _afd.finals.size() << ' '
	;

	std::copy(
		_afd.finals.begin(),
		_afd.finals.end(),
		std::experimental::make_ostream_joiner(os, ' ')
	);

	os << '\n';

	for(size_t i = 0; i < _afd.states.size(); ++i)
	{
		for(size_t j = 0; j < _afd.states[i].transitions.size(); ++j)
		{
			os
				<< i << ' '
				<< j << ' '
				<< _afd.states[i].transitions[j]
				<< '\n'
			;
		}
	}

	return os;
}
