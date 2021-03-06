#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <ostream>
#include <vector>
#include <string>
#include <memory>
#include <Callable.hpp>

// Forward declarations
class Overload;

/// Class for functions usable in scripts. These functions have a limited number
/// of overload, each overload can be variadic. We cannot call any function with
/// any arguments, some restrictions are applied. When a function is called, the
/// functions search the best overload that matches the arguments, according to
/// the following rules:
/// * If there is exactly one matching non-variadic overload, then this one is
/// chosen.
/// * Else, if there is exactly one matching variadic overload, then this one is
/// chose.
/// * Else, a ScriptError is raised, explaining the error.
///
/// \see Overload
class Function final
{
	public:
		/// Constructor.
		/// \param overloads A list of overloads.
		explicit Function(const std::vector<std::shared_ptr<Overload>>& overloads);

		/// Calls the function pointer of the first matching overload.
		/// \param expression The expression of the arguments to pass to the overload functor.
		/// \returns The return value of the overload functor.
		Value operator()(const EvaluationTree& expression, Scope& scope) const;

		/// Output operator overload.
		/// \param os The stream to output to.
		/// \param function The function to output.
		/// \returns os.
		friend std::ostream& operator<<(std::ostream& os, const Function& function);

	private:
		static std::vector<Value> evaluateArguments(const EvaluationTree& expression, Scope& scope);

		/// The list of overloads.
		std::vector<std::shared_ptr<Overload>> _overloads;
};

#endif // FUNCTION_HPP
