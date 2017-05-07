#ifndef VALUE_BAD_GET
#define VALUE_BAD_GET

#include <ScriptError.hpp>

/// Exception thrown when a value is get with the bad type.
class ValueBadGet : public ScriptError
{
    public:
		/// Constructor.
		/// \param what A string explaining the error.
        ValueBadGet(const std::string& what = "");
};

#endif // VALUE_BAD_GET
