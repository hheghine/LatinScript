#include "Ordinata.hpp"

// ordinata < numerus > arr = < 1, 2, 3, 4 > 
// arr < i > 

Ordinata::Ordinata(const std::string& init)
{
	try {
		_init(init);
	} catch (const std::exception& e) {
		std::cout << ls::RED << "[ ";
		ls::displayTime();
		std::cout << " |    ✘   ]" << "\terror: " \
		<< e.what() << ls::CRST << std::endl;
	}
}

void	Ordinata::_init(const std::string& init)
{
	svector decl = utils::splitLine(init);

	if (decl.size() < 5)
		throw std::invalid_argument("wrong syntax: " + init);
	if (decl.at(1) != "<")
		throw std::invalid_argument("wrong syntax: " + decl.at(1));

	if (!utils::isType(decl.at(2)))
		throw std::invalid_argument("unknown type: " + decl.at(2));
	_type = decl.at(2);

	if (decl.at(3) != ">")
		throw std::invalid_argument("invalid character instead of \
		bracket:" + decl.at(3));
	if (!utils::varNameCheck(decl.at(4)))
		throw std::invalid_argument("wrong variable name: " + decl.at(4));
	_name = decl.at(4);

	if (decl.size() > 5)
	{
		bool assignment = false;
		bool opened = false;
		bool closed = false;

		for(auto it = decl.begin() + 5; it != decl.end(); ++it)
		{
			if (*it == "=")
			{
				if (it + 1 != decl.end() && *(it + 1) == "<" \
					&& !assignment)
				{
					assignment = true;
					continue ;
				}
				throw std::invalid_argument("wrong syntax: " + init);
			}
			if (*it == "<")
			{
				opened = true;
				continue ;
			}
			if (*it == ">")
			{
				closed = true;
				break ;
			}
			if (*((*it).end() - 1) == ',')
				(*it).erase((*it).end() - 1);
			_array.push_back(createVar());
			_array[_array.size() - 1]->setValue(*it);
		}
		if (!opened || !closed)
			throw std::invalid_argument("wrong syntax: " + init);
	}
}

Object*	Ordinata::createVar()
{
	if (_type == "numerus")
		return new Numerus();
	if (_type == "filum")
		return new Filum();
	if (_type == "duplus")
		return new Duplus();
	return nullptr;
}

Ordinata::~Ordinata()
{
	for (auto it = _array.begin(); it != _array.end(); ++it)
		delete *it;
	_array.clear();
}

void	Ordinata::setValue(int idx, const std::string& rhs)
{
	if (idx >= (int)_array.size())
		throw std::runtime_error("SIGSEGV");
	_array[idx]->setValue(rhs);
}

void	Ordinata::setValue(int idx, const Object* rhs)
{
	if (idx >= (int)_array.size())
		throw std::runtime_error("SIGSEGV");
	_array[idx]->setValue(rhs);
}

Object*	Ordinata::getValue(int idx)
{
	if (idx >= (int)_array.size())
		throw std::runtime_error("SIGSEGV");
	return _array[idx];
}

std::string	Ordinata::__string()
{
	std::string str{""};
	for (auto it = _array.begin(); it != _array.end(); ++it)
	{
		str += "< " + (*it)->__string() + " >";
		if (it + 1 != _array.end())
			str += " ";
	}
	return str;
}