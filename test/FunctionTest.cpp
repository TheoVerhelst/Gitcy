#include <boost/test/unit_test.hpp>
#include <ScriptError.hpp>
#include <Function.hpp>
#include <Overload.hpp>
#include <iostream>

class OneInt : public Overload
{
	public:
		OneInt():
			Overload{{SignatureType::create<int>()}, false}
		{
		}

		virtual Value operator()(const std::vector<Value>&) const override
		{
			return std::string("blah");
		}
};

class VariadicOneDouble : public Overload
{
	public:
		VariadicOneDouble():
			Overload{{SignatureType::create<double>()}, true}
		{
		}

		virtual Value operator()(const std::vector<Value>&) const override
		{
			return std::string("blah");
		}
};

class VariadicTwoDouble : public Overload
{
	public:
		VariadicTwoDouble():
			Overload{{SignatureType::create<double>(), SignatureType::create<double>()}, true}
		{
		}

		virtual Value operator()(const std::vector<Value>&) const override
		{
			return std::string("blah");
		}
};

class FunctionTestFixture
{
	public:
		/// Constructor.
		FunctionTestFixture():
			// A normal overload, and two possibly ambiguous overloads
			function{{std::make_shared<OneInt>(), std::make_shared<VariadicOneDouble>(), std::make_shared<VariadicTwoDouble>()}}
		{
		}

		Function function;
};

BOOST_FIXTURE_TEST_SUITE(FunctionTest, FunctionTestFixture)

BOOST_AUTO_TEST_CASE(callOperatorNormal)
{
	BOOST_TEST(function({3}).get<std::string>() == "blah");
}

BOOST_AUTO_TEST_CASE(callOperatorAmbiguous)
{
	BOOST_CHECK_THROW(function({2.2, 2.3}), ScriptError);
}

BOOST_AUTO_TEST_CASE(callOperatorNoOverloadFound)
{
	BOOST_CHECK_THROW(function({2, std::string("bluh")}), ScriptError);
}

BOOST_AUTO_TEST_SUITE_END()
