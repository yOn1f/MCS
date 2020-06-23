#include "Utils.hpp"

std::string int_to_string(int n)
{
    std::ostringstream os;

    os << n;
    
    return os.str();
}

bool go_again()
{
	std::string again;
	bool valid_answer = false;

	do
	{
		std::cout << "Wanna go again? (YES/NO) ";
		std::cin >> again;
		std::transform(again.begin(), again.end(), again.begin(), toupper);

		if(again == "YES")
		{
			valid_answer = true;
			system(CLEAR);
			return true;
		}
		else if(again == "NO")
		{
			valid_answer = true;
			return false;
		}
		else
			system(CLEAR);
	}while(valid_answer == false);
}