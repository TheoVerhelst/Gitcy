#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <vector>
#include "Data.hpp"

class Interpreter;

class Functions
{
	public:
		/// Constructor.
		Functions(Interpreter& interpreter);
		Data print(const std::vector<Data>& args);
		Data do_(const std::vector<Data>& args);
		Data define(const std::vector<Data>& args);
		Data lowerThan(const std::vector<Data>& args);
		Data greaterThan(const std::vector<Data>& args);
		Data lowerEqual(const std::vector<Data>& args);
		Data greaterEqual(const std::vector<Data>& args);
		Data equal(const std::vector<Data>& args);
		Data notEqual(const std::vector<Data>& args);
		Data and_(const std::vector<Data>& args);
		Data or_(const std::vector<Data>& args);
		Data add(const std::vector<Data>& args);
		Data substract(const std::vector<Data>& args);
		Data multiply(const std::vector<Data>& args);
		Data divide(const std::vector<Data>& args);
		Data modulo(const std::vector<Data>& args);
		Data not_(const std::vector<Data>& args);

	private:
		Interpreter& m_interpreter;
};

#endif
