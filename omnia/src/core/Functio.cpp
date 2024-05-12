#include "Functio.hpp"

Functio::Functio(const std::string& declaration)
	: _name("")
	, _return_type("")
	, _return (nullptr)
{
	try {
		parse(declaration);
	} catch (const std::exception& e) {
		std::cout << RED << "[ ✘\t\t\t]" << "\terror: " \
		<< e.what() << CRST << std::endl;
	}
}

Functio::~Functio()
{
	if (_return)
		delete _return;

	for (auto it = vars.begin(); it != vars.end(); ++it)
		delete it->second;
	vars.clear();
}

void	Functio::parse(const std::string& declaration)
{
	svector decl_vec = utils::splitLine(declaration);

	if (!utils::varNameCheck(decl_vec.at(1)))
		throw std::invalid_argument("wrong function name: " + decl_vec.at(1));

	_name = decl_vec[1];

	if (decl_vec.at(2) != "<")
		throw std::invalid_argument("wrong function syntax");

	bool closed = false;


	auto it = decl_vec.begin() + 3;
	for (; it != decl_vec.end(); ++it)
	{
		if (*it == ">")
		{
			closed = true;
			break ;
		}
		if (!utils::isType(*it))
			throw std::invalid_argument("wrong function syntax");
		it ++;
		if (((*it).at((*it).size() - 1) != ',' && it + 1 != decl_vec.end() && *(it + 1) != ">"))
			throw std::invalid_argument("wrong function syntax");

		std::string var_name = *it;
		if (var_name[var_name.size() - 1] == ',')
			var_name.erase(var_name.end() - 1);
		vars[var_name] = createVar(*(it - 1));
	}

	if (!closed)
		throw std::invalid_argument("wrong function syntax: bracket not closed");

	it ++;

	if (it != decl_vec.end())
	{
		if (*it != ":")
			throw std::invalid_argument("wrong function syntax: invalid characters: " + *it);
		it ++;
		_return_type = *it;
		_return = createVar(_return_type);

		it ++;

		if (it != decl_vec.end())
			throw std::invalid_argument("wrong function syntax: " + *it);
	}
}

Object*	Functio::createVar(const std::string& type)
{
	if (type == "numerus")
		return new Numerus();
	throw std::invalid_argument("unknown return type: " + type);
}

void	Functio::setBody(const svector& body)
{
	for (auto it = body.begin(); it != body.end(); ++it)
		_body.push_back(*it);
}