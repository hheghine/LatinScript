#ifndef FUNCTIO_HPP
# define FUNCTIO_HPP

# include "LatinScript.hpp"
# include "ScriptRunner.hpp"

using namespace ls;

/*---------------------FUNCTIO---------------------*/

class Functio : public LatinScript {
	public:
		std::string					_name;
		std::string					_return_type;
		svector						_param_types;
		svector						_body;
		Object*						_return;

		svector						_var_names;

		static int					_in_function;

		// std::stack<std::unordered_map<std::string, Object *>> _args;

	public:
		Functio(const std::string& declaration);
		~Functio();

	public:
		void	setBody(const svector& body);
		void	main_loop();
		void	exec();

	private:
		void	letsGo(const std::string& declaration);

		void	handleAssignment(const svector& vec, const_iterator lhs, const_iterator& it);
		void	handleOperator(const svector& vec, const_iterator lhs, const_iterator& it);

		Object*	createVar(const std::string& type);
		void	handleReturn(const svector& vec);
};

#endif