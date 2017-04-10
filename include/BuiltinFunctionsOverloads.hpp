#ifndef BUILTIN_FUNCTIONS_OVERLOADS_HPP
#define BUILTIN_FUNCTIONS_OVERLOADS_HPP

#include <vector>
#include <Value.hpp>
#include <Overload.hpp>

namespace BuiltinFunctionsOverloads
{
	#define DEFINE_OVERLOAD(className) \
	class className : public Overload \
	{ \
		public: \
			className(); \
 \
			virtual Value call(const std::vector<Value>& arguments) const override; \
	}; \

	#define DEFINE_TEMPLATE_OVERLOAD(className) \
	template <typename T> \
	DEFINE_OVERLOAD(className)

	DEFINE_OVERLOAD(Print)
	DEFINE_OVERLOAD(Do)
	DEFINE_OVERLOAD(Define)
	DEFINE_OVERLOAD(And)
	DEFINE_OVERLOAD(Or)
	DEFINE_OVERLOAD(Not)
	DEFINE_TEMPLATE_OVERLOAD(LowerThan)
	DEFINE_TEMPLATE_OVERLOAD(GreaterThan)
	DEFINE_TEMPLATE_OVERLOAD(LowerEqual)
	DEFINE_TEMPLATE_OVERLOAD(GreaterEqual)
	DEFINE_TEMPLATE_OVERLOAD(Equal)
	DEFINE_TEMPLATE_OVERLOAD(NotEqual)
	DEFINE_TEMPLATE_OVERLOAD(Add)
	DEFINE_TEMPLATE_OVERLOAD(Substract)
	DEFINE_TEMPLATE_OVERLOAD(Multiply)
	DEFINE_TEMPLATE_OVERLOAD(Divide)
	DEFINE_OVERLOAD(Modulo)
	DEFINE_OVERLOAD(DoubleModulo)

	#undef DEFINE_OVERLOAD
	#undef DEFINE_TEMPLATE_OVERLOAD
}

#include <algorithm>
#include <functional>
#include <numeric>
#include <Utils.hpp>
#include <SignatureType.hpp>
#include <ScriptError.hpp>

namespace BuiltinFunctionsOverloads
{
	template <typename T>
	LowerThan<T>::LowerThan():
		Overload{{SignatureType::create<T>(), SignatureType::create<T>()}, true}
	{
	}

	template <typename T>
	Value LowerThan<T>::call(const std::vector<Value>& arguments) const
	{
		const std::vector<T> convertedArguments{Utils::convert<T>(arguments)};
		return std::adjacent_find(convertedArguments.begin(), convertedArguments.end(), std::greater_equal<T>()) == convertedArguments.end();
	}

	template <typename T>
	GreaterThan<T>::GreaterThan():
		Overload{{SignatureType::create<T>(), SignatureType::create<T>()}, true}
	{
	}

	template <typename T>
	Value GreaterThan<T>::call(const std::vector<Value>& arguments) const
	{
		const std::vector<T> convertedArguments{Utils::convert<T>(arguments)};
		return std::adjacent_find(convertedArguments.begin(), convertedArguments.end(), std::less_equal<T>()) == convertedArguments.end();
	}

	template <typename T>
	LowerEqual<T>::LowerEqual():
		Overload{{SignatureType::create<T>(), SignatureType::create<T>()}, true}
	{
	}

	template <typename T>
	Value LowerEqual<T>::call(const std::vector<Value>& arguments) const
	{
		const std::vector<T> convertedArguments{Utils::convert<T>(arguments)};
		return std::adjacent_find(convertedArguments.begin(), convertedArguments.end(), std::greater<T>()) == convertedArguments.end();
	}

	template <typename T>
	GreaterEqual<T>::GreaterEqual():
		Overload{{SignatureType::create<T>(), SignatureType::create<T>()}, true}
	{
	}

	template <typename T>
	Value GreaterEqual<T>::call(const std::vector<Value>& arguments) const
	{
		const std::vector<T> convertedArguments{Utils::convert<T>(arguments)};
		return std::adjacent_find(convertedArguments.begin(), convertedArguments.end(), std::less<T>()) == convertedArguments.end();
	}

	template <typename T>
	Equal<T>::Equal():
		Overload{{SignatureType::create<T>(), SignatureType::create<T>()}, true}
	{
	}

	template <typename T>
	Value Equal<T>::call(const std::vector<Value>& arguments) const
	{
		const std::vector<T> convertedArguments{Utils::convert<T>(arguments)};
		return std::adjacent_find(convertedArguments.begin(), convertedArguments.end(), std::not_equal_to<T>()) == convertedArguments.end();
	}

	template <typename T>
	NotEqual<T>::NotEqual():
		Overload{{SignatureType::create<T>(), SignatureType::create<T>()}, true}
	{
	}

	template <typename T>
	Value NotEqual<T>::call(const std::vector<Value>& arguments) const
	{
		return Not().call({Equal<T>().call(arguments)});
	}

	template <typename T>
	Add<T>::Add():
		Overload{{SignatureType::create<T>()}, true}
	{
	}

	template <typename T>
	Value Add<T>::call(const std::vector<Value>& arguments) const
	{
		const std::vector<T> convertedArguments{Utils::convert<T>(arguments)};
		return std::accumulate(convertedArguments.begin(), convertedArguments.end(), T());
	}

	template <typename T>
	Substract<T>::Substract():
		Overload{{SignatureType::create<T>()}, true}
	{
	}

	template <typename T>
	Value Substract<T>::call(const std::vector<Value>& arguments) const
	{
		if(arguments.size() == 1)
			return -arguments.front().get<T>();
		else
		{
			const std::vector<T> convertedArguments{Utils::convert<T>(arguments)};
			return std::accumulate(std::next(convertedArguments.begin()), convertedArguments.end(), convertedArguments.front(), std::minus<T>());
		}
	}

	template <typename T>
	Multiply<T>::Multiply():
		Overload{{SignatureType::create<T>()}, true}
	{
	}

	template <typename T>
	Value Multiply<T>::call(const std::vector<Value>& arguments) const
	{
		const std::vector<T> convertedArguments{Utils::convert<T>(arguments)};
		return std::accumulate(convertedArguments.begin(), convertedArguments.end(), static_cast<T>(1), std::multiplies<T>());
	}

	template <typename T>
	Divide<T>::Divide():
		Overload{{SignatureType::create<T>(), SignatureType::create<T>()}, true}
	{
	}

	template <typename T>
	Value Divide<T>::call(const std::vector<Value>& arguments) const
	{
		const std::vector<T> convertedArguments{Utils::convert<T>(arguments)};
		// If there is a zero in the values [begin + 1, end)
		if(std::find(std::next(convertedArguments.begin()), convertedArguments.end(), static_cast<T>(0)) != convertedArguments.end())
			throw ScriptError("division by zero");
		return std::accumulate(std::next(convertedArguments.begin()), convertedArguments.end(), convertedArguments.front(), std::divides<T>());
	}
}

#endif // BUILTIN_FUNCTIONS_OVERLOADS_HPP
