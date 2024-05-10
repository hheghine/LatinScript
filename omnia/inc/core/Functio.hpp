#ifndef FUNCTIO_HPP
# define FUNCTIO_HPP

# include <iostream>
# include <vector>
# include <string>

class Functio {
	public:
		std::string	_name;
		std::string	_return_type;
		std::vector<std::string> _param_types;
		std::vector<std::string> _body;

	public:
		// Functio(std::string name);
		~Functio() = default;
};

#endif