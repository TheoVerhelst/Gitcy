#ifndef SCOPE_HPP
#define SCOPE_HPP

#include <map>
#include <string>
#include <Value.hpp>

class Scope
{
	public:
		/// Constructor.
		/// \param variables The variables of the scope.
		Scope(std::map<std::string, std::shared_ptr<Value>> variables);

		/// Get the variable bound to the name \a name.
		/// \param name The name of the variable to get.
		/// \returns The value of the variable.
		/// \throws std::out_of_range If there is no variable bound to the
		/// given name.
		const Value& getVariable(const std::string& name) const;

		void setVariable(const std::string& name, const Value& newValue);

	private:
		std::map<std::string, std::shared_ptr<Value>> _variables;
};

#endif // SCOPE_HPP
