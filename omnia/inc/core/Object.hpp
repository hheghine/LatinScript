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

	virtual	void		setValue(const std::string& rhs) = 0;
	virtual void		setValue(void* ptr) = 0;

	virtual void		addition(const std::string& rhs) = 0;
	virtual void		addition(const Object* ob) = 0;

	virtual std::string __string() const = 0;
};

std::ostream&	operator<< (std::ostream& os, const Object& ob);

#endif