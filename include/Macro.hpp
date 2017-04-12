#ifndef MACRO_HPP
#define MACRO_HPP

#include <map>
#include <string>
#include <memory>
#include <Tree.hpp>
#include <EvaluationNode.hpp>
#include <Scope.hpp>

// Forward declarations
class Value;

class Macro
{
	public:
		// Destructor.
		virtual ~Macro() = default;


		virtual Value call(const Tree<EvaluationNode>::Ptr& expression, const Scope& scope) = 0;
};

#endif // MACRO_HPP
