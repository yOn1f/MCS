#include "FA.hpp"

int main()
{
	std::string nbr_to_test;

	do{
		FA FA;
		
		std::cout << "Which FA do you want to use? ";
		std::cin >> nbr_to_test;

		/* Composing reading and writing paths */
		const std::string reading_path = "Tests/" + nbr_to_test + ".txt";
		const std::string writing_path = "Execution_traces/" + nbr_to_test + ".txt";

		try
		{
			std::ofstream exec_file(writing_path);
			FA.read_from_file(reading_path);

			exec_file << "Original automaton:" << std::endl;
			FA.display(exec_file);
			exec_file << std::endl;

			bool is_async, is_det, is_complete;
			FA.verifications(is_async, is_det, is_complete, exec_file);
			
			FA.synchronization();
			exec_file << std::endl;
			FA.display(exec_file);

			exec_file.close();
			check_result(nbr_to_test);
		}
		catch (std::string const& s)
		{
			std::cerr << "ERROR: " << s << std::endl << std::endl;
		}
	}while(go_again() == true);
	return 0;
}