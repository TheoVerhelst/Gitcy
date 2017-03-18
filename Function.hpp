#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <ostream>
#include <vector>
#include <string>
#include "Data.hpp"
#include "Overload.hpp"

class Function
{
	public:
		/// Constructor.
		Function(const std::vector<Overload>& overloads);
		Data operator()(const std::vector<Data>& arguments) const;

		friend std::ostream& operator<<(std::ostream& os, const Function& function);

	private:
		std::vector<Overload> _overloads;
};

std::ostream& operator<<(std::ostream& os, const std::vector<Data>& values);

#endif // FUNCTION_HPP
