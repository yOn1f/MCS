#ifndef __TRANSITION_HPP__
#define __TRANSITION_HPP__

#include "Utils.hpp"

class Transition
{
	
	public:
		Transition();
		Transition(std::string o, char s, std::string t): origin(o), symbol(s), target(t) {}

		/* Getters */
		std::string get_origin() const {return origin;}
		char get_symbol() const {return symbol;}
		std::string get_target() const {return target;}

		friend std::ostream& operator<<(std::ostream&, const Transition);

	private:
		std::string origin;
		char symbol;
		std::string target;
};
#endif