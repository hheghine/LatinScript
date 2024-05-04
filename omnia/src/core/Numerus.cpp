#include "Numerus.hpp"

int	toInt(const std::string& str)
{
	std::stringstream ss(str);
	int val = 0;
	char remaining;

	if (!(ss >> val) || ss.get(remaining))
		throw std::invalid_argument("invalid assignment operation: " + str);
	return val;
}

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

void	Numerus::setValue(const std::string& rhs)
{
	if (std::isdigit(rhs[0]) || rhs[0] == '-' || rhs[0] == '+')
		setValue(new int(toInt(rhs)));
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