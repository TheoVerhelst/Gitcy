#ifndef USER_DEFINED_FUNCTION_HPP
#define USER_DEFINED_FUNCTION_HPP

#include <Overload.hpp>
#include <SignatureType.hpp>

// Forward declarations
class Scope;
class EvaluationTree;

/// A user-defined function is a function defined in Gitcy code with the macro
/// "function". This class holds the body of the function as a part of the
/// evaluation tree, and manages the scope in order to enable a proper
/// parameters and arguments substitution.
/// The idea is to make a copy of the outer scope when the function is called,
/// and to add as many variable in this local scope as there are parameters to
/// the function. These variables will of course have the values given as
/// arguments, and the proper names.
class UserDefinedFunction : public Overload
{
	public:
		/// Creates a new user-defined function with the given body, and the
		/// outer scope. A copy of the scope is done at call, so this
		/// is the state of the scope at call that matters: a variable not yet
		/// defined when the function is defined could be available in the
		/// function body, as soon as this variable is defined when the function
		/// is called.
		/// \param functionBody The body of the user-defined function.
		/// \param scope The scope in which the function is being
		/// called and defined.
		UserDefinedFunction(const EvaluationTree& functionBody, Scope& scope);
		
		/// Call the function with the given arguments, by first copying the
		/// scope given in the constructor, and then injecting the arguments in
		/// this local scope with the proper names.
		/// \param arguments The arguments to pass to the function.
		/// \returns The value resulting from the evaluation of the function
		/// body.
		virtual Value call(const std::vector<Value>& arguments) const override;

	private:
		/// Generates a std::vector which has only unspecified types, but the 
		/// same number of elements as the number of identifiers in the first
		/// childs of the function body. i.e. if the function body starts with
		/// two identifiers and continues with a function call, then the 
		/// returned vector will have two elements).
		/// \param functionBody The function body, as an evaluation tree.
		/// \returns The proper signature vector.
		static std::vector<SignatureType> generateSignature(const EvaluationTree& functionBody);
		
		static std::vector<std::string> generateParameterNames(const EvaluationTree& functionBody);
		
		const EvaluationTree& _functionBody;
		Scope& _scope;
		const std::vector<std::string> _parameterNames;
};

#endif // USER_DEFINED_FUNCTION_HPP
