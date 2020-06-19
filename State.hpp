#ifndef __STATE_HPP__
#define __STATE_HPP__

#include "Transition.hpp"

class State {
	public:
		State(std::string num, bool entry = false, bool exit = false) : state_num(num), is_entry(entry), is_exit(exit) {}

		void read_transitions(std::istream&, std::list<Transition>&);
		void display_transitions();

	private:
		std::string state_num;
		bool is_entry;
		bool is_exit;
		std::list<Transition> transitions;		
};
#endif