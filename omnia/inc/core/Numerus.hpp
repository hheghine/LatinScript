#ifndef NUMERUS_HPP
# define NUMERUS_HPP

# include "Object.hpp"
# include <sstream>

class Object;

class Numerus : public Object {
	public:
		Numerus();
		Numerus(Object* ptr);
		~Numerus();

		void		setValue(const std::string& rhs);
		void		setValue(void* ptr);
		std::string	__string() const;
};

#endif