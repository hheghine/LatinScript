#ifndef FUNCTIO_HPP
# define FUNCTIO_HPP

# include <iostream>
# include <vector>
# include <string>
# include <unordered_map>

# include "Object.hpp"
# include "Numerus.hpp"
# include "Utils.hpp"

using svector = std::vector<std::string>;


class Functio {
	public:
		std::string					_name;
		std::string					_return_type;
		std::vector<std::string>	_param_types;
		std::vector<std::string>	_body;
		Object*						_return;

		std::unordered_map<std::string, Object *> vars;

	public:
		Functio(const std::string& declaration);
		~Functio();

	private:
		Object*	createVar(const std::string& type);
};

#endif