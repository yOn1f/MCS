#include "State.hpp"

void State::read_transitions(std::istream& fs, std::list<Transition>& to_match)
{
	for(auto it = to_match.begin() ; it != to_match.end() ;)
	{
		if(it->get_origin() == state_num)
		{
			transitions.push_back(*it);
			it = to_match.erase(it);
		}
		else
			++it;
	}
}

void State::display_transitions(std::ofstream& exec_file) const
{
	for(auto i : transitions)
		exec_file << i << std::endl;
}