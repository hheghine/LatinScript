#include "Object.hpp"

Object::Object(const std::string& type, void* value, int links)
	: type{type}
	, value{value}
	, links{links}
{}

std::ostream&	operator<< (std::ostream& os, const Object& ob)
{
	os << ob.__string() << std::endl;
	return os;
}