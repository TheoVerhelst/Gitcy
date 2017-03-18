#include <algorithm>
#include <fstream>
#include <iostream>

#include "Interpreter.hpp"
#include "Function.hpp"
#include "ScriptError.hpp"

const std::string Interpreter::identifier("[\\w+%=!/<>&*|-]+");
const std::string Interpreter::number_literal("\\d+|\\d*\\.\\d*");
const std::string Interpreter::string_literal("\"([^\"]|\\\\\")*\"|'([^']|\\\\')*'");
const std::string Interpreter::open_parenthesis_literal("(");
const std::string Interpreter::close_parenthesis_literal(")");
const std::string Interpreter::parenthesis_literal("\\(|\\)");

const std::regex Interpreter::identifier_regex(identifier);
const std::regex Interpreter::number_literal_regex(number_literal);
const std::regex Interpreter::string_literal_regex("("+string_literal+")");
const std::regex Interpreter::token_regex("("+number_literal+"|"+string_literal+"|"+identifier+"|"+parenthesis_literal+")\\s*");
const std::regex Interpreter::value_regex(identifier+"|"+string_literal+"|"+number_literal);
const std::regex Interpreter::space_regex("[[:space:]]*");

Interpreter::Interpreter(const std::string& filename):
	m_functions{*this},
	m_filename(filename),
	m_variables
	{
		{"print",  std::make_shared<Data>(m_functions.print)},
		{"do",     std::make_shared<Data>(m_functions.do_)},
		{"define", std::make_shared<Data>(m_functions.define)},
		{"<",      std::make_shared<Data>(m_functions.lowerThan)},
		{">",      std::make_shared<Data>(m_functions.greaterThan)},
		{"<=",     std::make_shared<Data>(m_functions.lowerEqual)},
		{">=",     std::make_shared<Data>(m_functions.greaterEqual)},
		{"==",     std::make_shared<Data>(m_functions.equal)},
		{"is",     std::make_shared<Data>(m_functions.equal)},
		{"!=",     std::make_shared<Data>(m_functions.notEqual)},
		{"and",    std::make_shared<Data>(m_functions.and_)},
		{"or",     std::make_shared<Data>(m_functions.or_)},
		{"+",      std::make_shared<Data>(m_functions.add)},
		{"-",      std::make_shared<Data>(m_functions.substract)},
		{"*",      std::make_shared<Data>(m_functions.multiply)},
		{"/",      std::make_shared<Data>(m_functions.divide)},
		{"%",      std::make_shared<Data>(m_functions.modulo)},
		{"!",      std::make_shared<Data>(m_functions.not_)},
		{"true",   std::make_shared<Data>(true)},
		{"false",  std::make_shared<Data>(false)},
		{"null",   std::make_shared<Data>(Null())}
	}
{
	loadScript();
}

void Interpreter::loadScript()
{
	std::ifstream stream(m_filename);
	std::string fileContent((std::istreambuf_iterator<char>(stream)), (std::istreambuf_iterator<char>()));

	auto tokens(tokenize(fileContent));
	discardSpaces(tokens);
	m_evaluationTree = constructTree(tokens);
}

void Interpreter::interpret()
{
	evaluateTree(m_evaluationTree);
}

Interpreter::VecStr Interpreter::tokenize(std::string code)
{
	VecStr first, second, err;
	std::smatch m;

	// First tokenization, match string literal
	// This step must be done before everything else because
	// words in string must not be matched.
	while(regex_search(code, m, string_literal_regex))
	{
		if(m.prefix().str() != "")
			first.push_back(m.prefix().str());
		first.push_back(m[1].str());
		code = m.suffix().str();
	}
	first.push_back(code);

	// Second tokenization of every submatch
	for(auto& tok : first)
	{
		copy(std::sregex_token_iterator(tok.begin(), tok.end(), token_regex, 1),
	    	 std::sregex_token_iterator(),
			 std::back_inserter(second));
		copy(std::sregex_token_iterator(tok.begin(), tok.end(), token_regex, -1),
	    	 std::sregex_token_iterator(),
			 std::back_inserter(err));
	}

	// Strip spaces from errors
	for(long int i{0}; i < static_cast<long int>(err.size()); ++i)
	{
		if(std::regex_match(err[i], space_regex))
		{
			err.erase(err.begin()+i);
			i--;
		}
	}

	if(not err.empty())
	{
		std::string errorMessage("Unrecognized tokens while parsing:");
		for(auto& tok : err)
			errorMessage += " " + tok;
		throw ScriptError(errorMessage);
	}
	return second;
}

void Interpreter::discardSpaces(Interpreter::VecStr& tokens)
{
    tokens.erase(std::remove_if(tokens.begin(), tokens.end(),
		[](const std::string& token)
		{
			return std::all_of(token.begin(), token.end(), [](char c){return std::isspace(c);});
		}), tokens.end());
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
	//Number literal
	if(std::regex_match(token, number_literal_regex))
	{
		if(token.find(".") != std::string::npos)
			return Data(stof(token));
		else
			return Data(stoi(token));
	}
	//String literal
	else if(std::regex_match(token, string_literal_regex))
	{
		std::string res(token.begin()+1, token.end()-1);
		//Parse string and replace escaped characters
		for(size_t i{0}; i < res.size(); ++i)
		{
			if(res[i] == '\\')
			{
				const char escaped{res[i+1]};
				res.erase(i, 2);
				switch(escaped)
				{
					case 'a':
						res.insert(i, 1, '\a');
						break;
					case 'b':
						res.insert(i, 1, '\b');
						break;
					case 'f':
						res.insert(i, 1, '\f');
						break;
					case 'n':
						res.insert(i, 1, '\n');
						break;
					case 'r':
						res.insert(i, 1, '\r');
						break;
					case 't':
						res.insert(i, 1, '\t');
						break;
					case 'v':
						res.insert(i, 1, '\v');
						break;
					default:
						res.insert(i, 1, escaped);
						break;
				}
			}
		}
		return Data(res);
	}
	//Variable
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
		auto it(m_variables.find(identifier));
		if(it == m_variables.end())
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
		if(*from == "(")
			++depth;
		else if(*from == ")")
			--depth;
		if(depth == 0)
			break;
	}
	return from;
}

template <>
void cast<std::string>(Data& var)
{
	if(var.which() == 1)//Convert int to string
		var = std::to_string(boost::get<int>(var));
	else if(var.which() == 0)//Convert bool to string
		var = boost::get<bool>(var) ? "true" : "false";
	else if(var.which() == 2)//Convert float to string
		var = std::to_string(boost::get<float>(var));
}

