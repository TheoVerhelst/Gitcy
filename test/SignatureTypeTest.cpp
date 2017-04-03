#include <boost/test/unit_test.hpp>
#include <SignatureType.hpp>
#include <Utils.hpp>

class SignatureTypeTestFixture
{
	public:
		/// Constructor.
		SignatureTypeTestFixture():
			anyType{SignatureType::create()},
			boolType{SignatureType::create<bool>()},
			doubleType{SignatureType::create<double>()}
		{
		}

		SignatureType anyType, boolType, doubleType;
};

BOOST_FIXTURE_TEST_SUITE(SignatureTypeTest, SignatureTypeTestFixture)

BOOST_AUTO_TEST_CASE(anyMatchesAny)
{
	BOOST_TEST(anyType.matches(Data(true)));
	BOOST_TEST(anyType.matches(Data(std::string("bluh"))));
	BOOST_TEST(anyType.matches(Data(2.1)));
}

BOOST_AUTO_TEST_CASE(boolMatchesBool)
{
	BOOST_TEST(boolType.matches(Data(true)));
	BOOST_TEST(not boolType.matches(Data(std::string("bluh"))));
}

BOOST_AUTO_TEST_CASE(doubleMatchesDouble)
{
	BOOST_TEST(doubleType.matches(Data(581208941239.3231)));
	BOOST_TEST(not doubleType.matches(Data(std::string("bluh"))));
}

BOOST_AUTO_TEST_CASE(streamOperator)
{
	BOOST_TEST(Utils::toString(boolType) == "Boolean");
	BOOST_TEST(Utils::toString(doubleType) == "Real");
	BOOST_TEST(Utils::toString(anyType) == "<any type>");
}

BOOST_AUTO_TEST_SUITE_END()
