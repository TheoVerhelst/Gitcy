#include <typeindex>
#include <typeinfo>
#include <boost/test/unit_test.hpp>
#include <Value.hpp>

class ValueTestFixture
{
	public:
		/// Constructor.
		ValueTestFixture():
			value{2.4}
		{
		}

		Value value;
};

BOOST_FIXTURE_TEST_SUITE(ValueTest, ValueTestFixture)

BOOST_AUTO_TEST_CASE(getNormal)
{
	BOOST_TEST(value.get<double>() == 2.4);
}

BOOST_AUTO_TEST_CASE(getWrong)
{
	BOOST_CHECK_THROW(value.get<int>(), ValueBadGet);
}

BOOST_AUTO_TEST_CASE(holdsTypeNormal)
{
	BOOST_TEST(value.holdsType<double>());
}

BOOST_AUTO_TEST_CASE(holdsTypeWrong)
{
	BOOST_TEST(not value.holdsType<int>());
}

BOOST_AUTO_TEST_CASE(holdsTypeRuntimeNormal)
{
	BOOST_TEST(value.holdsType(std::type_index(typeid(double))));
}

BOOST_AUTO_TEST_CASE(holdsTypeRuntimeWrong)
{
	BOOST_TEST(not value.holdsType(std::type_index(typeid(int))));
}

BOOST_AUTO_TEST_CASE(getTypeName)
{
	BOOST_TEST(value.getTypeName() == "Real");
}

BOOST_AUTO_TEST_CASE(streamOperator)
{
	std::stringstream stream;
	stream << value;
	BOOST_TEST(stream.str() == "2.4");
}

BOOST_AUTO_TEST_SUITE_END()
