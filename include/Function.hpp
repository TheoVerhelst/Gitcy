#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <ostream>
#include <vector>
#include <string>
#include <Data.hpp>
#include <Overload.hpp>

/// Class for functions defined in C++ but usable in scripts. These functions
/// have a limited number of overload, each overload can be variadic. We cannot
/// call any function with any arguments, some restrictions are applied. When a
/// function is called, the functions search the best overload that matches the
/// arguments, according to the following rules:
/// * If there is exactly one matching non-variadic overload, then this one is
/// chosen.
/// * Else, if there is exactly one matching variadic overload, then this one is
/// chose.
/// * Else, a ScriptError is raised, explaining the error.
///
/// \see Overload
class Function
{
	public:
		/// Constructor.
		/// \param overloads A list of overloads.
		Function(const std::vector<Overload>& overloads);

		/// C++ call operator, which effectively call the function of the first
		/// matching overload.
		/// \param arguments The arguments to pass to the overlaod functor.
		/// \returns The return value of the overload functor.
		Data operator()(const std::vector<Data>& arguments) const;

		/// Output operator overload.
		/// \param os The stream to output to.
		/// \param function The function to output.
		/// \returns os.
		friend std::ostream& operator<<(std::ostream& os, const Function& function);

	private:
		/// The list of overload.
		std::vector<Overload> _overloads;
};

#endif // FUNCTION_HPP
