#ifndef SCRIPT_ERROR_HPP
#define SCRIPT_ERROR_HPP

#include <stdexcept>

/// Exception thrown when an error occurs in the script.
/// \TODO make ScriptError.cpp, checks whether we really need to redefine these methods.
class ScriptError: public std::runtime_error
{
	public:
		/// Constructor.
		/// \param what_arg A string explaining the error.
		ScriptError(const std::string what_arg="") throw():
			std::runtime_error(what_arg),
			_what(what_arg)
		{}

		/// Returns the error string as a C-style string.
		/// \returns The error string as a C-style string.
		virtual const char* what() const throw()
		{
			return _what.c_str();
		}

		/// Destructor.
		virtual ~ScriptError() throw()
		{}

	private:
		/// A string explaining the error.
		const std::string _what;
};

#endif // SCRIPT_ERROR_HPP
