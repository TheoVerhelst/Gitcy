#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <vector>
#include "Data.hpp"
#include "Function.hpp"

class Interpreter;

class Functions
{
	public:
		/// Constructor.
		Functions(Interpreter& interpreter);

		const Function print;
		const Function do_;
		const Function define;
		const Function lowerThan;
		const Function greaterThan;
		const Function lowerEqual;
		const Function greaterEqual;
		const Function equal;
		const Function notEqual;
		const Function and_;
		const Function or_;
		const Function add;
		const Function substract;
		const Function multiply;
		const Function divide;
		const Function modulo;
		const Function not_;

	private:
		Data _print(const std::vector<Data>& args);
		Data _do(const std::vector<Data>& args);
		Data _define(const std::vector<Data>& args);
		Data _lowerThanInt(const std::vector<Data>& args);
		Data _lowerThanFloat(const std::vector<Data>& args);
		Data _greaterThanInt(const std::vector<Data>& args);
		Data _greaterThanFloat(const std::vector<Data>& args);
		Data _lowerEqualInt(const std::vector<Data>& args);
		Data _lowerEqualFloat(const std::vector<Data>& args);
		Data _greaterEqualInt(const std::vector<Data>& args);
		Data _greaterEqualFloat(const std::vector<Data>& args);
		Data _equalInt(const std::vector<Data>& args);
		Data _equalFloat(const std::vector<Data>& args);
		Data _equalString(const std::vector<Data>& args);
		Data _notEqualInt(const std::vector<Data>& args);
		Data _notEqualFloat(const std::vector<Data>& args);
		Data _notEqualString(const std::vector<Data>& args);
		Data _and(const std::vector<Data>& args);
		Data _or(const std::vector<Data>& args);
		Data _addInt(const std::vector<Data>& args);
		Data _addFloat(const std::vector<Data>& args);
		Data _addString(const std::vector<Data>& args);
		Data _substractInt(const std::vector<Data>& args);
		Data _substractFloat(const std::vector<Data>& args);
		Data _multiplyInt(const std::vector<Data>& args);
		Data _multiplyFloat(const std::vector<Data>& args);
		Data _divideInt(const std::vector<Data>& args);
		Data _divideFloat(const std::vector<Data>& args);
		Data _moduloInt(const std::vector<Data>& args);
		Data _moduloFloat(const std::vector<Data>& args);
		Data _not(const std::vector<Data>& args);

		Interpreter& _interpreter;
};

#endif
