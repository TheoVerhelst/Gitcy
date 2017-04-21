#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <BuiltinFunctions.hpp>
#include <Scope.hpp>
#include <EvaluationTree.hpp>

/// Main class. Reads a source code file and interprets it.
class Interpreter
{
	public:
		// Default constructor.
		Interpreter();
		
		/// \param filename The filename of the script to interpret.
		void loadFile(const std::string& filename);

		/// Interprets the script loaded at construction.
		Value interpret();
		
		void runPrompt();

	private:
		/// All the functions that can be called in the scripts. \see Functions
		BuiltinFunctions _functions;
		
		const std::string _prompt;

		/// The global scope.
		Scope _globalScope;
		
		/// After loading the script, this variables holds the script as a tree
		/// ready to be evaluated.
		EvaluationTree _evaluationTree;
};

#endif
