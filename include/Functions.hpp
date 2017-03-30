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
class Data;

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
	/// Implements print.
	class Print : public Overload
	{
		public:
			/// Constructor.
			Print();

			/// \see Overload::operator().
			virtual Data operator()(const std::vector<Data>& arguments) const override;
	};

	/// Implements do.
	class Do : public Overload
	{
		 public:
			/// Constructor.
			Do();

			/// see Overload::operator().
			virtual Data operator()(const std::vector<Data>& arguments) const override;
	};

	/// Implements define.
	class Define : public Overload
	{
		 public:
			/// Constructor.
			Define();

			/// see Overload::operator().
			virtual Data operator()(const std::vector<Data>& arguments) const override;
	};

	/// Implements lowerThan.
	/// \tparam T Either int or double.
	template <typename T>
	class LowerThan : public Overload
	{
		 public:
			/// Constructor.
			LowerThan();

			/// see Overload::operator().
			virtual Data operator()(const std::vector<Data>& arguments) const override;
	};

	/// Implements greaterThan.
	/// \tparam T Either int or double.
	template <typename T>
	class GreaterThan : public Overload
	{
		 public:
			/// Constructor.
			GreaterThan();

			/// see Overload::operator().
			virtual Data operator()(const std::vector<Data>& arguments) const override;
	};

	/// Implements lowerEqual.
	/// \tparam T Either int or double.
	template <typename T>
	class LowerEqual : public Overload
	{
		 public:
			/// Constructor.
			LowerEqual();

			/// see Overload::operator().
			virtual Data operator()(const std::vector<Data>& arguments) const override;
	};

	/// Implements greaterEqual.
	/// \tparam T Either int or double.
	template <typename T>
	class GreaterEqual : public Overload
	{
		 public:
			/// Constructor.
			GreaterEqual();

			/// see Overload::operator().
			virtual Data operator()(const std::vector<Data>& arguments) const override;
	};

	/// Implements equal.
	/// \tparam T Either int, double, std::string or bool.
	template <typename T>
	class Equal : public Overload
	{
		 public:
			/// Constructor.
			Equal();

			/// see Overload::operator().
			virtual Data operator()(const std::vector<Data>& arguments) const override;
	};

	/// Implements notEqual.
	/// \tparam T Either int, double, std::string or bool.
	template <typename T>
	class NotEqual : public Overload
	{
		 public:
			/// Constructor.
			NotEqual();

			/// see Overload::operator().
			virtual Data operator()(const std::vector<Data>& arguments) const override;
	};

	/// Implements and.
	class And : public Overload
	{
		 public:
			/// Constructor.
			And();

			/// see Overload::operator().
			virtual Data operator()(const std::vector<Data>& arguments) const override;
	};

	/// Implements or.
	class Or : public Overload
	{
		 public:
			/// Constructor.
			Or();

			/// see Overload::operator().
			virtual Data operator()(const std::vector<Data>& arguments) const override;
	};

	/// Implements add.
	/// \tparam T Either int, double or string.
	template <typename T>
	class Add : public Overload
	{
		 public:
			/// Constructor.
			Add();

			/// see Overload::operator().
			virtual Data operator()(const std::vector<Data>& arguments) const override;
	};

	/// Implements substract.
	/// \tparam T Either int or double.
	template <typename T>
	class Substract : public Overload
	{
		 public:
			/// Constructor.
			Substract();

			/// see Overload::operator().
			virtual Data operator()(const std::vector<Data>& arguments) const override;
	};

	/// Implements multiply.
	/// \tparam T Either int or double.
	template <typename T>
	class Multiply : public Overload
	{
		 public:
			/// Constructor.
			Multiply();

			/// see Overload::operator().
			virtual Data operator()(const std::vector<Data>& arguments) const override;
	};

	/// Implements divide.
	/// \tparam T Either int or double.
	template <typename T>
	class Divide : public Overload
	{
		 public:
			/// Constructor.
			Divide();

			/// see Overload::operator().
			virtual Data operator()(const std::vector<Data>& arguments) const override;
	};

	/// Implements modulo for integers.
	class Modulo : public Overload
	{
		 public:
			/// Constructor.
			Modulo();

			/// see Overload::operator().
			virtual Data operator()(const std::vector<Data>& arguments) const override;
	};

	/// Implements modulo for double.
	class DoubleModulo : public Overload
	{
		 public:
			/// Constructor.
			DoubleModulo();

			/// see Overload::operator().
			virtual Data operator()(const std::vector<Data>& arguments) const override;
	};

	/// Implements not.
	class Not : public Overload
	{
		 public:
			/// Constructor.
			Not();

			/// see Overload::operator().
			virtual Data operator()(const std::vector<Data>& arguments) const override;
	};


}

#include <Data.hpp>
#include <ScriptError.hpp>

namespace BuiltinOverloads
{
	template <typename T>
	LowerThan<T>::LowerThan():
		Overload{{SignatureType::create<T>(), SignatureType::create<T>()}, true}
	{
	}

	template <typename T>
	Data LowerThan<T>::operator()(const std::vector<Data>& arguments) const
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
	Data GreaterThan<T>::operator()(const std::vector<Data>& arguments) const
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
	Data LowerEqual<T>::operator()(const std::vector<Data>& arguments) const
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
	Data GreaterEqual<T>::operator()(const std::vector<Data>& arguments) const
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
	Data Equal<T>::operator()(const std::vector<Data>& arguments) const
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
	Data NotEqual<T>::operator()(const std::vector<Data>& arguments) const
	{
		return Not()({Equal<T>()(arguments)});
	}

	template <typename T>
	Add<T>::Add():
		Overload{{SignatureType::create<T>()}, true}
	{
	}

	template <typename T>
	Data Add<T>::operator()(const std::vector<Data>& arguments) const
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
	Data Substract<T>::operator()(const std::vector<Data>& arguments) const
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
	Data Multiply<T>::operator()(const std::vector<Data>& arguments) const
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
	Data Divide<T>::operator()(const std::vector<Data>& arguments) const
	{
		const std::vector<T> convertedArguments{Utils::convert<T>(arguments)};
		// If there is a zero in the values [begin + 1, end)
		if(std::find(std::next(convertedArguments.begin()), convertedArguments.end(), static_cast<T>(0)) != convertedArguments.end())
			throw ScriptError("division by zero");
		return std::accumulate(std::next(convertedArguments.begin()), convertedArguments.end(), convertedArguments.front(), std::divides<T>());
	}
}

#endif
