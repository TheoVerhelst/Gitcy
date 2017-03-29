#include <sstream>
#include <boost/test/unit_test.hpp>
#include <Null.hpp>

BOOST_AUTO_TEST_SUITE(NullTest)

BOOST_AUTO_TEST_CASE(outputTest)
{
	std::stringstream stream;
	stream << Null();
	BOOST_TEST(stream.str() == "null");
}

BOOST_AUTO_TEST_SUITE_END()
