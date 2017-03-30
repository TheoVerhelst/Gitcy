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

		virtual Data operator()(const std::vector<Data>&) const override
		{
			return std::string("blah");
		}
};

class VariadicDouble : public Overload
{
	public:
		VariadicDouble():
			Overload{{SignatureType::create<double>()}, true}
		{
		}

		virtual Data operator()(const std::vector<Data>&) const override
		{
			return std::string("blah");
		}
};

class TwoDouble : public Overload
{
	public:
		TwoDouble():
			Overload{{SignatureType::create<double>(), SignatureType::create<double>()}, false}
		{
		}

		virtual Data operator()(const std::vector<Data>&) const override
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
			function{{std::make_shared<OneInt>(), std::make_shared<VariadicDouble>(), std::make_shared<TwoDouble>()}}
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
	BOOST_CHECK_THROW(function({2.2}), ScriptError);
}

BOOST_AUTO_TEST_CASE(callOperatorNoOverloadFound)
{
	BOOST_CHECK_THROW(function({2, "bluh"}), ScriptError);
}

BOOST_AUTO_TEST_SUITE_END()
