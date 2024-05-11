#ifndef FUNCTIO_HPP
# define FUNCTIO_HPP

# include <iostream>
# include <vector>
# include <string>

# include "Utils.hpp"

using svector = std::vector<std::string>;


class Functio {
	public:
		std::string	_name;
		std::string	_return_type;
		std::vector<std::string> _param_types;
		std::vector<std::string> _body;

	public:
		Functio(const std::string& declaration);
		~Functio() = default;
};

#endif