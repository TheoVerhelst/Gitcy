#ifndef SCOPE_HPP
#define SCOPE_HPP

#include <map>
#include <string>
#include <memory>

// Forward declarations
class Value;

/// Holds all local variables in a context of execution, and their respective
/// identifiers.
class Scope
{
	public:
		/// Constructor.
		/// \param variables The variables of the scope.
		explicit Scope(const std::map<std::string, std::shared_ptr<Value>>& variables);

		/// Get the variable bound to the name \a name.
		/// \param identifier The name of the variable to get.
		/// \returns The value of the variable.
		/// \throws std::out_of_range If there is no variable bound to the
		/// given name.
		const Value& getVariable(const std::string& identifier) const;

		/// Override a binding in the scope. If there was no such binding
		/// previously, it is created.
		/// \param identifier The identifier to use.
		/// \param value The value to bind to the identifier.
		void setVariable(const std::string& identifier, const Value& value);

	private:
		/// All the variable of the scope.
		std::map<std::string, std::shared_ptr<Value>> _variables;
};

#endif // SCOPE_HPP
