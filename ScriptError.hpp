#ifndef SCRIPT_ERROR_HPP
#define SCRIPT_ERROR_HPP

#include <stdexcept>

class ScriptError: public std::runtime_error
{
	public:
		ScriptError(const std::string what_arg="") throw():
			std::runtime_error(what_arg),
			m_what(what_arg)
		{}

		virtual const char* what() const throw()
		{
			return m_what.c_str();
		}

		virtual ~ScriptError() throw()
		{}

	private:
		const std::string m_what;
};

#endif // SCRIPT_ERROR_HPP
