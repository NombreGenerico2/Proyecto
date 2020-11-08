#include <dfa.hpp>
#include <matrix.hpp>

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

nfa dfa::reverse_edges()
{
	nfa n;

	n.states = std::vector<nfa::state>(states.size());
	n.states[initial].accepting = true;

	for(size_t i = 0; i < states.size(); ++i)
	{
		if(states[i].accepting)
			n.initials.push_back(i);

		for(size_t j = 0; j < states[i].transitions.size(); ++j)
		{
			n.states.at(states.at(i).transitions.at(j)).transitions.insert({j, i});
			//std::cerr
			//	<< "\tp: " << states.at(i).transitions.at(j) << '\n'
			//	<< "\ta: " << j << '\n'
			//	<< "\tq: " << i << '\n'
			//	<< '\n'
			//;
		}
	}
	//std::cerr << '\t' << n.states.size() << '\n';

	return n;
}

dfa dfa::brzozowski()
{
	//nfa n = reverse_edges();
	//std::cerr << n;
	//return n.powerset();
	return reverse_edges().powerset().reverse_edges().powerset();
}
void dfa::stateEquivalence()
{
	using namespace std;
	using ll = long long;
	using vi = std::vector<int>;
	using ii = pair< int,int >;

	int n = states.size();



	bool distinguidos[n][n];


	for (int i = 0 ; i < n ; i++){
		for (int j = 0 ; j < n; j++){
			distinguidos[i][j] = 0;	
		}
	}
	
		for (int i = 0 ; i < n ; i++){
		for (int j = 0 ; j < n; j++){
			cout<< distinguidos[i][j]<<" ";	
		}
		cout<<endl;
	}
	cout<<endl;

	for(int i = 0; i < n; i++){
        if(states[i].accepting){
            for(int j = i + 1; j < n; j++){
                if(!states[j].accepting){
                    //lleno la fila que le corresponde 
                    //a este estado de aceptacion
                    distinguidos[i][j] = true;
                }
            }
            for(int k = i + 1; k < n; k++){
                if(!states[k].accepting){
                    //lleno la columna que le corresponde
                    //a este estado de aceptacion
                    distinguidos[k][i] = true;
                }
            }
        }
    }
		for (int i = 0 ; i < n ; i++){
		for (int j = 0 ; j < n; j++){
			cout<< distinguidos[i][j]<<" ";	
		}
		cout<<endl;
	}
	//Estados finales
	/*
    for(int i = 0; i < n; i++){
    if(states[i].accepting){
        for(int j = i + 1; j < n; j++){
            if(!accept[j]){
                //lleno la fila que le corresponde 
                //a este estado de aceptacion
                distinguidos[i][j] = true;
            }
        }
        for(int k = i; k < n; k++){
            if(!accept[k]){
                //lleno la columna que le corresponde
                //a este estado de aceptacion
                distinguidos[k][i] = true;
            	}
        	}
    	}
	}*/
	
	//int modificaciones = 0;

	
}
