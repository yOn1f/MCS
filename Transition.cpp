#include "Transition.hpp"

std::ostream& operator<<(std::ostream& ofs, const Transition& transition)
{
	ofs << transition.origin << transition.symbol << transition.target;
	return ofs;
}