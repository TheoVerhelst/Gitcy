#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <ostream>
#include <vector>
#include <typeinfo>
#include <typeindex>
#include <string>
#include <functional>
#include <map>
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

typedef std::function<Data(const std::vector<Data>&)> Functor;

class Overload
{
	public:
		Overload(const std::vector<SignatureType>& typeList, bool isVariadic, const Functor& functor);
		bool matches(const std::vector<Data>& arguments) const;
		/// \precondition matches(arguments)
		Data operator()(const std::vector<Data>& arguments) const;

		friend std::ostream& operator<<(std::ostream& os, const Overload& signature);

	private:
		std::vector<SignatureType> _typeList;
		bool _isVariadic;
		Functor _functor;
};


class Function
{
	public:
		/// Constructor.
		Function(const std::vector<Overload>& overloads);
		Data operator()(const std::vector<Data>& arguments) const;

		friend std::ostream& operator<<(std::ostream& os, const Function& function);

	private:
		std::vector<Overload> _overloads;
};

std::ostream& operator<<(std::ostream& os, const std::vector<Data>& values);

std::string join(const std::string& middle, const std::vector<std::string>& strings);

#endif // FUNCTION_HPP
