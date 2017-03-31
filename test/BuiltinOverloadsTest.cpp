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
	const std::vector<Data> values{{4}, {3.3}, {std::string("bluh")}};
	BOOST_TEST(BuiltinOverloads::Do()(values).get<std::string>() == values[2].get<std::string>());
}

BOOST_AUTO_TEST_SUITE_END()
