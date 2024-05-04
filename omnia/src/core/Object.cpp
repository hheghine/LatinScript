#include "Object.hpp"

Object::Object(const std::string& type, void* value, int links)
	: type{type}
	, value{value}
	, links{links}
{}

void	Object::setValue(void* ptr)
{
	(void)ptr;
}

std::string	Object::__string() const
{
	return "ignōtus (undefined)";
}

std::ostream&	operator<< (std::ostream& os, const Object& ob)
{
	os << ob.__string() << std::endl;
	return os;
}