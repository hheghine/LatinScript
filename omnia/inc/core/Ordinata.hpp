#ifndef ORDINATA_HPP
# define ORDINATA_HPP

# include "LatinScript.hpp"

using obj_vec = std::vector<Object *>;
using svector = std::vector<std::string>;

class Ordinata {
	public:
		obj_vec		_array;
		std::string	_name;
		std::string	_type;

	public:
		explicit Ordinata(const std::string& init);
		~Ordinata();

	public:
		void	setValue(int idx, const std::string& rhs);
		void	setValue(int idx, const Object* rhs);
		Object*	getValue(int idx);
		Object*	createVar();

		std::string	__string();

	private:
		void	_init(const std::string& init);
};

#endif