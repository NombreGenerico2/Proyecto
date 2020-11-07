#include <afd.hpp>
#include <matrix.hpp>

std::istream& operator>>(std::istream& is, afd& _afd)
{
	int n, initial, finals_n;
	is >> n >> initial >> finals_n;

	_afd.states = std::vector<afd::state>(n);
	_afd.initial = initial;

	for(int i = 0; i < finals_n; ++i)
	{
		int accepting;
		is >> accepting;

		_afd.states[accepting].accepting = true;
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
	int accepting_n = 0;
	for(auto i: _afd.states)
		if(i.accepting)
			accepting_n++;

	os
		<< _afd.states.size() << ' '
		<< _afd.initial << ' '
		<< accepting_n
	;

	for(size_t i = 0; i < _afd.states.size(); ++i)
	{
		if(_afd.states[i].accepting)
			os << ' ' << i;
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
	matrix m(states.size());

	return *this;
}
