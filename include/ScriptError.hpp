#ifndef SCRIPT_ERROR_HPP
#define SCRIPT_ERROR_HPP

#include <stdexcept>

/// Exception thrown when an error occurs in the script.
class ScriptError: public std::runtime_error
{
	public:
		/// Constructor.
		/// \param what A string explaining the error.
		explicit ScriptError(const std::string& what="") throw();
};

#endif // SCRIPT_ERROR_HPP
