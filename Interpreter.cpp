#include <algorithm>
#include <fstream>
#include <iostream>

#include "Interpreter.hpp"
#include "Function.hpp"
#include "ScriptError.hpp"
#include "Utils.hpp"

const std::string Interpreter::real_literal("\\d*\\.\\d*");
const std::string Interpreter::integer_literal("\\d+");
const std::string Interpreter::string_literal("\"(?:[^\"]|\\\\\")*\"|'(?:[^']|\\\\')*'");
const std::string Interpreter::identifier("[\\w+%=!/<>&*|-]+");
const std::string Interpreter::open_parenthesis_literal("(");
const std::string Interpreter::close_parenthesis_literal(")");
const std::string Interpreter::parenthesis_literal("\\(|\\)");

const std::regex Interpreter::real_literal_regex(real_literal);
const std::regex Interpreter::integer_literal_regex(integer_literal);
const std::regex Interpreter::string_literal_regex(string_literal);
const std::regex Interpreter::identifier_regex(identifier);
const std::regex Interpreter::token_regex("("+real_literal+"|"+integer_literal+"|"+string_literal+"|"+identifier+"|"+parenthesis_literal+")[[:space:]]*");
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
		{"==",     std::make_shared<Data>(_functions.equal)},
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

Interpreter::VecStr Interpreter::tokenize(std::string code)
{
	VecStr tokens, errorTokens;

	std::copy(std::sregex_token_iterator(code.begin(), code.end(), token_regex, 1),
			std::sregex_token_iterator(),
			std::back_inserter(tokens));
	std::copy_if(std::sregex_token_iterator(code.begin(), code.end(), token_regex, -1),
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

Tree<EvaluationNode>::Ptr Interpreter::constructTree(const Interpreter::VecStr& tokens)
{
	return parseExpression(tokens.begin(), tokens.end()).second;
}

std::pair<Interpreter::VecStr::const_iterator, Tree<EvaluationNode>::Ptr> Interpreter::parseExpression(Interpreter::VecStr::const_iterator from, Interpreter::VecStr::const_iterator to)
{
	std::pair<VecStr::const_iterator, Tree<EvaluationNode>::Ptr> res{from, nullptr};

	// If we construct a function call expression
	if(*from == open_parenthesis_literal)
	{
		// Check that there is a closing parenthesis
		const auto closingParenthesis(findClosingParenthesis(from, to));
		if(closingParenthesis == to)
			throw ScriptError("No closing parenthesis has been found");

		res.first = closingParenthesis;
		res.second = Tree<EvaluationNode>::create(FunctionCall());

		for(auto it(from + 1); it != closingParenthesis; ++it)
		{
			auto result(parseExpression(it, to));
			it = result.first;
			res.second->addChild(result.second);
		}
	}
	else
		res.second = Tree<EvaluationNode>::create(parseToken(*from));

	return res;
}

EvaluationNode Interpreter::parseToken(const std::string& token)
{
	// Real literal
	if(std::regex_match(token, real_literal_regex))
		return Data(stof(token));
	// Integer literal
	else if(std::regex_match(token, integer_literal_regex))
		return Data(stoi(token));
	// String literal
	else if(std::regex_match(token, string_literal_regex))
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
	else if(std::regex_match(token, identifier_regex))
		return Identifier(token);
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

Interpreter::VecStr::const_iterator Interpreter::findClosingParenthesis(Interpreter::VecStr::const_iterator from, Interpreter::VecStr::const_iterator to)
{
	int depth{0};
	for(;from != to; ++from)
	{
		if(*from == open_parenthesis_literal)
			++depth;
		else if(*from == close_parenthesis_literal)
			--depth;
		// TODO change to <=
		if(depth == 0)
			break;
	}
	return from;
}

