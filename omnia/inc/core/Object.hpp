#ifndef OBJECT_HPP
# define OBJECT_HPP

# include <iostream>
# include <string>

class Object {
public:
	std::string	type;
	void*		value;
	int			links;

	Object(const std::string& type, void* value, int links);
	virtual ~Object() {}

	/* allocates a new value that is equal to the value of rhs */
	virtual void	setValue(const Object* rhs) = 0;
	/* casts rhs and allocates a value */
	virtual	void	setValue(const std::string& rhs) = 0;
	/* gets the allocated value pointer */
	virtual void	setValue(void* ptr) = 0;

	virtual void	addition(const std::string& rhs) = 0;
	virtual void	addition(const Object* rhs) = 0;

	virtual void	substraction(const std::string& rhs) = 0;
	virtual void	substraction(const Object* rhs) = 0;

	virtual void	multiplication(const std::string& rhs) = 0;
	virtual void	multiplication(const Object* rhs) = 0;

	virtual void	division(const std::string& rhs) = 0;
	virtual void	division(const Object* rhs) = 0;

	virtual Object*		clone() const = 0;

	virtual std::string __string() const = 0;
};

std::ostream&	operator<< (std::ostream& os, const Object& ob);

#endif