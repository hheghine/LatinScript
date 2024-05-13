#ifndef FUNCTIO_HPP
# define FUNCTIO_HPP

# include "LatinScript.hpp"

using namespace ls;

class Functio : public LatinScript {
	public:
		std::string					_name;
		std::string					_return_type;
		std::vector<std::string>	_param_types;
		std::vector<std::string>	_body;
		Object*						_return;

	public:
		Functio(const std::string& declaration);
		~Functio();

	public:
		void	setBody(const svector& body);
		void	main_loop();

	private:
		void	letsGo(const std::string& declaration);

		Object*	createVar(const std::string& type);
		void	handleReturn(const svector& vec);
};

#endif