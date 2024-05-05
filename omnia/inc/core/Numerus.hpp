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

		/* allocates a new value that is equal to the value of rhs */
		void	setValue(const Object* rhs);
		/* casts rhs and allocates a value */
		void	setValue(const std::string& rhs);
		/* gets the allocated value pointer */
		void	setValue(void* ptr);

		void	addition(const std::string& rhs);
		void	addition(const Object* ob);

		void	substraction(const std::string& rhs);
		void	substraction(const Object* ob);

		Object*	clone() const;

		std::string	__string() const;
};

#endif