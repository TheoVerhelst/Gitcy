#include <sstream>
#include <algorithm>
#include <functional>
#include <Utils.hpp>
#include <ScriptError.hpp>
#include <Data.hpp>
#include <Function.hpp>

Function::Function(const std::vector<Overload>& overloads):
	_overloads{overloads}
{
}

Data Function::operator()(const std::vector<Data>& arguments) const
{
	// Find the overloads that matches the arguments, and split them according to their variadicity (variadicness ?)
	std::vector<Overload> variadicCandidates, nonVariadicCandidates;
	for(auto& overload : _overloads)
	{
		if(overload.matches(arguments))
		{
			if(overload.isVariadic())
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
						"Candidate overloads:\n"
						"\t(" +  Utils::join(")\n\t(", candidateSet.get().begin(), candidateSet.get().end()) + ")\n");
			}
			else
				return candidateSet.get().front()(arguments);
		}
	}

	throw ScriptError("No overload found for given arguments:\n"
			"Got:\n"
			"\t(" + Utils::join(", ", arguments.begin(), arguments.end()) + ")\n"
			"Overloads:\n"
			"\t(" + Utils::join(")\n\t(", _overloads.begin(), _overloads.end()) + ")\n");


}

std::ostream& operator<<(std::ostream& os, const Function& function)
{
	return os << "<Function(" << Utils::join(" | ", function._overloads.begin(), function._overloads.end()) << ")>";
}
