#include <dfa.hpp>

#include <queue>

using namespace std;

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

dfa dfa::brzozowski()
{
	return reverse_edges().powerset().reverse_edges().powerset();
}
//O(n^4)
matrix dfa::stateEquivalence()
{
	size_t n = states.size();

	matrix m(n);

	matrix v(n);
	//O(n^2)
	for(size_t i = 0; i < n; i++)
	{
		if(states[i].accepting)
		{
			//o(n)
			for(size_t j = 0; j < i; j++)
			{
				if(!states[j].accepting){
					//cout<<"primer for"<<endl;
					m(i, j) = distinguishable;
					m(j,i) = distinguishable;
					v(j,i) = distinguishable;
					v(i, j) = distinguishable;
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
						m(j,i) = distinguishable;
						v(j, i) = distinguishable;
						v(i, j) = distinguishable;
						modificaciones++;


					}
				}
			}
		}
	}
	return m;
}
//O(n^2)
matrix dfa::stateEquivalence2()
{
	vector<pair<int ,int >> pares_;
	size_t n = states.size();
	for(size_t i = 0 ; i < n; i++){
		for(size_t j = 0; j < i; j++)
		{
			if(!states[j].accepting){
				pares_.push_back({i,j});
				pares_.push_back({j,i});
			}
		}
	}
	matrix m(n);
	for(int symbol = 0 ; symbol <= 1 ; symbol++){
		/*
		if (m(states[i].transitions[symbol], states[j].transitions[symbol]) && v(i,j) == false){
			m(i, j) = distinguishable;
			v(i, j) = distinguishable;
		}*/
	}

	return m;
}

std::vector<bool> dfa::closure(int state) const
{
	std::vector<bool> v(states.size());

	std::queue<int> to_visit;

	to_visit.push(state);

	while(!to_visit.empty())
	{
		int next_state = to_visit.front();

		for(int s: states[next_state].transitions)
		{
			if(!v[s])
			{
				to_visit.push(s);
				v[s] = true;
			}
		}

		to_visit.pop();
	}

	return v;
}

std::set<std::set<int>> dfa::make_partition()
{
	matrix m = stateEquivalence();
	auto c = closure(initial);

	std::multimap<int, int> closures;

	for(size_t i = 0; i < m.size(); ++i)
	{
		for(size_t j = 0; j < m.size(); ++j)
		{
			if(m(i, j) == equivalent)
				closures.insert({i, j});
		}
	}

	std::set<std::set<int>> result;
	for(size_t i = 0; i < m.size(); ++i)
	{
		if(!c[i])
			continue;

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
}

dfa dfa::huffman()
{
	dfa d;
	int state_c = 0;

	std::map<int, int> old2new;

	for(const auto& s: make_partition())
	{
		auto& new_state = d.states.emplace_back(state{});

		if(s.find(initial) != s.end())
			d.initial = state_c;

		for(const auto& state: s)
		{
			old2new[state] = state_c;

			if(states[state].accepting)
			{
				new_state.accepting = true;
			}

			// Old transitions
			new_state.transitions = states[state].transitions;
		}

		state_c++;
	}

	for(auto& s: d.states)
	{
		s.transitions = {old2new[s.transitions[0]], old2new[s.transitions[1]]};
	}

	return d;
}

dfa dfa::hopcroft()
{

	/*
		P = {F, Q/F} #particion
		W = {F, Q/F} #distinguishers
		states

	while(W is not empty):
		A = W.back()
		W.pop()
	for each c in [0, 1]:
		X = can_reach(A, c)
		#X: todos los estados que pueden llegar a A (de estados) mediante el caracter c
		for each set Y in P:
			if(X ∩ Y is nonempty and Y \ X is nonempty):
				#si Y != X y la interseccion existe
				#(Hay estados en Y que pueden llegar a W)
				#Reemplazo Y por su split
				P.remove(Y)
				P.add(X ∩ Y)
				P.add(Y \ X)
				if Y is in W:
					W.remove(Y)*/
	//P = {F, Q/F} particion
	//W = {F, Q/F} dinstinguishers
	//while(!W.empty())
	//A = W.jb

	//TODO
	return *this;
}
