#include <ValueBadGet.hpp>

ValueBadGet::ValueBadGet(const std::string& what):
    ScriptError("Bad call of Value::get" + (what == "" ? "" : ": " + what))
{
}
