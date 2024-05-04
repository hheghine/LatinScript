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

	virtual void		setValue(void* ptr);
	virtual std::string __string() const;
};

std::ostream&	operator<< (std::ostream& os, const Object& ob);

#endif