#ifndef __STATE_HPP__
#define __STATE_HPP__

#include "Transition.hpp"

class State {
	public:
		State(std::string num, bool entry = false, bool exit = false) : state_num(num), is_entry(entry), is_exit(exit) {}

		void read_transitions(std::istream&, std::list<Transition>&);
		void display_transitions(std::ostream&) const;
		void add_transition(const Transition&);

		std::string get_num() const { return state_num; }
		bool get_entry_status() const { return is_entry; }
		bool get_exit_status() const { return is_exit; }
		const std::list<Transition>& get_transitions() const { return transitions; }
		std::list<Transition> get_epsilon_transitions() const;
		const std::list<std::string> get_targets() const;

		void set_entry_status(const bool entry_status) { is_entry += entry_status; }
		void set_exit_status(const bool exit_status) { is_exit += exit_status; }

	private:
		std::string state_num;
		bool is_entry;
		bool is_exit;
		std::list<Transition> transitions;		
};
#endif