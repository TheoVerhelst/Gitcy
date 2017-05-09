#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <map>
#include <regex>
#include <EvaluationNode.hpp>

// Forward declarations
class EvaluationTree;

// TODO remove static
class Parser
{
	public:
		Parser();
		
		/// Makes an evaluation tree out of Gitcy code.
		/// \param code The code to use.
		/// \returns A tree of evaluation nodes corresponding to the code.
		EvaluationTree constructTree(const std::string& code);

		/// Makes an evaluation tree out of Gitcy code, with a do statement
		/// enclosing the code, allowing to evaluate more than one tree.
		/// \param code The code to use.
		/// \returns A tree of evaluation nodes corresponding to the code.
		EvaluationTree constructMultipleTrees(const std::string& code);

	private:

		/// We use vector of strings in alot of places in this class.
		typedef std::vector<std::string> TokenVector;
		typedef TokenVector::const_iterator TokenIterator;

		// Parsing
		const std::string realLiteral;               ///< Regex string of a real number literal.
		const std::string integerLiteral;            ///< Regex string of an integer number literal.
		const std::string numberLiteral;             ///< Regex string of a number literal.
		const std::string stringLiteral;             ///< Regex string of a string literal.
		const std::string identifier;                ///< Regex string of an identifier.
		const std::string openingParenthesisLiteral; ///< Regex string of an opening parenthesis.
		const std::string closingParenthesisLiteral; ///< Regex string of a closing parenthesis.
		const std::string parenthesisLiteral;        ///< Regex string of a parenthesis.
		const std::regex realLiteralRegex;           ///< Regex object of a real number literal.
		const std::regex integerLiteralRegex;        ///< Regex object of an integer number literal.
		const std::regex stringLiteralRegex;         ///< Regex object of a string literal.
		const std::regex identifierRegex;            ///< Regex object of an identifier.
		const std::regex tokenRegex;                 ///< Regex object of a token.

		/// Map of characters to escape in string literals, when they are
		/// preceded by a backslash. For example, the character 'n' is
		/// translated to '\n'.
		const std::map<char, char> escapedCharacters;

		/// Convert a string of code to a list of tokens as defined by the regex
		/// tokenRegex.
		/// \param code The code to tokenize.
		/// \returns The list of tokens.
		TokenVector tokenize(std::string code);

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
		std::pair<TokenIterator, EvaluationTree> parseExpression(TokenIterator from, TokenIterator to);

		/// Parses a token, and returns the corresponding evaluation node.
		/// \param token The token to parse.
		/// \returns The corresponding evaluation node.
		EvaluationNode parseToken(const std::string& token);

		/// Finds the closing parenthesis corresponding to the opening
		/// parenthesis token pointed by the iterator \a from.
		/// \param from The starting iterator where to begin the search.
		/// \param to The end iterator where to stop the search.
		/// \returns An iterator between \a from and \a to if \a from points to
		/// an opening parenthesis token and if there is a matching closing
		/// parenthesis. If \a from points to another token, then returns \a
		/// from. Else, if there is not matching closing parenthesis, returns \a
		/// to.
		TokenIterator findClosingParenthesis(TokenIterator from, TokenIterator to);
};

#endif // PARSER_HPP
