#ifndef SCRIPT_ERROR_HPP
#define SCRIPT_ERROR_HPP

#include <stdexcept>

/// Exception thrown when an error occurs in the script.
class ScriptError: public std::runtime_error
{
	public:
		/// Use same constructor as std::runtime_error
		using std::runtime_error::runtime_error;
};

#endif // SCRIPT_ERROR_HPP
