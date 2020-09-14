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

	do
	{
		std::cout << "Wanna go again? (YES/NO) ";
		std::cin >> again;
		std::transform(again.begin(), again.end(), again.begin(), toupper);
		system(CLEAR);
	}while(again != "YES" and again != "NO");

	if(again == "YES")
		return true;
	else
		return false;
}

void check_result(const std::string& nbr_to_test)
{
	std::string check;

	std::cout << "The result has been written in a .txt file. Do you want to open it? (YES/NO) ";
	std::cin >> check;

	std::transform(check.begin(), check.end(), check.begin(), toupper);
	if(check == "YES")
	{
		const std::string show_result = std::string(OPEN_FILE_COMMAND) + EXEC_TRACES_DIR_NAME +  nbr_to_test + ".txt";
		system(show_result.c_str());
		system(CLEAR);
	}
}

/* Note: Line 49 --> can't do (char* + char *) but ((string + char*) + char*) = (string + char*) = string is ok */
/* Note: Line 50 --> the system function only accepts char* arguments so you must transform the string back to char* with c_str() */