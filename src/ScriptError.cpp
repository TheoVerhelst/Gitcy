#include <ScriptError.hpp>

ScriptError::ScriptError(const std::string& what) throw():
	std::runtime_error(what)
{
}
