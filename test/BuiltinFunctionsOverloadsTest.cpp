#include <iostream>
#include <boost/test/unit_test.hpp>
#include <BuiltinFunctionsOverloads.hpp>
#include <Utils.hpp>

BOOST_AUTO_TEST_SUITE(BuiltinFunctionsOverloadsTest)

BOOST_AUTO_TEST_CASE(PrintOneString)
{
	const std::string testedString{"Coucou"};

	const Utils::OstreamListener coutListener{std::cout};
	BuiltinFunctionsOverloads::Print().call({testedString});
	BOOST_TEST(coutListener.getOutput() == testedString + "\n");
}

BOOST_AUTO_TEST_CASE(PrintTwoValues)
{
	const std::string testedString{"Coucou"};
	const int testedInt{4};
	const std::string expectedOutput{"Coucou 4\n"};

	const Utils::OstreamListener coutListener{std::cout};
	BuiltinFunctionsOverloads::Print().call({testedString, testedInt});
	BOOST_TEST(coutListener.getOutput() == expectedOutput);
}

BOOST_AUTO_TEST_CASE(DoReturnsLastValue)
{
	BOOST_TEST(BuiltinFunctionsOverloads::Do().call({4, 3.3, false}).get<bool>() == false);
}

BOOST_AUTO_TEST_CASE(AndTwoTruesOneFalses)
{
	BOOST_TEST(BuiltinFunctionsOverloads::And().call({true, false, true}).get<bool>() == false);
}

BOOST_AUTO_TEST_CASE(AndFourTrues)
{
	BOOST_TEST(BuiltinFunctionsOverloads::And().call({true, true, true, true}).get<bool>() == true);
}

BOOST_AUTO_TEST_CASE(OrTwoTruesOneFalses)
{
	BOOST_TEST(BuiltinFunctionsOverloads::Or().call({true, false, true}).get<bool>() == true);
}

BOOST_AUTO_TEST_CASE(OrFourFalses)
{
	BOOST_TEST(BuiltinFunctionsOverloads::Or().call({false, false, false, false}).get<bool>() == false);
}

BOOST_AUTO_TEST_CASE(NotFalse)
{
	BOOST_TEST(BuiltinFunctionsOverloads::Not().call({false}).get<bool>() == true);
}

BOOST_AUTO_TEST_CASE(LowerThanFourOrderedDoubles)
{
	BOOST_TEST(BuiltinFunctionsOverloads::LowerThan<double>().call({2.3, 2.5, 4.3, 333.1}).get<bool>() == true);
}

BOOST_AUTO_TEST_CASE(LowerThanFourUnorderedInt)
{
	BOOST_TEST(BuiltinFunctionsOverloads::LowerThan<int>().call({2, 1, 4, 333}).get<bool>() == false);
}

BOOST_AUTO_TEST_CASE(GreaterThanFourOrderedDoubles)
{
	BOOST_TEST(BuiltinFunctionsOverloads::GreaterThan<double>().call({44.3, 1.0, -0.2, -11.2}).get<bool>() == true);
}

BOOST_AUTO_TEST_CASE(GreaterThanFourUnorderedInt)
{
	BOOST_TEST(BuiltinFunctionsOverloads::GreaterThan<int>().call({2, 1, 4, 333}).get<bool>() == false);
}

BOOST_AUTO_TEST_SUITE_END()
