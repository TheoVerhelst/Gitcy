#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include <istream>
#include <BuiltinFunctions.hpp>
#include <Scope.hpp>
#include <EvaluationTree.hpp>
#include <Parser.hpp>

/// Main class. Reads a source code file and interprets it.
class Interpreter
{
	public:
		// Default constructor.
		Interpreter();

		/// Loads the source code from an input stream.
		/// \param stream An input stream from which read the source code.
		void loadFromStream(std::istream& stream);

		/// Interprets the script loaded at construction.
		Value interpret();

		void runPrompt();

	private:
		/// All the functions that can be called in the scripts. \see Functions
		BuiltinFunctions _functions;

		const std::string _prompt;

		Parser _parser;

		/// The global scope.
		Scope _globalScope;

		/// After loading the script, this variables holds the script as a tree
		/// ready to be evaluated.
		EvaluationTree _evaluationTree;
};

#endif
