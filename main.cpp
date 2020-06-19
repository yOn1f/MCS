#include <iostream>
#include "Fa.hpp"

int main()
{
	std::string again;

	FA FA;
	std::string nbr_to_test;

	std::cout << "Which FA do you want to use? ";
	std::cin >> nbr_to_test;

	/* Composing reading and writing paths */
	const std::string reading_path = "Tests/" + nbr_to_test + ".txt";
	const std::string writing_path = "Execution_traces/" + nbr_to_test + ".txt";

	FA.read_from_file(reading_path);

	std::cout << std::endl;
	FA.display();

	return 0;
}