#include <dfa.hpp>

#include <set>

std::istream& operator>>(std::istream& is, dfa& _dfa)
{
	int n, initial, finals_n;
	is >> n >> initial >> finals_n;

	_dfa.states = std::vector<dfa::state>(n);
	_dfa.initial = initial;

	//Estados de aceptacion
	for(int i = 0; i < finals_n; ++i)
	{
		int accepting;
		is >> accepting;

		_dfa.states[accepting].accepting = true;
	}

	//Transiciones
	for(int i = 0; i < n*2; ++i)
	{
		int p, a, q;
		is >> p >> a >> q;

		_dfa.states[p].transitions[a] = q;
	}

	return is;
}

std::ostream& operator<<(std::ostream& os, const dfa& _dfa)
{
	int accepting_n = 0;
	for(auto i: _dfa.states)
		if(i.accepting)
			accepting_n++;

	os
		<< _dfa.states.size() << ' '
		<< _dfa.initial << ' '
		<< accepting_n
	;

	for(size_t i = 0; i < _dfa.states.size(); ++i)
	{
		if(_dfa.states[i].accepting)
			os << ' ' << i;
	}

	os << '\n';

	for(size_t i = 0; i < _dfa.states.size(); ++i)
	{
		for(size_t j = 0; j < _dfa.states[i].transitions.size(); ++j)
		{
			os
				<< i << ' '
				<< j << ' '
				<< _dfa.states[i].transitions[j]
				<< '\n'
			;
		}
	}

	return os;
}
//O(n)
nfa dfa::reverse_edges()
{
	nfa n;

	n.states = std::vector<nfa::state>(states.size());
	n.states[initial].accepting = true;
	//O(n)
	for(size_t i = 0; i < states.size(); ++i)
	{
		//O(1)
		if(states[i].accepting)
			n.initials.push_back(i);
		//O(1)
		// 2 = states[i].transitions.size()
		for(size_t j = 0; j < 2; ++j)
		{
			n.states.at(states.at(i).transitions.at(j)).transitions.insert({j, i});
		}
	}

	return n;
}
//O(2^n)
dfa dfa::brzozowski()
{
	//reverse_edges() O(n)
	//powerset() O(2^n)
	return reverse_edges().powerset().reverse_edges().powerset();
}
//O(n^4)
matrix dfa::stateEquivalence()
{
	size_t n = states.size();

	matrix m(n);

	matrix v(n);
	//O(n^2)
	for(size_t i = 0; i < n; i++){
		if(states[i].accepting){
			//o(n)
			for(size_t j = 0; j < i; j++){
				if(!states[j].accepting){
					m(i, j) = distinguishable;
					v(i, j) = distinguishable;
				}
			}
			//O(n)
			for(size_t k = i + 1; k < n; k++){
				if(!states[k].accepting){
					m(k, i) = distinguishable;
					v(k, i) = distinguishable;
				}
			}
		}
	}


	int modificaciones = 1;
	//O(n^4)
	while(modificaciones > 0)
	{
		modificaciones = 0;
		//O(n^2)
		for(size_t i = 0  ; i < n ;i++){
			//O(n)
			for(size_t j = 0 ; j < n; j++){
				if (i == j)continue;
				//O(1)
				for(int symbol = 0 ; symbol <= 1 ; symbol++){
					if (m(states[i].transitions[symbol], states[j].transitions[symbol]) && v(i,j) == false){
						m(i, j) = distinguishable;
						v(i, j) = distinguishable;
						modificaciones++;
					}
				}
			}
		}
	}

	return m;
}

matrix dfa::stateEquivalence2()
{
	// TODO
	return stateEquivalence();
}

dfa dfa::huffman()
{
	auto fill = [](const matrix& m) -> std::set<std::set<int>>
	{
		std::multimap<int, int> closures;

		for(size_t i = 0; i < m.size(); ++i)
		{
			for(size_t j = 0; j < m.size(); ++j)
			{
				if(m(i, j))
					closures.insert({i, j});
			}
		}

		std::set<std::set<int>> result;
		for(size_t i = 0; i < m.size(); ++i)
		{
			std::set<int> new_set;
			new_set.insert(i);

			auto range = closures.equal_range(i);
			for(auto it = range.first; it != range.second; ++it)
			{
				new_set.insert(it->second);
			}

			result.insert(new_set);
		}

		return result;
	};

	dfa d;
	int state_c = 0;

	for(const auto& s: fill(stateEquivalence2()))
	{
		auto& new_state = d.states.emplace_back(state{});

		if(s.find(initial) != s.end())
			d.initial = state_c;

		for(const auto& state: s)
		{
			if(states[state].accepting)
			{
				new_state.accepting = true;
			}
		}

		// TODO transitions

		state_c++;
	}


	return d;
}

dfa dfa::hopcroft()
{
	// TODO
	return *this;
}
