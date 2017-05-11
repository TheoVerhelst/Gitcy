#include <boost/test/unit_test.hpp>
#include <Parser.hpp>
#include <Scope.hpp>
#include <BuiltinFunctions.hpp>
#include <EvaluationTree.hpp>
#include <Null.hpp>
#include <BuiltinCallables.hpp>

class BuiltinCallablesTestFixture
{
	public:
		Parser parser;
        Scope scope{{{"a", std::make_shared<Value>(32)},
				{"true", std::make_shared<Value>(true)},
				{"false", std::make_shared<Value>(false)},
                {"+", std::make_shared<Value>(BuiltinFunctions::add)}}};
};

BOOST_FIXTURE_TEST_SUITE(BuiltinCallablesEvaluateTest, BuiltinCallablesTestFixture)

BOOST_AUTO_TEST_CASE(evaluateTokenYeldsThree)
{
    BOOST_TEST(BuiltinCallables::evaluate(parser.constructTree("3"), scope).get<int>() == 3);
}

BOOST_AUTO_TEST_CASE(evaluateIdentifierYeldsA)
{
    BOOST_TEST(BuiltinCallables::evaluate(parser.constructTree("a"), scope).get<int>() == 32);
}

BOOST_AUTO_TEST_CASE(evaluateNestedCallsYeldsResult)
{
    BOOST_TEST(BuiltinCallables::evaluate(parser.constructTree("(+ (+ (+ 3 1 2) 12) 2 22 7)"), scope).get<int>() == 49);
}

BOOST_AUTO_TEST_CASE(evaluateEmptyCallThrows)
{
    BOOST_REQUIRE_THROW(BuiltinCallables::evaluate(parser.constructTree("()"), scope), ScriptError);
}

BOOST_AUTO_TEST_CASE(evaluateCallNonCallableThrows)
{
    BOOST_REQUIRE_THROW(BuiltinCallables::evaluate(parser.constructTree("(3 2 1)"), scope), ScriptError);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(BuiltinCallablesDefineTest, BuiltinCallablesTestFixture)

BOOST_AUTO_TEST_CASE(defineAddsToScope)
{
	BuiltinCallables::define(parser.constructTree("(define a 3)"), scope);
	BOOST_TEST(scope.getVariable("a").get<int>() == 3);
}

BOOST_AUTO_TEST_CASE(defineWithoutIdentifierThrows)
{
	BOOST_REQUIRE_THROW(BuiltinCallables::define(parser.constructTree("(define 2 3)"), scope), ScriptError);
}

BOOST_AUTO_TEST_CASE(defineWithoutArgumentsThrows)
{
	BOOST_REQUIRE_THROW(BuiltinCallables::define(parser.constructTree("(define)"), scope), ScriptError);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(BuiltinCallablesIfTest, BuiltinCallablesTestFixture)

BOOST_AUTO_TEST_CASE(ifTrueExecutesFirstBody)
{
	BOOST_TEST(BuiltinCallables::if_(parser.constructTree("(if true \"abc\")"), scope).get<std::string>() == "abc");
}

BOOST_AUTO_TEST_CASE(ifFalseReturnsNull)
{
	BOOST_TEST(BuiltinCallables::if_(parser.constructTree("(if false \"abc\")"), scope).holdsType<Null>());
}

BOOST_AUTO_TEST_CASE(ifFalseReturnsSecondBody)
{
	BOOST_TEST(BuiltinCallables::if_(parser.constructTree("(if false \"abc\" \"def\")"), scope).get<std::string>() == "def");
}

BOOST_AUTO_TEST_CASE(defineWithoutIdentifierThrows)
{
	BOOST_REQUIRE_THROW(BuiltinCallables::define(parser.constructTree("(define 2 3)"), scope), ScriptError);
}

BOOST_AUTO_TEST_CASE(defineWithoutArgumentsThrows)
{
	BOOST_REQUIRE_THROW(BuiltinCallables::define(parser.constructTree("(define)"), scope), ScriptError);
}

BOOST_AUTO_TEST_SUITE_END()
