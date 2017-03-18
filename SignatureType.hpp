#ifndef SIGNATURE_TYPE_HPP
#define SIGNATURE_TYPE_HPP

#include <string>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <experimental/optional>
#include "Data.hpp"

class SignatureType
{
	public:
		SignatureType();
		SignatureType(const std::type_info& type);
		std::string getName() const;
		bool matches(const Data& data) const;

	private:
		std::experimental::optional<std::type_index> _typeIndex;
		static const std::map<std::type_index, std::string> _typePrettyNames;
};

#endif // SIGNATURE_TYPE_HPP
