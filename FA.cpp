#include "FA.hpp"

/*------------------------------------------------------------- Reading methods -------------------------------------------------------------*/
void FA::read_from_file(const std::string& reading_path)
{

	std::ifstream my_FA(reading_path); /* opening the file and creating a input stream */

	if(my_FA) /* testing if the opening of the file succeeded */
	{
		my_FA >> nb_symbols_alphabet;

		my_FA >> nb_states;

		/* Reading the initial states */
		read_entry_exits(my_FA, initial_states);

		/* Reading the final states */
		read_entry_exits(my_FA, final_states);

		my_FA >> nb_transitions;
		fill_states(my_FA, nb_transitions);
	}
	else
		throw std::string("Could not open the file.");
}

void FA::read_entry_exits(std::ifstream& fs, std::list<std::string>& l)
{
	int nb_states_to_read;
	std::string state_num;

	fs >> nb_states_to_read;

	for(int i = 0 ; i < nb_states_to_read ; i++)
	{
		fs >> state_num;
		l.push_back(state_num);
	}

	/* States are numbered from 0 to nb_states - 1 */
	for(int i = 0 ; i < nb_states ; i++)
	{
		std::string num = int_to_string(i);

		bool is_entry = (std::find(initial_states.begin(), initial_states.end(), num) != initial_states.end()) ? true : false;
		bool is_exit = (std::find(final_states.begin(), final_states.end(), num) != final_states.end()) ? true : false;

		State *new_state = new State(num, is_entry, is_exit);
		states.push_back(*new_state);
	}
}

void FA::fill_states(std::ifstream& my_FA, int nb_transitions)
{

	char origin, target;
	char symbol;
	std::list<Transition> to_match;

	for(int i = 0 ; i < nb_transitions ; i++)
	{
		my_FA >> origin >> symbol >> target;
		Transition *new_transition = new Transition(std::string(1, origin), symbol, std::string(1, target)); //using string consructor to convert char into string
		to_match.push_back(*new_transition);
	}

	std::list<State>::iterator i;
	for(i = states.begin() ; i != states.end() ; ++i)
		(*i).read_transitions(my_FA, to_match);
}

/*------------------------------------------------------------- Displaying method -------------------------------------------------------------*/
void FA::display() const
{
	/* Displaying the initial states */
	std::cout << "Initial states: ";
	for(auto i : initial_states)
		std::cout << i << " ";
	std::cout << std::endl;

	/* Displaying the final states */
	std::cout << "Final states: ";
	for(auto i : final_states)
		std::cout << i << " ";
	std::cout << std::endl;

	/* Displaying the transitions */
	std::cout << "Transitions: " << std::endl;
	for(auto i : states)
		i.display_transitions();
}


/*------------------------------------------------------------- Verification methods -------------------------------------------------------------*/
void FA::verifications(bool& is_async, bool& is_det, bool& is_complete) const
{
	/* Asynchronism test */
	if(this->is_asynchronous())
	{
		std::cout << "This automaton has epsilon transitions (";
		for(auto i : this->get_states())
		{
			for(auto j : i.get_transitions())
			{
				if(j.get_symbol() == EPSILON_SYMBOL)
					std::cout << j << ", ";
			}
		}
		std::cout << "). It is asynchronous." << std::endl;
	}

	/* Determinism test */
	int det_or_not = this->is_deterministic();
	if(det_or_not == MORE_THAN_ONE_ENTRY)
	{
		std::cout << "This automaton has more than one entry (states ";
		for(auto i : this->get_entries())
			std::cout << i << ", ";
		std::cout << "). It is not deterministic." << std::endl;
	}
	else if(det_or_not == SEVERAL_TRANSITION_SAME_SYMBOL)
	{
		std::cout << "This automaton has several transitions labeled with the same symbol. It is not deterministic." << std::endl;
		// TODO: display transitions with same symbol
	}
	else
		std::cout << "This automaton is deterministic." << std::endl;

	/* Completion test */
	std::string state_nbr;
	if(not(this->is_complete(state_nbr)))
	{
		std::cout << "State " << state_nbr << " doesn't have at least 1 transition by symbol in the alphabet so this FA is not complete." << std::endl;
	}
	else
		std::cout << "This automaton is complete." << std::endl;
}

bool FA::is_asynchronous() const
{
	for(auto s : states)
	{
		for(auto t : s.get_transitions())
		{
			if(t.get_symbol() == '*')
				return true;
		}
	}

	return false;
}

int FA::is_deterministic() const
{
	if(initial_states.size() > 1)
		return MORE_THAN_ONE_ENTRY;
	else
	{
		for(auto s : states)
		{
			for(auto i = s.get_transitions().begin() ; i != s.get_transitions().end() ; ++i)
			{
				for(auto j = ++i ; j != s.get_transitions().end() ; ++j)
				{
					if((*i).get_origin() == j->get_origin() and (*i).get_symbol() == j->get_symbol())
						return SEVERAL_TRANSITION_SAME_SYMBOL;
				}
			}
		}
	}
	return 0;
}

bool FA::is_complete(std::string& state_nbr) const
{
	std::vector<std::string> CS; /* CS means checked states */

	for(auto s : states)
	{
		if(std::find(CS.begin(), CS.end(), s.get_num()) == CS.end()) /* We'll look at a state only if we haven't already */
		{
			std::vector<char> symbols;

			for(auto i : s.get_transitions())
			{
				/* We look if the state has at least 1 transition labeled with eachs symbol of the alphabet */
				if(i.get_origin() == s.get_num() and std::find(symbols.begin(), symbols.end(), i.get_symbol()) == symbols.end())
					symbols.push_back(i.get_symbol());
			}

			if(symbols.size() != nb_symbols_alphabet)
			{
				state_nbr = s.get_num();
				return false;
			}

			CS.push_back(s.get_num()); /* Current state has been checked and has at least 1 transition by symbol in the alphabet */
		}
	}

	return true;
}