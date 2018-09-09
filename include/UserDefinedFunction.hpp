#ifndef USER_DEFINED_FUNCTION_HPP
#define USER_DEFINED_FUNCTION_HPP

#include <Overload.hpp>
#include <SignatureType.hpp>
#include <EvaluationTree.hpp>

// Forward declarations
class Scope;

/// A user-defined function is a function defined in Gitcy code with the macro
/// "function". This class holds the body of the function as a part of the
/// evaluation tree, and manages the scope in order to enable a proper
/// parameters substitution.
/// The idea is to make a copy of the outer scope when the function is called,
/// and to inject the values of the arguments according to the parameter list.
class UserDefinedFunction : public Overload
{
	public:
		/// Creates a new user-defined function with the given parameters list,
		/// the function body, and the outer scope. A copy of the scope is done
		/// at call, so this is the state of the scope at call that matters.
		///
		/// \param pramaters The list of identifiers of the parameter list.
		/// \param functionBody The body of the user-defined function.
		/// \param scope The scope in which the function is being
		/// called and defined.
		UserDefinedFunction(const std::vector<Identifier> parameters,
				const EvaluationTree& functionBody, Scope& scope);

		/// Call the function with the given arguments, by first copying the
		/// scope given in the constructor, and then injecting the arguments in
		/// this local scope with the proper names.
		/// \param arguments The arguments to pass to the function.
		/// \returns The value resulting from the evaluation of the function
		/// body.
		virtual Value call(const std::vector<Value>& arguments) const override;

	private:
		/// The body of the function, will be evaluated each time the function
		/// is called. This is a value and not reference, since the orginal
		/// function body may be destructed at call time.
		const EvaluationTree _functionBody;

		/// The scope of execution of the function.
		Scope& _scope;

		/// The parameters, in order of declaration.
		const std::vector<Identifier> _parameters;
};

#endif // USER_DEFINED_FUNCTION_HPP
