#include <algorithm>
#include <fstream>
#include <iostream>
#include <ScriptError.hpp>
#include <Utils.hpp>
#include <BuiltinCallables.hpp>
#include <Interpreter.hpp>

const std::string Interpreter::realLiteral("\\d*\\.\\d*");
const std::string Interpreter::integerLiteral("\\d+");
const std::string Interpreter::stringLiteral("\"(?:[^\"]|\\\\\")*\"|'(?:[^']|\\\\')*'");
const std::string Interpreter::identifier("[\\w+%=!/<>&*|-]+");
const std::string Interpreter::openingParenthesisLiteral("(");
const std::string Interpreter::closingParenthesisLiteral(")");
const std::string Interpreter::parenthesisLiteral("\\(|\\)");

const std::regex Interpreter::realLiteralRegex(realLiteral);
const std::regex Interpreter::integerLiteralRegex(integerLiteral);
const std::regex Interpreter::stringLiteralRegex(stringLiteral);
const std::regex Interpreter::identifierRegex(identifier);
const std::regex Interpreter::tokenRegex("("+realLiteral+"|"+integerLiteral+"|"+stringLiteral+"|"+identifier+"|"+parenthesisLiteral+")[[:space:]]*");
const std::map<char, char> Interpreter::escapedCharacters
		{{'a', '\a'}, {'b', '\b'}, {'f', '\f'}, {'n', '\n'}, {'r', '\r'}, {'t', '\t'}, {'v', '\v'}};

Interpreter::Interpreter(const std::string& filename):
	_filename(filename),
	_globalScope
	{{
		{"print",    std::make_shared<Value>(_functions.print)},
		{"do",       std::make_shared<Value>(_functions.do_)},
		{"<",        std::make_shared<Value>(_functions.lowerThan)},
		{">",        std::make_shared<Value>(_functions.greaterThan)},
		{"<=",       std::make_shared<Value>(_functions.lowerEqual)},
		{">=",       std::make_shared<Value>(_functions.greaterEqual)},
		{"=",        std::make_shared<Value>(_functions.equal)},
		{"is",       std::make_shared<Value>(_functions.equal)},
		{"!=",       std::make_shared<Value>(_functions.notEqual)},
		{"and",      std::make_shared<Value>(_functions.and_)},
		{"or",       std::make_shared<Value>(_functions.or_)},
		{"+",        std::make_shared<Value>(_functions.add)},
		{"-",        std::make_shared<Value>(_functions.substract)},
		{"*",        std::make_shared<Value>(_functions.multiply)},
		{"/",        std::make_shared<Value>(_functions.divide)},
		{"%",        std::make_shared<Value>(_functions.modulo)},
		{"!",        std::make_shared<Value>(_functions.not_)},
		{"true",     std::make_shared<Value>(true)},
		{"false",    std::make_shared<Value>(false)},
		{"null",     std::make_shared<Value>(Null())},
		{"define",   std::make_shared<Value>(std::shared_ptr<Callable>(new BuiltinCallables::Define()))},
		{"if",       std::make_shared<Value>(std::shared_ptr<Callable>(new BuiltinCallables::If()))},
		{"function", std::make_shared<Value>(std::shared_ptr<Callable>(new BuiltinCallables::DefineFunction()))},
	}}
{
	loadScript();
}

void Interpreter::loadScript()
{
	std::ifstream stream{_filename};
	const std::string fileContent{std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>()};
	_evaluationTree = constructTree(tokenize(fileContent));
}

void Interpreter::interpret()
{
	BuiltinCallables::Evaluate().call(_evaluationTree, _globalScope);
}

Interpreter::TokenVector Interpreter::tokenize(std::string code)
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

EvaluationTree Interpreter::constructTree(const Interpreter::TokenVector& tokens)
{
	return parseExpression(tokens.begin(), tokens.end()).second;
}

std::pair<Interpreter::TokenIterator, EvaluationTree> Interpreter::parseExpression(Interpreter::TokenIterator from, Interpreter::TokenIterator to)
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

EvaluationNode Interpreter::parseToken(const std::string& token)
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

Interpreter::TokenIterator Interpreter::findClosingParenthesis(Interpreter::TokenIterator from, Interpreter::TokenIterator to)
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
