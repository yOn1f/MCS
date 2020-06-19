#include "Transition.hpp"

/*------------------------------------------------------------- Utils -------------------------------------------------------------*/
std::string int_to_string(int n)
{
    std::ostringstream os;

    os << n;
    
    return os.str();
}

std::ostream& operator<<(std::ostream& os, const Transition transition)
{
	os << transition.origin << transition.symbol << transition.target;
	return os;
}