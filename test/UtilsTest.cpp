#include <sstream>
#include <iostream>
#include <boost/test/unit_test.hpp>
#include <Functions.hpp>
#include <Utils.hpp>

class UtilsTestFixture
{
	public:
		/// Constructor.
		UtilsTestFixture():
			threeStrings{std::string("one"), std::string("two"), std::string("three")},
			oneString{std::string("bluh")},
			empty{},
			threeInts{4, 2, 1},
			twoBool{true, false}
		{
		}

		std::vector<Data> threeStrings, oneString, empty, threeInts, twoBool;
};

BOOST_FIXTURE_TEST_SUITE(UtilsTest, UtilsTestFixture)

BOOST_AUTO_TEST_CASE(joinBasic)
{
	BOOST_TEST(Utils::join("|", threeStrings.begin(), threeStrings.end()) == "one|two|three");
}

BOOST_AUTO_TEST_CASE(joinOneElement)
{
	BOOST_TEST(Utils::join(",", oneString.begin(), oneString.end()) == "bluh");
}

BOOST_AUTO_TEST_CASE(joinNoElement)
{
	BOOST_TEST(Utils::join("#", empty.begin(), empty.end()) == "");
}

BOOST_AUTO_TEST_CASE(joinUsesStreamOperatorOnInt)
{
	BOOST_TEST(Utils::join(",", threeInts.begin(), threeInts.end()) == "4,2,1");
}

BOOST_AUTO_TEST_CASE(joinUsesStreamOperatorOnBool)
{
	BOOST_TEST(Utils::join("&", twoBool.begin(), twoBool.end()) == "true&false");
}

BOOST_AUTO_TEST_CASE(toStringBasic)
{
	BOOST_TEST(Utils::toString(true) == "true");
	BOOST_TEST(Utils::toString(324) == "324");
}

BOOST_AUTO_TEST_CASE(toStringComplexObject)
{
	const auto function(BuiltinFunctions().lowerEqual);
	std::stringstream stream;
	stream << function;
	BOOST_TEST(Utils::toString(function) == stream.str());
}

BOOST_AUTO_TEST_CASE(convertBasic)
{
	std::vector<std::string> expectedThreeStrings{"one", "two", "three"};
	std::vector<int> expectedThreeInts{4, 2, 1};
	BOOST_TEST(Utils::convert<std::string>(threeStrings) == expectedThreeStrings);
	BOOST_TEST(Utils::convert<int>(threeInts) == expectedThreeInts);
}

BOOST_AUTO_TEST_CASE(convertBadTypeThrows)
{
	BOOST_CHECK_THROW(Utils::convert<int>(twoBool), boost::bad_get);
}

BOOST_AUTO_TEST_CASE(ostreamListenerEmpty)
{
	Utils::OstreamListener listener{std::cout};
	BOOST_TEST(listener.getOutput() == "");
}

BOOST_AUTO_TEST_CASE(ostreamListenerGetOutputBasic)
{
	Utils::OstreamListener listener{std::cerr};
	std::cerr << "Xovxov " << 808 << " voxvoX";
	BOOST_TEST(listener.getOutput() == "Xovxov 808 voxvoX");
}

BOOST_AUTO_TEST_SUITE_END()

