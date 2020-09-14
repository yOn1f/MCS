#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <list>

#define NO_MATCH std::string::npos
#define EXEC_TRACES_DIR_NAME "Execution_traces\\"

#if defined(_WIN32) || defined(_WIN64) /* Windows */
#define CLEAR "cls"
#define OPEN_FILE_COMMAND "start "
#else /* Other OS */
#define CLEAR "clear"
#define OPEN_FILE_COMMAND "open "
#endif

std::string int_to_string(int);
bool go_again();
void check_result(const std::string&);

template <typename T>
std::string join(std::list<T>& l, std::string sep)
{
	std::string result;
	typename std::list<T>::const_iterator i;

	for(auto i : l)
	{
		result = result + i;
		if(i != l.back())
			result += sep;
	}

	return result;
}

template <typename T>
void operator+=(std::list<T>& lhs, const std::list<T>& rhs)
{
      for(auto i : rhs)
      	lhs.push_back(i);
}
#endif