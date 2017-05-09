#include <BuiltinFunctionsOverloads.hpp>
#include <BuiltinFunctions.hpp>

BuiltinFunctions::BuiltinFunctions():
	#define OVERLOAD(className) std::make_shared<BuiltinFunctionsOverloads::className>()
	print{Function({OVERLOAD(Print)})},
	do_{Function({OVERLOAD(Do)})},
	lowerThan{Function({OVERLOAD(LowerThan<int>), OVERLOAD(LowerThan<double>)})},
	greaterThan{Function({OVERLOAD(GreaterThan<int>), OVERLOAD(GreaterThan<double>)})},
	lowerEqual{Function({OVERLOAD(LowerEqual<int>), OVERLOAD(LowerEqual<double>)})},
	greaterEqual{Function({OVERLOAD(GreaterEqual<int>), OVERLOAD(GreaterEqual<double>)})},
	equal{Function({OVERLOAD(Equal<int>), OVERLOAD(Equal<double>), OVERLOAD(Equal<std::string>), OVERLOAD(Equal<bool>)})},
	notEqual{Function({OVERLOAD(NotEqual<int>), OVERLOAD(NotEqual<double>), OVERLOAD(NotEqual<std::string>), OVERLOAD(NotEqual<bool>)})},
	and_{Function({OVERLOAD(And)})},
	or_{Function({OVERLOAD(Or)})},
	add{Function({OVERLOAD(Add<int>), OVERLOAD(Add<double>), OVERLOAD(Add<std::string>)})},
	substract{Function({OVERLOAD(Substract<int>), OVERLOAD(Substract<double>)})},
	multiply{Function({OVERLOAD(Multiply<int>), OVERLOAD(Multiply<double>)})},
	divide{Function({OVERLOAD(Divide<int>), OVERLOAD(Divide<double>)})},
	modulo{Function({OVERLOAD(Modulo), OVERLOAD(DoubleModulo)})},
	not_{Function({OVERLOAD(Not)})}
	#undef OVERLOAD
{
}
