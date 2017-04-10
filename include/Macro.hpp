#ifndef MACRO_HPP
#define MACRO_HPP

#include <map>
#include <string>
#include <memory>
#include <Tree.hpp>
#include <EvaluationNode.hpp>

// Forward declarations
class Value;

class Macro
{
	public:
		// Destructor.
		virtual ~Macro() = default;


		virtual Value call(const Tree<EvaluationNode>::Ptr&, std::map<std::string, std::shared_ptr<Value>>&) = 0;
};

#endif // MACRO_HPP
