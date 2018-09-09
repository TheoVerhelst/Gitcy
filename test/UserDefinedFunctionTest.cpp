#include <boost/test/unit_test.hpp>
#include <Scope.hpp>
#include <Parser.hpp>
#include <EvaluationTree.hpp>
#include <BuiltinCallables.hpp>
#include <BuiltinFunctions.hpp>
#include <Function.hpp>
#include <UserDefinedFunction.hpp>

class UserDefinedFunctionTestFixture
{
	public:
		Parser parser;
        Scope scope{{
				{"function", std::make_shared<Value>(BuiltinCallables::defineFunction)},
				{"+", std::make_shared<Value>(BuiltinFunctions::add)}}};
		EvaluationTree node{parser.constructTree("(function f a b (+ a b))")};
};

BOOST_FIXTURE_TEST_SUITE(UserDefinedFunctionTest, UserDefinedFunctionTestFixture)

BOOST_AUTO_TEST_CASE(FunctionDefinitionReturnsCallable)
{
	Value value(BuiltinCallables::evaluate(node, scope));
	BOOST_TEST(value.holdsType<Function>());
}

BOOST_AUTO_TEST_CASE(FunctionDefinitionAddsToScope)
{
	BuiltinCallables::evaluate(node, scope);
	BOOST_REQUIRE_NO_THROW(scope.getVariable("f"));
	BOOST_TEST(scope.getVariable("f").holdsType<Function>());
}

BOOST_AUTO_TEST_CASE(UserDefinedFunctionReturnsCorrectValue)
{
	const EvaluationTree argumentsTree{parser.constructTree("(f 4 3)")};
	BOOST_TEST(BuiltinCallables::evaluate(node, scope).get<Function>()(argumentsTree, scope).get<int>() == 7);
}

BOOST_AUTO_TEST_SUITE_END()
