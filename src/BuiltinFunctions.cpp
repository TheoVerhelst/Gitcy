#include <iostream>
#include <string>
#include <BuiltinFunctionsOverloads.hpp>
#include <BuiltinFunctions.hpp>

BuiltinFunctions::BuiltinFunctions():
	#define OVERLOAD(className) std::make_shared<BuiltinFunctionsOverloads::className>()
	print{new Function({OVERLOAD(Print)})},
	do_{new Function({OVERLOAD(Do)})},
	lowerThan{new Function({OVERLOAD(LowerThan<int>), OVERLOAD(LowerThan<double>)})},
	greaterThan{new Function({OVERLOAD(GreaterThan<int>), OVERLOAD(GreaterThan<double>)})},
	lowerEqual{new Function({OVERLOAD(LowerEqual<int>), OVERLOAD(LowerEqual<double>)})},
	greaterEqual{new Function({OVERLOAD(GreaterEqual<int>), OVERLOAD(GreaterEqual<double>)})},
	equal{new Function({OVERLOAD(Equal<int>), OVERLOAD(Equal<double>), OVERLOAD(Equal<std::string>), OVERLOAD(Equal<bool>)})},
	notEqual{new Function({OVERLOAD(NotEqual<int>), OVERLOAD(NotEqual<double>), OVERLOAD(NotEqual<std::string>), OVERLOAD(NotEqual<bool>)})},
	and_{new Function({OVERLOAD(And)})},
	or_{new Function({OVERLOAD(Or)})},
	add{new Function({OVERLOAD(Add<int>), OVERLOAD(Add<double>), OVERLOAD(Add<std::string>)})},
	substract{new Function({OVERLOAD(Substract<int>), OVERLOAD(Substract<double>)})},
	multiply{new Function({OVERLOAD(Multiply<int>), OVERLOAD(Multiply<double>)})},
	divide{new Function({OVERLOAD(Divide<int>), OVERLOAD(Divide<double>)})},
	modulo{new Function({OVERLOAD(Modulo), OVERLOAD(DoubleModulo)})},
	not_{new Function({OVERLOAD(Not)})}
	#undef OVERLOAD
{
}
