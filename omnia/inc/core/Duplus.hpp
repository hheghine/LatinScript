#ifndef DUPLUS_HPP
# define DUPLUS_HPP

# include "Object.hpp"
# include "Utils.hpp"

class Object;

class Duplus : public Object {
	public:
		Duplus();
		explicit Duplus(Object* ptr);
		~Duplus();

		void	setValue(const Object* rhs);
		void	setValue(const std::string& rhs);
		void	setValue(void* ptr);

		void	addition(const std::string& rhs);
		void	addition(const Object* rhs);

		void	substraction(const std::string& rhs);
		void	substraction(const Object* rhs);

		void	multiplication(const std::string& rhs);
		void	multiplication(const Object* rhs);

		void	division(const std::string& rhs);
		void	division(const Object* rhs);

		bool	isEqual(const std::string& rhs);
		bool	isEqual(const Object* rhs);

		bool	isGreater(const std::string& rhs);
		bool	isGreater(const Object* rhs);

		bool	isLess(const std::string& rhs);
		bool	isLess(const Object* rhs);

		bool	isGreaterOrEq(const std::string& rhs);
		bool	isGreaterOrEq(const Object* rhs);

		bool	isLessOrEq(const std::string& rhs);
		bool	isLessOrEq(const Object* rhs);

		Object*	clone() const;

		std::string	__string() const;
};

#endif