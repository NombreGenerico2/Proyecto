#include <afd.hpp>

std::istream& operator>>(std::istream& is, afd& _afd)
{
	int n, initial, finals_n;
	is >> n >> initial >> finals_n;

	_afd.states = std::vector<afd::state>(n);
	_afd.initial = initial;
	_afd.finals = std::vector<bool>(n);

	for(int i = 0; i < finals_n; ++i)
	{
		int _final;
		is >> _final;

		_afd.finals[_final] = true;
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
	int final_n = 0;
	for(auto i: _afd.finals)
		if(i)
			final_n++;

	os
		<< _afd.states.size() << ' '
		<< _afd.initial << ' '
		<< final_n
	;

	for(size_t i = 0; i < _afd.finals.size(); ++i)
	{
		if(_afd.finals[i])
		{
			os << ' ' << i;
		}
	}

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

afd afd::brzozowski()
{
	// TODO
	return *this;
}
