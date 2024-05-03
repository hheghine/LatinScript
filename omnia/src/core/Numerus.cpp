#include "Numerus.hpp"

Numerus::Numerus()
	: Object("numerus", new int{}, 0)
{}

Numerus::Numerus(Object* ptr)
	: Object("numerus", new int{}, 0)
{
	if (ptr->type == "numerus")
		*(int *)value = *(int *)ptr->value;
}

Numerus::~Numerus()
{
	if (value)
		delete (int *)value;
}