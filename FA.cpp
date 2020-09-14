#include "FA.hpp"

/*------------------------------------------------------------- Reading methods -------------------------------------------------------------*/
void FA::read_from_file(const std::string& reading_path)
{
	std::ifstream my_FA(reading_path); /* Opening the file and creating a input stream */

	if(my_FA) /* Testing if the opening of the file succeeded */
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
}

void FA::fill_states(std::ifstream& my_FA, int nb_transitions)
{
	char origin, target;
	char symbol;
	std::list<Transition> to_match;

	/* States are numbered from 0 to nb_states - 1 */
	for(int i = 0 ; i < nb_states ; i++)
	{
		std::string num = int_to_string(i);

		bool is_entry = (std::find(initial_states.begin(), initial_states.end(), num) != initial_states.end()) ? true : false;
		bool is_exit = (std::find(final_states.begin(), final_states.end(), num) != final_states.end()) ? true : false;

		State *new_state = new State(num, is_entry, is_exit);
		states.push_back(*new_state);
	}

	for(int i = 0 ; i < nb_transitions ; i++)
	{
		my_FA >> origin >> symbol >> target;
		Transition *new_transition = new Transition(std::string(1, origin), symbol, std::string(1, target)); //using string consructor to convert char into string
		to_match.push_back(*new_transition);
	}

	std::list<State>::iterator i;
	for(i = states.begin() ; i != states.end() ; ++i)
		i->read_transitions(my_FA, to_match);
}

/*------------------------------------------------------------- Displaying method -------------------------------------------------------------*/
void FA::display(std::ofstream& exec_file) const
{
	std::list<std::string> to_display;

	/* Displaying the initial states */
	exec_file << "Initial states: ";
	for(auto i : initial_states)
	{
		to_display.push_back(i);
	}
	exec_file << join(to_display, " ") << std::endl;
	to_display.clear();

	/* Displaying the final states */
	exec_file << "Final states: ";
	for(auto i : final_states)
	{
		to_display.push_back(i);
	}
	exec_file << join(to_display, " ") << std::endl;

	/* Displaying the transitions */
	exec_file << "Transitions: " << std::endl;
	for(auto i : states)
		i.display_transitions(exec_file);
}

/*------------------------------------------------------------- Verification methods -------------------------------------------------------------*/
void FA::verifications(bool& is_async, bool& is_det, bool& is_complete, std::ofstream& exec_file) const
{
	std::list<std::string> to_display; /* List to be sent to join() for proper layout */

	/* Asynchronism test */
	if(this->is_asynchronous())
	{
		exec_file << "This automaton has epsilon transitions (";
		for(auto i : this->get_states())
		{
			for(auto j : i.get_transitions())
			{
				if(j.get_symbol() == EPSILON_SYMBOL){
					to_display.push_back(j.get_origin() + j.get_symbol() + j.get_target()); /* Transforms a Transition into a string */
				}
			}
		}
		exec_file << join(to_display, ", ") << "). It is asynchronous." << std::endl;
		is_async = true;
		to_display.clear();
	}

	/* Determinism test */
	int det_or_not = this->is_deterministic();
	if(det_or_not == MORE_THAN_ONE_ENTRY)
	{
		exec_file << "This automaton has more than one entry (states ";
		for(auto i : this->get_entries())
			to_display.push_back(i);

		exec_file << join(to_display, ", ") << "). It is not deterministic." << std::endl;
		is_det = false;	
	}
	else if(det_or_not == SEVERAL_TRANSITION_SAME_SYMBOL)
	{
		exec_file << "This automaton has several transitions labeled with the same symbol. It is not deterministic." << std::endl;
		is_det = false;
	}
	else
		exec_file << "This automaton is deterministic." << std::endl;

	/* Completion test */
	std::string state_nbr;
	if(!(this->is_complete(state_nbr)))
	{
		exec_file << "State " << state_nbr << " doesn't have at least 1 transition by symbol in the alphabet so this FA is not complete." << std::endl;
		is_complete = false;
	}
	else
	{
		exec_file << "This automaton is complete." << std::endl;
		is_complete = true;
	}
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
				for(auto j = s.get_transitions().begin() ; j != i ; ++j)
				{
					if((*i).get_origin() == j->get_origin() && (*i).get_symbol() == j->get_symbol())
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
				if(i.get_origin() == s.get_num() && std::find(symbols.begin(), symbols.end(), i.get_symbol()) == symbols.end())
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

/*------------------------------------------------------------- Modification methods -------------------------------------------------------------*/
void FA::synchronization() const
{
	std::list<Transition> all_epsilon_transitions; /* allows return by reference if the list */
	this->get_all_epsilon_transitions(all_epsilon_transitions); /* is very long */

	std::list<Transition> outcoming;
	std::list<Transition>::iterator i;

	for(i = all_epsilon_transitions.begin() ; i != all_epsilon_transitions.end() ; ++i)
	{
		// TODO: find something shorter for this->get_state_from_num(i->get_target())
		outcoming = this->get_state_from_num(i->get_target()).get_transitions(); /* getting transitions outcoming of target state of i */

		for(auto j : outcoming)
		{
			if((j.get_symbol() == '*') && (j.get_origin() != j.get_target())) /* don't take transitions s*s into account */
				all_epsilon_transitions.push_back(j);

			j.set_target(i->get_target());
			std::cout << "Before call: " << this->get_state_from_num(i->get_target()).get_transitions().size() << std::endl;
			this->get_state_from_num(i->get_target()).add_transition(j); /* adding them to the origin state of i */
			std::cout << "After call: " << this->get_state_from_num(i->get_target()).get_transitions().size() << std::endl;
		}

		/* setting entry and exit status of the origin state */
		this->get_state_from_num(i->get_origin()).set_entry_status(this->get_state_from_num(i->get_target()).get_entry_status());
		this->get_state_from_num(i->get_origin()).set_exit_status(this->get_state_from_num(i->get_target()).get_exit_status());

		all_epsilon_transitions.erase(i);
	}
}

void FA::get_all_epsilon_transitions(std::list<Transition>& all_epsilon_transitions) const
{
	for(auto i : states)
		all_epsilon_transitions += i.get_epsilon_transitions();
}

State FA::get_state_from_num(const std::string& state_num) const
{
	std::list<State>::const_iterator i = states.begin();
	while(i->get_num() != state_num)
		++i;

	return *i;
}

// State#get_transitions() pour avoir transitions sortantes de l'état target dans la transition i
// puis les appliquer à l'état origine de i et les ajouter à l'état en question et si epsilon ajouter à liste epsilon_transitions (1*1, 2*2 .... impossible)
// delete * transition
// si target = sortie alors origin = sortie et inversement