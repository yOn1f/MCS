#ifndef __FA_HPP__
#define __FA_HPP__

#include <fstream>
#include <algorithm>

#include "State.hpp"

#define NB_LINES_TO_READ_IN_FILE 6

class FA {
	public:
		/* Reading methods */
		void read_from_file(const std::string&);
		void read_entry_exits(std::ifstream&, std::list<std::string>&);
		void fill_states(std::ifstream&, int);

		/* Displaying method */
		void display() const;

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