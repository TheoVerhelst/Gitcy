#include <iostream>
#include <boost/test/unit_test.hpp>
#include <Functions.hpp>
#include <Utils.hpp>

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
	BOOST_TEST(BuiltinOverloads::Do()({4, 3.3, false}).get<bool>() == false);
}

BOOST_AUTO_TEST_CASE(AndTwoTruesOneFalses)
{
	BOOST_TEST(BuiltinOverloads::And()({true, false, true}).get<bool>() == false);
}

BOOST_AUTO_TEST_CASE(AndFourTrues)
{
	BOOST_TEST(BuiltinOverloads::And()({true, true, true, true}).get<bool>() == true);
}

BOOST_AUTO_TEST_CASE(OrTwoTruesOneFalses)
{
	BOOST_TEST(BuiltinOverloads::Or()({true, false, true}).get<bool>() == true);
}

BOOST_AUTO_TEST_CASE(OrFourFalses)
{
	BOOST_TEST(BuiltinOverloads::Or()({false, false, false, false}).get<bool>() == false);
}

BOOST_AUTO_TEST_CASE(NotFalse)
{
	BOOST_TEST(BuiltinOverloads::Not()({false}).get<bool>() == true);
}

BOOST_AUTO_TEST_CASE(LowerThanFourOrderedDoubles)
{
	BOOST_TEST(BuiltinOverloads::LowerThan<double>()({2.3, 2.5, 4.3, 333.1}).get<bool>() == true);
}

BOOST_AUTO_TEST_CASE(LowerThanFourUnorderedInt)
{
	BOOST_TEST(BuiltinOverloads::LowerThan<int>()({2, 1, 4, 333}).get<bool>() == false);
}

BOOST_AUTO_TEST_SUITE_END()
