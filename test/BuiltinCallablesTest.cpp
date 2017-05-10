#include <boost/test/unit_test.hpp>
#include <Parser.hpp>
#include <Scope.hpp>
#include <BuiltinFunctions.hpp>
#include <EvaluationTree.hpp>
#include <BuiltinCallables.hpp>

class BuiltinCallablesTestFixture
{
	public:
		Parser parser;
        Scope scope{{{"a", std::make_shared<Value>(32)},
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

BOOST_AUTO_TEST_SUITE_END()
