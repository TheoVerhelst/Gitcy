#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <ostream>
#include <vector>
#include <functional>
#include "Interpreter.hpp"

class Function
{
	public:
		/// Constructor.
		Function(int numberOfParameters, std::function<Data(const std::vector<Data>&)> pointer);
		int getNumberOfParameters() const;
		const std::function<Data(const std::vector<Data>&)>& getPointer() const;

	private:
		int _numberOfParameters;
		std::function<Data(const std::vector<Data>&)> _pointer;
};

std::ostream& operator<<(std::ostream& os, const Function& function);

#endif // FUNCTION_HPP
