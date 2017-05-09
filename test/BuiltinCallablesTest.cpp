#include <boost/test/unit_test.hpp>
#include <Parser.hpp>
#include <Scope.hpp>
#include <EvaluationTree.hpp>
#include <BuiltinCallables.hpp>

class BuiltinCallablesTestFixture
{
	public:
		Parser parser;
        Scope scope{{}};
};

BOOST_FIXTURE_TEST_SUITE(BuiltinCallablesEvaluateTest, BuiltinCallablesTestFixture)

BOOST_AUTO_TEST_CASE(evaluateTokenYeldsThree)
{
    BOOST_TEST(BuiltinCallables::evaluate(parser.constructTree("3"), scope).get<int>() == 3);
}

BOOST_AUTO_TEST_SUITE_END()
