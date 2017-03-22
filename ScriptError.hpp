#ifndef SCRIPT_ERROR_HPP
#define SCRIPT_ERROR_HPP

#include <stdexcept>

/// \TODO make ScriptError.cpp, checks whether we really need to redefine these methods.
class ScriptError: public std::runtime_error
{
	public:
		ScriptError(const std::string what_arg="") throw():
			std::runtime_error(what_arg),
			_what(what_arg)
		{}

		virtual const char* what() const throw()
		{
			return _what.c_str();
		}

		virtual ~ScriptError() throw()
		{}

	private:
		const std::string _what;
};

#endif // SCRIPT_ERROR_HPP
