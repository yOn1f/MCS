#include "FA.hpp"

// TODO: fix display in verifications()

int main()
{
	FA FA;
	std::string nbr_to_test;

	do{
		std::cout << "Which FA do you want to use? ";
		std::cin >> nbr_to_test;

		/* Composing reading and writing paths */
		const std::string reading_path = "Tests/" + nbr_to_test + ".txt";
		const std::string writing_path = "Execution_traces/" + nbr_to_test + ".txt";

		try
		{
			FA.read_from_file(reading_path);
			std::cout <<  std::endl << "Original automaton:" << std::endl;
			FA.display();
			std::cout << std::endl;

			bool is_async, is_det, is_complete;
			FA.verifications(is_async, is_det, is_complete);
		}
		catch (std::string const& s)
		{
			std::cerr << "ERROR: " << s << std::endl << std::endl;
		}
	}while(go_again() == true);
	return 0;
}