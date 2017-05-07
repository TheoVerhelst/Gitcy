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

Value Function::operator()(const EvaluationTree& expression, Scope& scope)
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
			"Got:\n"
			"\t(" + Utils::join(", ", arguments.begin(), arguments.end()) + ")\n"
			"Overloads:\n" + Utils::toString(*this));
}

std::vector<Value> Function::evaluateArguments(const EvaluationTree& expression, Scope& scope)
{
	std::vector<Value> arguments;
	std::transform(expression.begin(), expression.end(), arguments.begin(),
		std::bind(BuiltinCallables::evaluate, std::placeholders::_1, std::ref(scope)));
	return arguments;
}

std::ostream& operator<<(std::ostream& os, const Function& function)
{
	for(auto& overload : function._overloads)
		os << "\t(" << *overload << ")" << std::endl;
	return os;
}
