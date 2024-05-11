#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <vector>
# include <string>

namespace utils
{

using svector = std::vector<std::string>;

svector	splitLine(const std::string& line);
int			toInt(const std::string& str);

std::string::const_iterator	search(std::string::const_iterator start, \
									std::string::const_iterator end, \
									char key);
std::string::const_iterator	search(std::string::const_iterator start, \
									std::string::const_iterator end, \
									const std::string& key);

std::string	extractString(std::string::const_iterator start, \
							std::string::const_iterator end, char key);
std::string	extractString(std::string::const_iterator start, \
							std::string::const_iterator end);


}

#endif