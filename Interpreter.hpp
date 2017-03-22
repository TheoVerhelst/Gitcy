#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include <vector>
#include <map>
#include <regex>
#include <memory>
#include "Tree.hpp"
#include "EvaluationNode.hpp"
#include "Functions.hpp"

/// Main class. Reads a file given its filename and interprets it.
class Interpreter
{
	public:
		Interpreter(const std::string& filename);
		void interpret();

	private:
		typedef std::vector<std::string> VecStr;

		friend class Functions;

		// Current script state
		Functions _functions;
		const std::string _filename;
		std::map<std::string, std::shared_ptr<Data>> _variables;
		Tree<EvaluationNode>::Ptr _evaluationTree;


		// Parsing
		static const std::string real_literal;
		static const std::string integer_literal;
		static const std::string number_literal;
		static const std::string string_literal;
		static const std::string identifier;
		static const std::string open_parenthesis_literal;
		static const std::string close_parenthesis_literal;
		static const std::string parenthesis_literal;
		static const std::regex real_literal_regex;
		static const std::regex integer_literal_regex;
		static const std::regex string_literal_regex;
		static const std::regex identifier_regex;
		static const std::regex token_regex;
		static const std::map<char, char> escapedCharacters;

		// Methods
		void loadScript();
		static VecStr tokenize(std::string code);
		static Tree<EvaluationNode>::Ptr constructTree(const VecStr& tokens);
		/// Returns an iterator to the last token of the expression
		/// and the evaluation tree representing the expression
		static std::pair<VecStr::const_iterator, Tree<EvaluationNode>::Ptr> parseExpression(VecStr::const_iterator from, VecStr::const_iterator to);
		static EvaluationNode parseToken(const std::string& token);
		Data evaluateTree(const Tree<EvaluationNode>::Ptr& expression);
		static VecStr::const_iterator findClosingParenthesis(VecStr::const_iterator from, VecStr::const_iterator to);
};

#endif
