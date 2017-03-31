#include <iostream>
#include <boost/test/unit_test.hpp>
#include <Functions.hpp>
#include <Utils.hpp>

BOOST_AUTO_TEST_SUITE(BuiltinOverloadsTest)

BOOST_AUTO_TEST_CASE(PrintOneString)
{
	const Utils::OstreamListener coutListener{std::cout};
	const std::string testedString{"Coucou"};
	BuiltinOverloads::Print()({testedString});
	BOOST_TEST(coutListener.getOutput() == testedString);
}

BOOST_AUTO_TEST_SUITE_END()
