#include <iostream>
#include <string>
#include <BuiltinFunctionsOverloads.hpp>
#include <BuiltinFunctions.hpp>

BuiltinFunctions::BuiltinFunctions():
	#define OVERLOAD(className) std::make_shared<BuiltinFunctionsOverloads::className>()
	print{{OVERLOAD(Print)}},
	do_{{OVERLOAD(Do)}},
	define{{OVERLOAD(Define)}},
	lowerThan{{OVERLOAD(LowerThan<int>), OVERLOAD(LowerThan<double>)}},
	greaterThan{{OVERLOAD(GreaterThan<int>), OVERLOAD(GreaterThan<double>)}},
	lowerEqual{{OVERLOAD(LowerEqual<int>), OVERLOAD(LowerEqual<double>)}},
	greaterEqual{{OVERLOAD(GreaterEqual<int>), OVERLOAD(GreaterEqual<double>)}},
	equal{{OVERLOAD(Equal<int>), OVERLOAD(Equal<double>), OVERLOAD(Equal<std::string>), OVERLOAD(Equal<bool>)}},
	notEqual{{OVERLOAD(NotEqual<int>), OVERLOAD(NotEqual<double>), OVERLOAD(NotEqual<std::string>), OVERLOAD(NotEqual<bool>)}},
	and_{{OVERLOAD(And)}},
	or_{{OVERLOAD(Or)}},
	add{{OVERLOAD(Add<int>), OVERLOAD(Add<double>), OVERLOAD(Add<std::string>)}},
	substract{{OVERLOAD(Substract<int>), OVERLOAD(Substract<double>)}},
	multiply{{OVERLOAD(Multiply<int>), OVERLOAD(Multiply<double>)}},
	divide{{OVERLOAD(Divide<int>), OVERLOAD(Divide<double>)}},
	modulo{{OVERLOAD(Modulo), OVERLOAD(DoubleModulo)}},
	not_{{OVERLOAD(Not)}}
	#undef OVERLOAD
{
}
