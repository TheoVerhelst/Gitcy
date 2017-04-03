#include <iostream>
#include <boost/test/unit_test.hpp>
#include <BuiltinFunctionsOverloads.hpp>
#include <Utils.hpp>

BOOST_AUTO_TEST_SUITE(BuiltinFunctionsOverloadsTest)

BOOST_AUTO_TEST_CASE(PrintOneString)
{
	const std::string testedString{"Coucou"};

	const Utils::OstreamListener coutListener{std::cout};
	BuiltinFunctionsOverloads::Print()({testedString});
	BOOST_TEST(coutListener.getOutput() == testedString + "\n");
}

BOOST_AUTO_TEST_CASE(PrintTwoValues)
{
	const std::string testedString{"Coucou"};
	const int testedInt{4};
	const std::string expectedOutput{"Coucou 4\n"};

	const Utils::OstreamListener coutListener{std::cout};
	BuiltinFunctionsOverloads::Print()({testedString, testedInt});
	BOOST_TEST(coutListener.getOutput() == expectedOutput);
}

BOOST_AUTO_TEST_CASE(DoReturnsLastValue)
{
	BOOST_TEST(BuiltinFunctionsOverloads::Do()({4, 3.3, false}).get<bool>() == false);
}

BOOST_AUTO_TEST_CASE(AndTwoTruesOneFalses)
{
	BOOST_TEST(BuiltinFunctionsOverloads::And()({true, false, true}).get<bool>() == false);
}

BOOST_AUTO_TEST_CASE(AndFourTrues)
{
	BOOST_TEST(BuiltinFunctionsOverloads::And()({true, true, true, true}).get<bool>() == true);
}

BOOST_AUTO_TEST_CASE(OrTwoTruesOneFalses)
{
	BOOST_TEST(BuiltinFunctionsOverloads::Or()({true, false, true}).get<bool>() == true);
}

BOOST_AUTO_TEST_CASE(OrFourFalses)
{
	BOOST_TEST(BuiltinFunctionsOverloads::Or()({false, false, false, false}).get<bool>() == false);
}

BOOST_AUTO_TEST_CASE(NotFalse)
{
	BOOST_TEST(BuiltinFunctionsOverloads::Not()({false}).get<bool>() == true);
}

BOOST_AUTO_TEST_CASE(LowerThanFourOrderedDoubles)
{
	BOOST_TEST(BuiltinFunctionsOverloads::LowerThan<double>()({2.3, 2.5, 4.3, 333.1}).get<bool>() == true);
}

BOOST_AUTO_TEST_CASE(LowerThanFourUnorderedInt)
{
	BOOST_TEST(BuiltinFunctionsOverloads::LowerThan<int>()({2, 1, 4, 333}).get<bool>() == false);
}

BOOST_AUTO_TEST_CASE(GreaterThanFourOrderedDoubles)
{
	BOOST_TEST(BuiltinFunctionsOverloads::GreaterThan<double>()({44.3, 1.0, -0.2, -11.2}).get<bool>() == true);
}

BOOST_AUTO_TEST_CASE(GreaterThanFourUnorderedInt)
{
	BOOST_TEST(BuiltinFunctionsOverloads::GreaterThan<int>()({2, 1, 4, 333}).get<bool>() == false);
}

BOOST_AUTO_TEST_SUITE_END()
