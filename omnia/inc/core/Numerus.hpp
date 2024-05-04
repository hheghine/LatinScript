#ifndef NUMERUS_HPP
# define NUMERUS_HPP

# include "Object.hpp"

class Object;

class Numerus : public Object {
	public:
		Numerus();
		Numerus(Object* ptr);
		~Numerus();

		void		setValue(void* ptr);
		std::string	__string() const;
};

#endif