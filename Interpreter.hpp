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
		static const std::string identifier;
		static const std::string number_literal;
		static const std::string string_literal;
		static const std::string open_parenthesis_literal;
		static const std::string close_parenthesis_literal;
		static const std::string parenthesis_literal;

		static const std::regex identifier_regex;
		static const std::regex number_literal_regex;
		static const std::regex string_literal_regex;
		static const std::regex token_regex;
		static const std::regex value_regex;
		static const std::regex space_regex;

		// Methods
		void loadScript();
		static VecStr tokenize(std::string code);
		static void discardSpaces(VecStr& tokens);
		static Tree<EvaluationNode>::Ptr constructTree(const VecStr& tokens);
		/// Returns an iterator to the last token of the expression
		/// and the evaluation tree representing the expression
		static std::pair<VecStr::const_iterator, Tree<EvaluationNode>::Ptr> parseExpression(VecStr::const_iterator from, VecStr::const_iterator to);
		static EvaluationNode parseToken(const std::string& token);
		Data evaluateTree(const Tree<EvaluationNode>::Ptr& expression);
		static VecStr::const_iterator findClosingParenthesis(VecStr::const_iterator from, VecStr::const_iterator to);
};

template <typename T>
void cast(Data& var);

template <>
void cast<std::string>(Data& var);

template <typename T>
void cast(Data& var)
{
	if(var.which() == 1)//var is a bool
		var = static_cast<T>(boost::get<bool>(var));
	else if(var.which() == 2)//var is an int
		var = static_cast<T>(boost::get<int>(var));
	else if(var.which() == 3)//var is a float
		var = static_cast<T>(boost::get<float>(var));
	else if(typeid(T) == typeid(bool))//var is a string, convert it to bool
		var = boost::get<std::string>(var).size() > 0;
	else if(typeid(T) == typeid(float))//var is a string, convert it to float
		var = std::stof(boost::get<std::string>(var));
	else//var is a string, convert it to int
		var = std::stoi(boost::get<std::string>(var));
}

#endif
