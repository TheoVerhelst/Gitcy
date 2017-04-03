#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <functional>
#include <Function.hpp>
#include <Overload.hpp>
#include <Utils.hpp>

// Forward declarations
class Interpreter;
class Value;

/// Holds all functions that are written in C++ but callable in scripts.
/// These functions are public const variables, and are initialized in the
/// constructor.
class BuiltinFunctions
{
	public:
		/// Constructor.
		BuiltinFunctions();

		const Function print;        ///< Prints the arguments to stdout.
		const Function do_;          ///< Just evaluates its arguments, and returns the last.
		const Function define;       ///< Binds a value to a name.
		const Function lowerThan;    ///< Checks if first argument is lower than second.
		const Function greaterThan;  ///< Checks if first argument is greater than second.
		const Function lowerEqual;   ///< Checks if first argument is lower of equal to the second.
		const Function greaterEqual; ///< Checks if first argument is greater or equal to the second.
		const Function equal;        ///< Checks if first argument is equal to the second.
		const Function notEqual;     ///< Checks if first argument is not equal to the second.
		const Function and_;         ///< Returns the logical and between first and second argument.
		const Function or_;          ///< Returns the logical and between first and second argument.
		const Function add;          ///< Returns the arithmetic addition between its arguments.
		const Function substract;    ///< Returns the arithmetic substraction between its arguments.
		const Function multiply;     ///< Returns the arithmetic multiplication between its arguments.
		const Function divide;       ///< Returns the arithmetic division between its arguments.
		const Function modulo;       ///< Returns the arithmetic modulo between its arguments.
		const Function not_;         ///< Returns the logical not of its argument.
};

namespace BuiltinOverloads
{
	#define DEFINE_OVERLOAD(className) \
	class className : public Overload \
	{ \
		public: \
			className(); \
 \
			virtual Value operator()(const std::vector<Value>& arguments) const override; \
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

#include <Value.hpp>
#include <ScriptError.hpp>

namespace BuiltinOverloads
{
	template <typename T>
	LowerThan<T>::LowerThan():
		Overload{{SignatureType::create<T>(), SignatureType::create<T>()}, true}
	{
	}

	template <typename T>
	Value LowerThan<T>::operator()(const std::vector<Value>& arguments) const
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
	Value GreaterThan<T>::operator()(const std::vector<Value>& arguments) const
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
	Value LowerEqual<T>::operator()(const std::vector<Value>& arguments) const
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
	Value GreaterEqual<T>::operator()(const std::vector<Value>& arguments) const
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
	Value Equal<T>::operator()(const std::vector<Value>& arguments) const
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
	Value NotEqual<T>::operator()(const std::vector<Value>& arguments) const
	{
		return Not()({Equal<T>()(arguments)});
	}

	template <typename T>
	Add<T>::Add():
		Overload{{SignatureType::create<T>()}, true}
	{
	}

	template <typename T>
	Value Add<T>::operator()(const std::vector<Value>& arguments) const
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
	Value Substract<T>::operator()(const std::vector<Value>& arguments) const
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
	Value Multiply<T>::operator()(const std::vector<Value>& arguments) const
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
	Value Divide<T>::operator()(const std::vector<Value>& arguments) const
	{
		const std::vector<T> convertedArguments{Utils::convert<T>(arguments)};
		// If there is a zero in the values [begin + 1, end)
		if(std::find(std::next(convertedArguments.begin()), convertedArguments.end(), static_cast<T>(0)) != convertedArguments.end())
			throw ScriptError("division by zero");
		return std::accumulate(std::next(convertedArguments.begin()), convertedArguments.end(), convertedArguments.front(), std::divides<T>());
	}
}

#endif
