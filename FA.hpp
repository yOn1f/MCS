#ifndef __FA_HPP__
#define __FA_HPP__

#include "State.hpp"
#include <typeinfo>

#define NB_LINES_TO_READ_IN_FILE 6
#define EPSILON_SYMBOL '*'
#define MORE_THAN_ONE_ENTRY 1
#define SEVERAL_TRANSITION_SAME_SYMBOL 2

class FA {
	public:
		/* Reading methods */
		void read_from_file(const std::string&);
		void read_entry_exits(std::ifstream&, std::list<std::string>&);
		void fill_states(std::ifstream&, int);

		/* Displaying method */
		void display(std::ofstream&) const;

		/* Verification methods */
		void verifications(bool&, bool&, bool&, std::ofstream&) const;
		bool is_asynchronous() const;
		int is_deterministic() const;
		bool is_complete(std::string&) const;

		/* Modification methods */
		void synchronization() const;
		std::string& find_last_target(const std::list<Transition>&, const Transition&) const;

		/* Getters */
		std::list<std::string> get_entries() const { return initial_states; }
		std::list<State> get_states() const { return states; }
		void get_all_epsilon_transitions(std::list<Transition>&) const;
		State get_state_from_num(const std::string&) const;
		
	private:
		/* Attributes */
		int nb_symbols_alphabet;
		int nb_states;
		int nb_transitions;
		std::list<std::string> initial_states;
		std::list<std::string> final_states;
		std::list<State> states;
};
#endif