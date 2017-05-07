#include <algorithm>
#include <EvaluationTree.hpp>
#include <ScriptError.hpp>
#include <Utils.hpp>
#include <Parser.hpp>

const std::string Parser::realLiteral("\\d*\\.\\d*");
const std::string Parser::integerLiteral("\\d+");
const std::string Parser::stringLiteral("\"(?:[^\"]|\\\\\")*\"|'(?:[^']|\\\\')*'");
const std::string Parser::identifier("[\\w+%=!/<>&*|-]+");
const std::string Parser::openingParenthesisLiteral("(");
const std::string Parser::closingParenthesisLiteral(")");
const std::string Parser::parenthesisLiteral("\\(|\\)");

const std::regex Parser::realLiteralRegex(realLiteral);
const std::regex Parser::integerLiteralRegex(integerLiteral);
const std::regex Parser::stringLiteralRegex(stringLiteral);
const std::regex Parser::identifierRegex(identifier);
const std::regex Parser::tokenRegex("[[:space:]]*("+realLiteral+"|"+integerLiteral+"|"+stringLiteral+"|"+identifier+"|"+parenthesisLiteral+")[[:space:]]*");
const std::map<char, char> Parser::escapedCharacters
		{{'a', '\a'}, {'b', '\b'}, {'f', '\f'}, {'n', '\n'}, {'r', '\r'}, {'t', '\t'}, {'v', '\v'}};

EvaluationTree Parser::constructTree(const std::string& code)
{
	const TokenVector tokens{tokenize(code)};
	return parseExpression(tokens.begin(), tokens.end()).second;
}

EvaluationTree Parser::constructMultipleTree(const std::string& code)
{
	// The implicit "do" statement allows to evaluate more than one tree
	return constructTree(openingParenthesisLiteral + "do " + code + closingParenthesisLiteral);
}

Parser::TokenVector Parser::tokenize(std::string code)
{
	TokenVector tokens, errorTokens;

	std::copy(std::sregex_token_iterator(code.begin(), code.end(), tokenRegex, 1),
			std::sregex_token_iterator(),
			std::back_inserter(tokens));
	std::copy_if(std::sregex_token_iterator(code.begin(), code.end(), tokenRegex, -1),
			std::sregex_token_iterator(),
			std::back_inserter(errorTokens),
			[](const std::string& dismatch)
			{
				return not dismatch.empty();
			});

	if(not errorTokens.empty())
		throw ScriptError("Unrecognized tokens while parsing: `" + Utils::join("`, `", errorTokens.begin(), errorTokens.end()) + "`");

	return tokens;
}

std::pair<Parser::TokenIterator, EvaluationTree> Parser::parseExpression(Parser::TokenIterator from, Parser::TokenIterator to)
{
	TokenIterator pastIterator{from};
	const EvaluationNode node{parseToken(*from)};
	std::vector<EvaluationTree> childs;

	// If we construct a call expression
	if(node.type() == typeid(Call))
	{
		// Check that there is a closing parenthesis
		const auto closingParenthesis(findClosingParenthesis(from, to));
		if(closingParenthesis == to)
			throw ScriptError("No closing parenthesis has been found");

		pastIterator = closingParenthesis;

		// Add childs by evaluating following tokens
		for(auto it(from + 1); it != closingParenthesis; ++it)
		{
			auto result(parseExpression(it, to));
			it = result.first;
			childs.push_back(result.second);
		}
	}

	return {pastIterator, {node, childs}};
}

EvaluationNode Parser::parseToken(const std::string& token)
{
	// Real literal
	if(std::regex_match(token, realLiteralRegex))
		return Value(stof(token));
	// Integer literal
	else if(std::regex_match(token, integerLiteralRegex))
		return Value(stoi(token));
	// String literal
	else if(std::regex_match(token, stringLiteralRegex))
	{
		std::string res;
		for(auto it(token.begin() + 1); it != token.end() - 1; ++it)
		{
			if(*it == '\\')
			{
				char nextChar{*std::next(it)};
				auto replaceIt(escapedCharacters.find(nextChar));
				if(replaceIt != escapedCharacters.end())
					res += replaceIt->second;
				else
					res += nextChar;
				++it;
			}
			else
				res += *it;
		}
		return Value(res);
	}
	// Identifier
	else if(std::regex_match(token, identifierRegex))
		return Identifier(token);
	// Function call
	else if(token == openingParenthesisLiteral)
		return Call();
	else
		throw ScriptError("Unrecognized token: \"" + token + "\"");
}

Parser::TokenIterator Parser::findClosingParenthesis(Parser::TokenIterator from, Parser::TokenIterator to)
{
	int depth{0};
	while(from != to)
	{
		if(*from == openingParenthesisLiteral)
			++depth;
		else if(*from == closingParenthesisLiteral)
			--depth;
		if(depth <= 0)
			break;
		++from;
	}
	return from;
}
