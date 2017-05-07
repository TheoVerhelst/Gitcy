#ifndef VALUE_TYPES_HPP
#define VALUE_TYPES_HPP

#include <string>
#include <map>
#include <typeindex>

class ValueTypes
{
	public:
		/// Returns a fancy name of the supplied type.
		/// \param typeIndex The type to check.
		/// \returns The type name.
		static std::string getTypeName(const std::type_index& typeIndex);

		static const std::type_index& getTypeIndex(const std::string& typeName);

	private:
		/// Map of pretty names for types to display in the output operator.
		static const std::map<std::type_index, std::string> _typeNames;
};

#endif // VALUE_TYPES_HPP
