#include <ScriptError.hpp>

ScriptError::ScriptError(const std::string& what):
	std::runtime_error(what)
{
}
