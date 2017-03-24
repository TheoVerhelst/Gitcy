#include <algorithm>
#include <fstream>
#include <iostream>

#include <Interpreter.hpp>
#include <Function.hpp>
#include <ScriptError.hpp>
#include <Utils.hpp>

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
	_functions{*this},
	_filename(filename),
	_variables
	{
		{"print",  std::make_shared<Data>(_functions.print)},
		{"do",     std::make_shared<Data>(_functions.do_)},
		{"define", std::make_shared<Data>(_functions.define)},
		{"<",      std::make_shared<Data>(_functions.lowerThan)},
		{">",      std::make_shared<Data>(_functions.greaterThan)},
		{"<=",     std::make_shared<Data>(_functions.lowerEqual)},
		{">=",     std::make_shared<Data>(_functions.greaterEqual)},
		{"=",      std::make_shared<Data>(_functions.equal)},
		{"is",     std::make_shared<Data>(_functions.equal)},
		{"!=",     std::make_shared<Data>(_functions.notEqual)},
		{"and",    std::make_shared<Data>(_functions.and_)},
		{"or",     std::make_shared<Data>(_functions.or_)},
		{"+",      std::make_shared<Data>(_functions.add)},
		{"-",      std::make_shared<Data>(_functions.substract)},
		{"*",      std::make_shared<Data>(_functions.multiply)},
		{"/",      std::make_shared<Data>(_functions.divide)},
		{"%",      std::make_shared<Data>(_functions.modulo)},
		{"!",      std::make_shared<Data>(_functions.not_)},
		{"true",   std::make_shared<Data>(true)},
		{"false",  std::make_shared<Data>(false)},
		{"null",   std::make_shared<Data>(Null())}
	}
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
	evaluateTree(_evaluationTree);
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

Tree<EvaluationNode>::Ptr Interpreter::constructTree(const Interpreter::TokenVector& tokens)
{
	return parseExpression(tokens.begin(), tokens.end()).second;
}

std::pair<Interpreter::TokenIterator, Tree<EvaluationNode>::Ptr> Interpreter::parseExpression(Interpreter::TokenIterator from, Interpreter::TokenIterator to)
{
	TokenIterator pastIterator{from};
	Tree<EvaluationNode>::Ptr evaluationTree{Tree<EvaluationNode>::create(parseToken(*from))};

	// If we construct a function call expression
	if(evaluationTree->getValue().type() == typeid(FunctionCall))
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
			evaluationTree->addChild(result.second);
		}
	}

	return {pastIterator, evaluationTree};
}

EvaluationNode Interpreter::parseToken(const std::string& token)
{
	// Real literal
	if(std::regex_match(token, realLiteralRegex))
		return Data(stof(token));
	// Integer literal
	else if(std::regex_match(token, integerLiteralRegex))
		return Data(stoi(token));
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
		return Data(res);
	}
	// Identifier
	else if(std::regex_match(token, identifierRegex))
		return Identifier(token);
	// Function call
	else if(token == openingParenthesisLiteral)
		return FunctionCall();
	else
		throw ScriptError("Unrecognized token: \"" + token + "\"");
}

Data Interpreter::evaluateTree(const Tree<EvaluationNode>::Ptr& expression)
{
	Data res;
	const EvaluationNode node{expression->getValue()};
	if(node.type() == typeid(FunctionCall))
	{
		if(expression->numberChildren() == 0)
			return false;

		const Data& functionValue{evaluateTree(expression->getChild(0))};
		// Check that the first child is a function
		if(functionValue.type() != typeid(Function))
			throw ScriptError("First value in a function call is not a function (got type \"" + std::string(functionValue.type().name()) + "\")");

		const Function& function{boost::get<Function>(functionValue)};
		std::vector<Data> args;
		for(size_t i{1}; i < expression->numberChildren(); ++i)
			args.push_back(evaluateTree(expression->getChild(i)));
		res = function(args);
	}
	else if(node.type() == typeid(Data))
		res = boost::get<Data>(node);
	else if(node.type() == typeid(Identifier))
	{
		const Identifier identifier{boost::get<Identifier>(node)};
		auto it(_variables.find(identifier));
		if(it == _variables.end())
			throw ScriptError("Unknown variable: \"" + identifier + "\"");
		res = *(it->second);
	}

	return res;
}

Interpreter::TokenIterator Interpreter::findClosingParenthesis(Interpreter::TokenIterator from, Interpreter::TokenIterator to)
{
	int depth{0};
	for(;from != to; ++from)
	{
		if(*from == openingParenthesisLiteral)
			++depth;
		else if(*from == closingParenthesisLiteral)
			--depth;
		if(depth <= 0)
			break;
	}
	return from;
}

