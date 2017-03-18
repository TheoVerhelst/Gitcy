#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <ostream>
#include <vector>
#include <typeinfo>
#include <typeindex>
#include <string>
#include <functional>
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
};

class Signature
{
	public:
		Signature(const std::vector<SignatureType>& typeList, bool isVariadic);
		bool matches(const std::vector<Data>& arguments) const;
		friend std::ostream& operator<<(std::ostream& os, const Signature& signature);

	private:
		std::vector<SignatureType> _typeList;
		bool _isVariadic;
};

typedef std::function<Data(const std::vector<Data>&)> Functor;

class Function
{
	public:
		/// Constructor.
		Function(const std::vector<std::pair<Signature, Functor>>& overloads);
		Data operator()(const std::vector<Data>& arguments) const;
		friend std::ostream& operator<<(std::ostream& os, const Function& function);

	private:
		std::vector<std::pair<Signature, Functor>> _overloads;
};

std::ostream& operator<<(std::ostream& os, const std::vector<Data>& values);

std::string join(const std::string& middle, const std::vector<std::string>& strings);

#endif // FUNCTION_HPP
