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

void	Numerus::setValue(const Object* rhs)
{
	if (rhs->value)
	{
		if (this->value)
			delete (int *)this->value;
		this->value = new int(*((int *)rhs->value));
	}
}

void	Numerus::setValue(const std::string& rhs)
{
	if (std::isdigit(rhs[0]) || rhs[0] == '-' || rhs[0] == '+')
		setValue(new int(utils::toInt(rhs)));
}

void	Numerus::setValue(void* ptr)
{
	if (this->value)
		delete (int *)this->value;
	this->value = ptr;
}

void	Numerus::addition(const std::string& rhs)
{
	if (std::isdigit(rhs[0]) || rhs[0] == '-' || rhs[0] == '+')
		*(int *)value += utils::toInt(rhs);
	else
		throw std::invalid_argument("invalid argument: " + rhs);
}

void	Numerus::addition(const Object* rhs)
{
	if (rhs->type == this->type)
		*(int *)value += *((int *)rhs->value);
	else
		throw std::invalid_argument("invalid argument type: " + rhs->type);
}

void	Numerus::substraction(const std::string& rhs)
{
	if (std::isdigit(rhs[0]) || rhs[0] == '-' || rhs[0] == '+')
		*(int *)value -= utils::toInt(rhs);
	else
		throw std::invalid_argument("invalid argument: " + rhs);
}

void	Numerus::substraction(const Object* rhs)
{
	if (rhs->type == this->type)
		*(int *)value -= *((int *)rhs->value);
	else
		throw std::invalid_argument("invalid argument type: " + rhs->type);
}

void	Numerus::multiplication(const std::string& rhs)
{
	if (std::isdigit(rhs[0]) || rhs[0] == '-' || rhs[0] == '+')
		*(int *)value *= utils::toInt(rhs);
	else
		throw std::invalid_argument("invalid argument: " + rhs);
}

void	Numerus::multiplication(const Object* rhs)
{
	if (rhs->type == this->type)
		*(int *)value *= *((int *)rhs->value);
	else
		throw std::invalid_argument("invalid argument type: " + rhs->type);
}

void	Numerus::division(const std::string& rhs)
{
	if (std::isdigit(rhs[0]) || rhs[0] == '-' || rhs[0] == '+')
		*(int *)value /= utils::toInt(rhs);
	else
		throw std::invalid_argument("invalid argument: " + rhs);
}

void	Numerus::division(const Object* rhs)
{
	if (rhs->type == this->type)
		*(int *)value /= *((int *)rhs->value);
	else
		throw std::invalid_argument("invalid argument type: " + rhs->type);
}

bool	Numerus::isEqual(const std::string& rhs)
{
	if (std::isdigit(rhs[0]) || rhs[0] == '-' || rhs[0] == '+')
		return *((int *)value) == utils::toInt(rhs);
	throw std::invalid_argument("invalid argument: " + rhs);
}

bool	Numerus::isEqual(const Object* rhs)
{
	if (this->type == rhs->type)
		return *((int *)value) == *((int *)rhs->value);
	throw std::invalid_argument("invalid consition: " + this->type + " == " + rhs->type);
}

bool	Numerus::isGreater(const std::string& rhs)
{
	if (std::isdigit(rhs[0]) || rhs[0] == '-' || rhs[0] == '+')
		return *((int *)value) > utils::toInt(rhs);
	throw std::invalid_argument("invalid argument: " + rhs);
}

bool	Numerus::isGreater(const Object* rhs)
{
	if (this->type == rhs->type)
		return *((int *)value) > *((int *)rhs->value);
	throw std::invalid_argument("invalid consition: " + this->type + " == " + rhs->type);
}

bool	Numerus::isLess(const std::string& rhs)
{
	if (std::isdigit(rhs[0]) || rhs[0] == '-' || rhs[0] == '+')
		return *((int *)value) < utils::toInt(rhs);
	throw std::invalid_argument("invalid argument: " + rhs);
}

bool	Numerus::isLess(const Object* rhs)
{
	if (this->type == rhs->type)
		return *((int *)value) < *((int *)rhs->value);
	throw std::invalid_argument("invalid consition: " + this->type + " == " + rhs->type);
}

bool	Numerus::isGreaterOrEq(const std::string& rhs)
{
	return !isLess(rhs);
}

bool	Numerus::isGreaterOrEq(const Object* rhs)
{
	return !isLess(rhs);
}

bool	Numerus::isLessOrEq(const std::string& rhs)
{
	return !isGreater(rhs);
}

bool	Numerus::isLessOrEq(const Object* rhs)
{
	return !isGreater(rhs);
}

Object*	Numerus::clone() const
{
	return new Numerus();
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