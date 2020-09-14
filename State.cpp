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

void State::display_transitions(std::ostream& exec_file) const
{
	for(auto i : transitions)
		exec_file << i << std::endl;
}

void State::add_transition(const Transition&_new)
{
	auto i = transitions.begin();

	while(i != transitions.end())
	{
		if(i->get_symbol() < _new.get_symbol())
		{
			++i;
		}
		transitions.insert(i, _new);
		i = transitions.end();
	}
}

const std::list<std::string> State::get_targets() const
{
	std::list<std::string> targets;

	for(auto i : transitions)
		 targets.push_back(i.get_target());

	return targets;
}

std::list<Transition> State::get_epsilon_transitions() const
{
	std::list<Transition> epsilon_transitions;

	for(auto i : transitions)
	{
		if(i.get_symbol() == '*')
			epsilon_transitions.push_back(i);
	}

	return epsilon_transitions;
}