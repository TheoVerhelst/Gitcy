#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include <vector>
#include <map>
#include <regex>
#include <memory>
#include <Tree.hpp>
#include <EvaluationNode.hpp>
#include <Functions.hpp>

/// Main class. Reads a file given its filename and interprets it.
class Interpreter
{
	public:
		/// Constructor.
		/// \param filename The filename of the script to interpret.
		Interpreter(const std::string& filename);

		/// Interpret the script loaded at construction.
		void interpret();

	private:
		/// We use vector of strings in alot of places in this class.
		typedef std::vector<std::string> TokenVector;
		typedef TokenVector::const_iterator TokenIterator;

		friend class Functions;

		// Current script state

		/// All the functions that can be called in the scripts. \see Functions
		Functions _functions;

		/// The filename of the interpreted script. It is mainly used in error messages.
		const std::string _filename;

		/// The variables, as pairs of name/value.
		std::map<std::string, std::shared_ptr<Data>> _variables;

		/// After loading the script, this variables holds the script as a tree ready to be evaluated.
		Tree<EvaluationNode>::Ptr _evaluationTree;


		// Parsing
		static const std::string real_literal;              ///< Regex string of a real number literal.
		static const std::string integer_literal;           ///< Regex string of an integer number literal.
		static const std::string number_literal;            ///< Regex string of a number literal.
		static const std::string string_literal;            ///< Regex string of a string literal.
		static const std::string identifier;                ///< Regex string of an identifier.
		static const std::string open_parenthesis_literal;  ///< Regex string of an opening parenthesis. \TODO rename opening_parenthesis
		static const std::string close_parenthesis_literal; ///< Regex string of a closing parenthesis.
		static const std::string parenthesis_literal;       ///< Regex string of a parenthesis.
		static const std::regex real_literal_regex;         ///< Regex object of a real number literal.
		static const std::regex integer_literal_regex;      ///< Regex object of an integer number literal.
		static const std::regex string_literal_regex;       ///< Regex object of a string literal.
		static const std::regex identifier_regex;           ///< Regex object of an identifier.
		static const std::regex token_regex;                ///< Regex object of a token.

		/// Map of characters to escape in string literals, when they are
		/// preceded by an antislash `\`. For example, the character 'n' is
		/// translated to '\n'.
		static const std::map<char, char> escapedCharacters;

		// Methods

		/// Loads the script at filename _filename;
		void loadScript();

		/// Convert a string of code to a list of tokens as defined by the regex
		/// token_regex.
		/// \param code The code to tokenize.
		/// \returns The list of tokens.
		static TokenVector tokenize(std::string code);

		/// Makes an evaluation tree out of a list of tokens.
		/// \param tokens The list of token to use.
		/// \returns A tree of evaluation node corresponding to the code.
		static Tree<EvaluationNode>::Ptr constructTree(const TokenVector& tokens);

		/// Given two iterators of a token vector, makes a tree out of the
		/// expression starting at the first iterator. The second iterator has
		/// not to be the end of this expression, it is just used to know where
		/// the code ends.
		/// \param from An iterator to the first token of the expression to
		/// construct.
		/// \param to An ending iterator, should normally be the end iterator of
		/// the token vector.
		/// \returns A pair where \a first is an iterator pointing to the first
		/// token that is not part of the constructed expression, and \a second
		/// is the constructed tree.
		static std::pair<TokenIterator, Tree<EvaluationNode>::Ptr> parseExpression(TokenIterator from, TokenIterator to);

		/// Parses a token, and returns the corresponding evaluation node.
		/// \param token The token to parse.
		/// \returns The corresponding evaluation node.
		/// \TODO make this function return FunctionCall().
		static EvaluationNode parseToken(const std::string& token);

		/// Evaluates an evaluation tree, by calling recursively the functions
		/// and evaluating the values and identifiers.
		/// \param expression The evaluation tree to evaluate.
		/// \return The return value.
		Data evaluateTree(const Tree<EvaluationNode>::Ptr& expression);

		/// Finds the closing parenthesis corresponding to the opening
		/// parenthesis token pointed by the iterator \a from.
		/// \param from The starting iterator where to begin the search.
		/// \param to The end iterator where to stop the search.
		/// \returns An iterator between \a from and \a to if \a from points to
		/// an opening parenthesis token and if there is a matching closing
		/// parenthesis. If \a from points to another token, then returns \a
		/// from. Else, if there is not matching closing parenthesis, returns \a
		/// to.
		static TokenIterator findClosingParenthesis(TokenIterator from, TokenIterator to);
};

#endif
