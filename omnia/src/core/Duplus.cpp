#include "Duplus.hpp"

Duplus::Duplus()
	: Object("duplus", new double{0}, 0)
{
	links = 1;
}

Duplus::Duplus(Object* ptr)
	: Object("duplus", new double{}, 0)
{
	if (ptr->type == "duplus")
		*(double *)value = *(double *)ptr->value;
}

void	Duplus::setValue(const Object* rhs)
{
	if (rhs->value)
	{
		if (rhs->type == this->type)
		{
			if (this->value)
				delete (double *)this->value;
			this->value = new double(*((double *)rhs->value));
		}
		else if (rhs->type == "numerus")
		{
			if (this->value)
				delete (double *)this->value;
			this->value = new double(*((int *)rhs->value));
		}
	}
}

void	Duplus::setValue(const std::string& rhs)
{
	if (std::isdigit(rhs[0]) || rhs[0] == '-' || rhs[0] == '+')
		setValue(new double(utils::toDouble(rhs)));
}

void	Duplus::setValue(void* ptr)
{
	if (this->value)
		delete (double *)this->value;
	this->value = ptr;
}

void	Duplus::addition(const std::string& rhs)
{
	if (std::isdigit(rhs[0]) || rhs[0] == '-' || rhs[0] == '+')
		*(double *)value += utils::toDouble(rhs);
	else
		throw std::invalid_argument("invalid argument: " + rhs);
}

void	Duplus::addition(const Object* rhs)
{
	if (rhs->type == this->type)
		*(double *)value += *((double *)rhs->value);
	else if (rhs->type == "numerus")
		*(double *)value += *((int *)rhs->value);
	else
		throw std::invalid_argument("invalid argument type: " + rhs->type);
}

void	Duplus::substraction(const std::string& rhs)
{
	if (std::isdigit(rhs[0]) || rhs[0] == '-' || rhs[0] == '+')
		*(double *)value -= utils::toDouble(rhs);
	else
		throw std::invalid_argument("invalid argument: " + rhs);
}

void	Duplus::substraction(const Object* rhs)
{
	if (rhs->type == this->type)
		*(double *)value -= *((double *)rhs->value);
	else if (rhs->type == "numerus")
		*(double *)value -= *((int *)rhs->value);
	else
		throw std::invalid_argument("invalid argument type: " + rhs->type);
}

void	Duplus::multiplication(const std::string& rhs)
{
	if (std::isdigit(rhs[0]) || rhs[0] == '-' || rhs[0] == '+')
		*(double *)value *= utils::toDouble(rhs);
	else
		throw std::invalid_argument("invalid argument: " + rhs);
}

void	Duplus::multiplication(const Object* rhs)
{
	if (rhs->type == this->type)
		*(double *)value *= *((double *)rhs->value);
	else if (rhs->type == "numerus")
		*(double *)value *= *((int *)rhs->value);
	else
		throw std::invalid_argument("invalid argument type: " + rhs->type);
}

void	Duplus::division(const std::string& rhs)
{
	if (std::isdigit(rhs[0]) || rhs[0] == '-' || rhs[0] == '+')
		*(double *)value /= utils::toDouble(rhs);
	else
		throw std::invalid_argument("invalid argument: " + rhs);
}

void	Duplus::division(const Object* rhs)
{
	if (rhs->type == this->type)
		*(double *)value /= *((double *)rhs->value);
	else if (rhs->type == "numerus")
		*(double *)value /= *((int *)rhs->value);
	else
		throw std::invalid_argument("invalid argument type: " + rhs->type);
}

bool	Duplus::isEqual(const std::string& rhs)
{
	if (std::isdigit(rhs[0]) || rhs[0] == '-' || rhs[0] == '+')
		return *((double *)value) == utils::toDouble(rhs);
	throw std::invalid_argument("invalid argument: " + rhs);
}

bool	Duplus::isEqual(const Object* rhs)
{
	if (rhs->type == this->type)
		return *((double *)value) == *((double *)rhs->value);
	else if (rhs->type == "numerus")
		return *((double *)value) == *((int *)rhs->value);
	throw std::invalid_argument("invalid consition: " + this->type + " == " + rhs->type);
}

bool	Duplus::isGreater(const std::string& rhs)
{
	if (std::isdigit(rhs[0]) || rhs[0] == '-' || rhs[0] == '+')
		return *((double *)value) > utils::toDouble(rhs);
	throw std::invalid_argument("invalid argument: " + rhs);
}

bool	Duplus::isGreater(const Object* rhs)
{
	if (this->type == rhs->type)
		return *((double *)value) > *((double *)rhs->value);
	throw std::invalid_argument("invalid consition: " + this->type + " == " + rhs->type);
}

bool	Duplus::isLess(const std::string& rhs)
{
	if (std::isdigit(rhs[0]) || rhs[0] == '-' || rhs[0] == '+')
		return *((double *)value) < utils::toDouble(rhs);
	throw std::invalid_argument("invalid argument: " + rhs);
}

bool	Duplus::isLess(const Object* rhs)
{
	if (rhs->type == this->type)
		return *((double *)value) < *((double *)rhs->value);
	else if (rhs->type == "numerus")
		return *((double *)value) < *((int *)rhs->value);
	throw std::invalid_argument("invalid consition: " + this->type + " == " + rhs->type);
}

bool	Duplus::isGreaterOrEq(const std::string& rhs)
{
	return !isLess(rhs);
}

bool	Duplus::isGreaterOrEq(const Object* rhs)
{
	return !isLess(rhs);
}

bool	Duplus::isLessOrEq(const std::string& rhs)
{
	return !isGreater(rhs);
}

bool	Duplus::isLessOrEq(const Object* rhs)
{
	return !isGreater(rhs);
}

Object*	Duplus::clone() const
{
	return new Duplus();
}

std::string	Duplus::__string() const
{
	return std::to_string(*((double *)value));
}

Duplus::~Duplus()
{
	if (value)
		delete (double *)value;
}