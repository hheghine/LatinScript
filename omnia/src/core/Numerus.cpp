#include "Numerus.hpp"

Numerus::Numerus()
	: Object("numerus", new int{0}, 0)
{
	links = 1;
}

Numerus::Numerus(Object* ptr)
	: Object("numerus", new int{}, 0)
{
	if (ptr->type == "numerus")
		*(int *)value = *(int *)ptr->value;
}

void	Numerus::setValue(void* ptr)
{
	delete (int *)this->value;
	this->value = (int *)ptr;
}

std::string	Numerus::__string() const
{
	return std::to_string(*((int *)value));
}

Numerus::~Numerus()
{
	if (value)
		delete (int *)value;
}