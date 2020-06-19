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
		std::cout << "Couldn't open the file." << std::endl;
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