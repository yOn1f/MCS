#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>

#define NO_MATCH std::string::npos

#if defined(_WIN32) || defined(_WIN64) /* Windows */
#define CLEAR "cls"
#else /* Other OS */
#define CLEAR "clear"
#endif

std::string int_to_string(int);
bool go_again();
#endif