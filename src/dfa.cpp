#include <dfa.hpp>

#include <algorithm>
#include <iterator>
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
nfa dfa::reverse_edges() const
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

dfa dfa::brzozowski() const
{
	return reverse_edges().powerset().reverse_edges().powerset();
}
//O(n^4)
matrix dfa::stateEquivalence() const
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
matrix dfa::stateEquivalence2() const
{
	size_t n = states.size();
	std::multimap<std::pair<int, int>, std::pair<int, int>> p_list;

	// O(n^2): n <- |Q|
	for(size_t p = 0; p < states.size(); ++p)
	{
		for(size_t q = 0; q < states.size(); ++q)
		{
			for(int a: {0, 1})
			{
				int r = states[p].transitions[a];
				int s = states[q].transitions[a];

				p_list.insert({{r,s},{p,q}});
			}
		}
	}

	matrix m(n);
	std::queue<std::pair<int, int>> to_check;

	for(size_t i = 0; i < n; i++)
	{
		if(states[i].accepting)
		{
			for(size_t j = 0; j < i; j++)
			{
				if(!states[j].accepting){
					m(i,j) = distinguishable;
					m(j,i) = distinguishable;
					to_check.push({i, j});
					to_check.push({j, i});
				}
			}
		}
	}

	//for(size_t i = 0  ; i < n ;i++){
	//	for(size_t j = 0 ; j < n; j++){
	//		if (i == j)continue;
	//		for(int symbol = 0 ; symbol <= 1 ; symbol++){
	//			if(m(states[i].transitions[symbol], states[j].transitions[symbol]) && m(i,j) == equivalent){
	//				m(i,j) = distinguishable;
	//				m(j,i) = distinguishable;

	//				to_check.push({i, j});
	//				to_check.push({j, i});
	//			}
	//		}
	//	}
	//}

	while(!to_check.empty())
	{
		auto [p, q] = to_check.front();

		if(m(p, q) != distinguishable)
		{
			to_check.push({p, q});
			m(p, q) = distinguishable;
		}

		to_check.pop();
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

	v[state] = true;

	return v;
}

std::set<std::set<int>> dfa::make_partition() const
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

dfa dfa::huffman(partition_t p) const
{
	dfa d;
	int state_c = 0;

	std::map<int, int> old2new;

	std::set<std::set<int>> set_set;

	switch(p)
	{
		case partition_t::matrix1:
		case partition_t::matrix2:
			set_set = make_partition();
			break;

		case partition_t::hopcroft:
			set_set = hopcroft();
			break;
	}

	for(const auto& s: set_set)
	{
		d.states.push_back(state{});
		auto& new_state = *(d.states.rbegin());

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
std::set<std::set<int>> dfa::hopcroft() const
{
	auto can_reach = [this](const std::set<int>& A, int c) -> std::set<int>
	{
		std::set<int> s;

		int i = 0;
		for(const auto& state: states)
		{
			if(A.find(state.transitions[c]) != A.end())
				s.insert(i);

			i++;
		}

		return s;
	};

	auto partition = [this]() -> std::set<std::set<int>>
	{
		std::set<int> no_accepting;
		std::set<int> accepting;

		for(size_t i = 0; i < states.size(); ++i)
		{
			if(states[i].accepting)
			{
				accepting.insert(i);
			}
			else
			{
				no_accepting.insert(i);
			}
		}

		return {accepting, no_accepting};
	};

	auto intersection = [](const std::set<int>& a, const std::set<int>& b) -> std::set<int>
	{
		std::set<int> s;

		std::set_intersection(
			a.begin(),
			a.end(),
			b.begin(),
			b.end(),
			std::inserter(s, s.end())
		);

		return s;
	};

	auto diff = [](const std::set<int>& a, const std::set<int>& b) -> std::set<int>
	{
		std::set<int> s;

		std::set_difference(
			a.begin(),
			a.end(),
			b.begin(),
			b.end(),
			std::inserter(s, s.end())
		);

		return s;
	};


	auto P = partition();
	auto W = P;

	while(!W.empty())
	{
		auto A = *W.begin();
		W.erase(W.begin());

		for(int c: {0, 1})
		{
			std::set<int> X = can_reach(A, c);
			for(const auto& Y: P)
			{
				auto yx_inter = intersection(X, Y);
				auto yx_diff = diff(Y, X);

				if(!yx_inter.empty() && !yx_diff.empty())
				{
					P.erase(Y);
					P.insert(yx_inter);
					P.insert(yx_diff);

					if(W.find(Y) != W.end())
					{
						W.erase(Y);
						W.insert(yx_inter);
						W.insert(yx_diff);
					}
					else
					{
						if(yx_inter.size() <= yx_diff.size())
						{
							W.insert(yx_inter);
						}
						else
						{
							W.insert(yx_diff);
						}
					}
				}
			}
		}
	}

	return P;
}
