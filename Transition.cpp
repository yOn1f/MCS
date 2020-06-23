#include "Transition.hpp"

std::ostream& operator<<(std::ostream& os, const Transition transition)
{
	os << transition.origin << transition.symbol << transition.target;
	return os;
}