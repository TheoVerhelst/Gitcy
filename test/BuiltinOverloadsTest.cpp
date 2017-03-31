#include <iostream>
#include <boost/test/unit_test.hpp>
#include <Functions.hpp>
#include <Utils.hpp>

template <typename TestedOverload, typename ResultType>
void checkOverloadReturn(const std::vector<Data>& values, const ResultType& expectedValue)
{
	BOOST_TEST(static_cast<Data>(TestedOverload()(values)).get<ResultType>() == expectedValue);
}

BOOST_AUTO_TEST_SUITE(BuiltinOverloadsTest)

BOOST_AUTO_TEST_CASE(PrintOneString)
{
	const std::string testedString{"Coucou"};

	const Utils::OstreamListener coutListener{std::cout};
	BuiltinOverloads::Print()({testedString});
	BOOST_TEST(coutListener.getOutput() == testedString + "\n");
}

BOOST_AUTO_TEST_CASE(PrintTwoValues)
{
	const std::string testedString{"Coucou"};
	const int testedInt{4};
	const std::string expectedOutput{"Coucou 4\n"};

	const Utils::OstreamListener coutListener{std::cout};
	BuiltinOverloads::Print()({testedString, testedInt});
	BOOST_TEST(coutListener.getOutput() == expectedOutput);
}

BOOST_AUTO_TEST_CASE(DoReturnsLastValue)
{
	checkOverloadReturn<BuiltinOverloads::Do>({4, 3.3, false}, false);
}

BOOST_AUTO_TEST_CASE(AndTwoTruesOneFalses)
{
	checkOverloadReturn<BuiltinOverloads::And>({true, false, true}, false);
}

BOOST_AUTO_TEST_CASE(AndFourTrues)
{
	checkOverloadReturn<BuiltinOverloads::And>({true, true, true, true}, true);
}

BOOST_AUTO_TEST_CASE(OrTwoTruesOneFalses)
{
	checkOverloadReturn<BuiltinOverloads::Or>({true, false, true}, true);
}

BOOST_AUTO_TEST_CASE(OrFourFalses)
{
	checkOverloadReturn<BuiltinOverloads::And>({false, false, false, false}, false);
}

BOOST_AUTO_TEST_CASE(NotFalse)
{
	checkOverloadReturn<BuiltinOverloads::Not>({false}, true);
}

BOOST_AUTO_TEST_SUITE_END()
