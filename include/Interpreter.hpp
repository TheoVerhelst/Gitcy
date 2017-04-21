#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <BuiltinFunctions.hpp>
#include <Scope.hpp>
#include <EvaluationTree.hpp>

/// Main class. Reads a source code file and interprets it.
class Interpreter
{
	public:
		/// Constructor.
		/// \param filename The filename of the script to interpret.
		explicit Interpreter(const std::string& filename);

		/// Interprets the script loaded at construction.
		void interpret();

	private:
		/// All the functions that can be called in the scripts. \see Functions
		BuiltinFunctions _functions;

		/// The filename of the interpreted script. It is mainly used in error
		/// messages.
		const std::string _filename;

		/// The global scope.
		Scope _globalScope;

		/// After loading the script, this variables holds the script as a tree
		/// ready to be evaluated.
		EvaluationTree _evaluationTree;

		/// Loads the script at filename _filename;
		void loadScript();
};

#endif
