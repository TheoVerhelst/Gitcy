#include <boost/test/unit_test.hpp>
#include <ScriptError.hpp>
#include <Function.hpp>
#include <Overload.hpp>
#include <EvaluationTree.hpp>
#include <Scope.hpp>
#include <Parser.hpp>

class OneInt : public Overload
{
	public:
		OneInt():
			Overload{{SignatureType::create<int>()}, false}
		{
		}

		virtual Value call(const std::vector<Value>&) const override
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

		virtual Value call(const std::vector<Value>&) const override
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

		virtual Value call(const std::vector<Value>&) const override
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
			function{{std::make_shared<OneInt>(), std::make_shared<VariadicOneDouble>(), std::make_shared<VariadicTwoDouble>()}},
			scope{{}}
		{
		}

		Function function;
		Scope scope;
		Parser parser;
};

BOOST_FIXTURE_TEST_SUITE(FunctionTest, FunctionTestFixture)

BOOST_AUTO_TEST_CASE(callReturnsBlah)
{
	BOOST_TEST(function(parser.constructTree("(function 3)"), scope).get<std::string>() == "blah");
}

BOOST_AUTO_TEST_CASE(ambiguousOverloadCallThrows)
{
	BOOST_CHECK_THROW(function(parser.constructTree("(function 2.2 2.3)"), scope), ScriptError);
}

BOOST_AUTO_TEST_CASE(nonExistingOverloadCallThrows)
{
	BOOST_CHECK_THROW(function(parser.constructTree("(function 2 \"bluh\")"), scope), ScriptError);
}

BOOST_AUTO_TEST_SUITE_END()
