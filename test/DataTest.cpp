#include <typeindex>
#include <typeinfo>
#include <boost/test/unit_test.hpp>
#include <Value.hpp>

class DataTestFixture
{
	public:
		/// Constructor.
		DataTestFixture():
			data{2.4}
		{
		}

		Value data;
};

BOOST_FIXTURE_TEST_SUITE(DataTest, DataTestFixture)

BOOST_AUTO_TEST_CASE(getNormal)
{
	BOOST_TEST(data.get<double>() == 2.4);
}

BOOST_AUTO_TEST_CASE(getWrong)
{
	BOOST_CHECK_THROW(data.get<int>(), boost::bad_get);
}

BOOST_AUTO_TEST_CASE(holdsTypeNormal)
{
	BOOST_TEST(data.holdsType<double>());
}

BOOST_AUTO_TEST_CASE(holdsTypeWrong)
{
	BOOST_TEST(not data.holdsType<int>());
}

BOOST_AUTO_TEST_CASE(holdsTypeRuntimeNormal)
{
	BOOST_TEST(data.holdsType(std::type_index(typeid(double))));
}

BOOST_AUTO_TEST_CASE(holdsTypeRuntimeWrong)
{
	BOOST_TEST(not data.holdsType(std::type_index(typeid(int))));
}

BOOST_AUTO_TEST_CASE(canHoldTypeNormal)
{
	// TODO move this in another test
	BOOST_TEST(ValueTypes::isSupportedType<int>());
}

BOOST_AUTO_TEST_CASE(canHoldTypeWrong)
{
	BOOST_TEST(not ValueTypes::isSupportedType<float>());
}

BOOST_AUTO_TEST_CASE(getTypeName)
{
	BOOST_TEST(data.getTypeName() == "Real");
}

BOOST_AUTO_TEST_CASE(getTypeNameStaticNormal)
{
	BOOST_TEST(ValueTypes::getTypeName(std::type_index(typeid(std::string))) == "String");
}

BOOST_AUTO_TEST_CASE(getTypeNameStaticWrong)
{
	BOOST_CHECK_THROW(Value::getTypeName(std::type_index(typeid(float))), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(streamOperator)
{
	std::stringstream stream;
	stream << data;
	BOOST_TEST(stream.str() == "2.4");
}

BOOST_AUTO_TEST_SUITE_END()
