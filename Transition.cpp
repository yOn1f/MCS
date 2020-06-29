#include "Transition.hpp"

std::ofstream& operator<<(std::ofstream& ofs, const Transition& transition)
{
	ofs << transition.origin << transition.symbol << transition.target;
	return ofs;
}