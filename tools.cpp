#include <iostream>
#include <vector>
#include <sstream>
#include "tools.hpp"

void split_string(std::string const &str, const char delim,
                  std::vector<std::string> &vec_of_strings)
{
    std::string strings_to_vector;

    std::stringstream string_stream(str);

    while (std::getline(string_stream, strings_to_vector, delim))
    {
        vec_of_strings.push_back(strings_to_vector);
    }
}