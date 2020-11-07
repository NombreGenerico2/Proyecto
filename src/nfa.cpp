#include <queue>
#include <set>

#include <dfa.hpp>
#include <nfa.hpp>

dfa nfa::powerset()
{
	dfa d;

	size_t state_n = 0;

	std::map<std::set<int>, int> visited;
	std::queue<std::pair<std::set<int>, int>> q;

	d.initial = state_n;
	q.push({{initials.begin(), initials.end()}, state_n++});

	while(!q.empty())
	{
		dfa::state new_state;

		for(int i: {0, 1})
		{
			std::set<int> new_state_set;

			// Fill set with old transitions.
			for(int j: q.front().first)
			{
				if(states[j].accepting)
					new_state.accepting = true;

				auto range = states[j].transitions.equal_range(i);

				for(auto k = range.first; k != range.second; ++k)
				{
					new_state_set.insert(k->second);
				}
			}

			int state_to;
			auto it = visited.find(new_state_set);

			if(it == visited.end())
			{
				state_to = state_n;
				q.push({new_state_set, state_n++});
			}
			else
			{
				state_to = it->second;
			}

			new_state.transitions[i] = state_to;
		}

		d.states.push_back(new_state);
		visited.insert(q.front());
		q.pop();
	}

	return d;
}
