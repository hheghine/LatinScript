#include "Filum.hpp"

Filum::Filum()
	: Object("filum", new std::string{""}, 0)
{
	links = 1;
}

Filum::Filum(Object* ptr)
	: Object("filum", new std::string{""}, 0)
{
	if (ptr->type == "filum")
		*(std::string *)value = *(std::string *)ptr->value;
}

void	Filum::setValue(const Object* rhs)
{
	if (rhs->value)
	{
		if (this->value)
			delete (std::string *)this->value;
		this->value = new std::string(*((std::string *)rhs->value));
	}
}

void	Filum::setValue(const std::string& rhs)
{
	std::string str = removeBrackets(rhs);

	setValue(new std::string(str));
}

void	Filum::setValue(void* ptr)
{
	if (this->value)
		delete (std::string *)this->value;
	this->value = ptr;
}

std::string	Filum::removeBrackets(const std::string& s)
{
	std::string str = s;
	if (str.find('*') != std::string::npos)
	{
		if (*(str.end() - 1) != '*')
			throw std::invalid_argument("srong syntax: closing '*' not found");
		str = utils::extractString(str.begin(), str.end(), '*');
	}
	return str;
}

Object*	Filum::clone() const
{
	return new Filum();
}

void	Filum::addition(const std::string& rhs)
{
	*(std::string* )value += removeBrackets(rhs);
}

void	Filum::addition(const Object* rhs)
{
	if (rhs->type == this->type)
		*(std::string *)value += *((std::string *)rhs->value);
	else
		throw std::invalid_argument("invalid argument type: " + rhs->type);
}

void	Filum::substraction(const std::string& rhs)
{
	(void) rhs;
	throw std::invalid_argument("invalid operation");
}

void	Filum::substraction(const Object* rhs)
{
	(void) rhs;
	throw std::invalid_argument("invalid operation");
}

void	Filum::multiplication(const std::string& rhs)
{
	(void) rhs;
	throw std::invalid_argument("invalid operation");
}

void	Filum::multiplication(const Object* rhs)
{
	(void) rhs;
	throw std::invalid_argument("invalid operation");
}

void	Filum::division(const std::string& rhs)
{
	(void) rhs;
	throw std::invalid_argument("invalid operation");
}

void	Filum::division(const Object* rhs)
{
	(void) rhs;
	throw std::invalid_argument("invalid operation");
}

bool	Filum::isEqual(const std::string& rhs)
{
	// std::string* strPtr = static_cast<std::string*>(value);
	return *((std::string *)value) == rhs;
}

bool	Filum::isEqual(const Object* rhs)
{
	if (this->type == rhs->type)
		return *((std::string *)value) == *((std::string *)rhs->value);
	throw std::invalid_argument("invalid consition: " + this->type + " == " + rhs->type);
}

bool	Filum::isGreater(const std::string& rhs)
{
	return *((std::string *)value) > rhs;
}

bool	Filum::isGreater(const Object* rhs)
{
	if (this->type == rhs->type)
		return *((std::string *)value) > *((std::string *)rhs->value);
	throw std::invalid_argument("invalid consition: " + this->type + " == " + rhs->type);
}

bool	Filum::isLess(const std::string& rhs)
{
	return *((std::string *)value) > rhs;
}

bool	Filum::isLess(const Object* rhs)
{
	if (this->type == rhs->type)
		return *((std::string *)value) < *((std::string *)rhs->value);
	throw std::invalid_argument("invalid consition: " + this->type + " == " + rhs->type);
}

bool	Filum::isGreaterOrEq(const std::string& rhs)
{
	return !isLess(rhs);
}

bool	Filum::isGreaterOrEq(const Object* rhs)
{
	return !isLess(rhs);
}

bool	Filum::isLessOrEq(const std::string& rhs)
{
	return !isGreater(rhs);
}

bool	Filum::isLessOrEq(const Object* rhs)
{
	return !isGreater(rhs);
}

std::string	Filum::__string() const
{
	return *((std::string*)value);
}

Filum::~Filum()
{
	if (value)
		delete (std::string *)value;
}