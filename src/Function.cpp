#include <Utils.hpp>
#include <ScriptError.hpp>
#include <BuiltinCallables.hpp>
#include <Overload.hpp>
#include <EvaluationTree.hpp>
#include <Function.hpp>

Function::Function(const std::vector<std::shared_ptr<Overload>>& overloads):
	_overloads{overloads}
{
}

Value Function::operator()(const EvaluationTree& expression, Scope& scope) const
{
	const std::vector<Value> arguments(evaluateArguments(expression, scope));

	// Find the overloads that matches the arguments, and split them according to their variadicity (variadicness ?)
	std::vector<std::shared_ptr<Overload>> variadicCandidates, nonVariadicCandidates;
	for(auto& overload : _overloads)
	{
		if(overload->matches(arguments))
		{
			if(overload->isVariadic())
				variadicCandidates.push_back(overload);
			else
				nonVariadicCandidates.push_back(overload);
		}
	}

	for(auto& candidateSet : {std::ref(nonVariadicCandidates), std::ref(variadicCandidates)})
	{
		if(candidateSet.get().size() > 0)
		{
			if(candidateSet.get().size() > 1)
			{
				throw ScriptError("Ambiguous overload resolution for given arguments:\n"
						"Got:\n"
						"\t(" + Utils::join(", ", arguments.begin(), arguments.end()) + ")\n"
						"Candidate overloads:\n" +
						Utils::toString(Function(candidateSet.get())));
			}
			else
				return candidateSet.get().front()->call(arguments);
		}
	}

	throw ScriptError("No overload found for given arguments:\n"
			"Arguments:\n"
			"\t(" + Utils::join(", ", arguments.begin(), arguments.end()) + ")\n"
			"Of type:\n"
			"\t(" + std::accumulate(arguments.begin(), arguments.end(), std::string(),
				[](const std::string& a, const Value& b)
				{
					return a + (a.empty() ? "" : ", ") + b.getTypeName();
				}) + ")\n"
			"Do not match any of the overloads:\n" + Utils::toString(*this));
}

std::vector<Value> Function::evaluateArguments(const EvaluationTree& expression, Scope& scope)
{
	std::vector<Value> arguments;
	for(auto it(std::next(expression.begin())); it != expression.end(); ++it)
		arguments.push_back(BuiltinCallables::evaluate(*it, scope));
	return arguments;
}

std::ostream& operator<<(std::ostream& os, const Function& function)
{
	for(auto& overload : function._overloads)
		os << "\t(" << *overload << ")" << std::endl;
	return os;
}
