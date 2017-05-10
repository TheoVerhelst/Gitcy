#include <BuiltinFunctionsOverloads.hpp>
#include <BuiltinFunctions.hpp>

#define OVERLOAD(name) std::make_shared<BuiltinFunctionsOverloads::name>()
const Callable BuiltinFunctions::print{Function({OVERLOAD(Print)})};
const Callable BuiltinFunctions::do_{Function({OVERLOAD(Do)})};
const Callable BuiltinFunctions::lowerThan{Function({OVERLOAD(LowerThan<int>), OVERLOAD(LowerThan<double>)})};
const Callable BuiltinFunctions::greaterThan{Function({OVERLOAD(GreaterThan<int>), OVERLOAD(GreaterThan<double>)})};
const Callable BuiltinFunctions::lowerEqual{Function({OVERLOAD(LowerEqual<int>), OVERLOAD(LowerEqual<double>)})};
const Callable BuiltinFunctions::greaterEqual{Function({OVERLOAD(GreaterEqual<int>), OVERLOAD(GreaterEqual<double>)})};
const Callable BuiltinFunctions::equal{Function({OVERLOAD(Equal<int>), OVERLOAD(Equal<double>), OVERLOAD(Equal<std::string>), OVERLOAD(Equal<bool>)})};
const Callable BuiltinFunctions::notEqual{Function({OVERLOAD(NotEqual<int>), OVERLOAD(NotEqual<double>), OVERLOAD(NotEqual<std::string>), OVERLOAD(NotEqual<bool>)})};
const Callable BuiltinFunctions::and_{Function({OVERLOAD(And)})};
const Callable BuiltinFunctions::or_{Function({OVERLOAD(Or)})};
const Callable BuiltinFunctions::add{Function({OVERLOAD(Add<int>), OVERLOAD(Add<double>), OVERLOAD(Add<std::string>)})};
const Callable BuiltinFunctions::substract{Function({OVERLOAD(Substract<int>), OVERLOAD(Substract<double>)})};
const Callable BuiltinFunctions::multiply{Function({OVERLOAD(Multiply<int>), OVERLOAD(Multiply<double>)})};
const Callable BuiltinFunctions::divide{Function({OVERLOAD(Divide<int>), OVERLOAD(Divide<double>)})};
const Callable BuiltinFunctions::modulo{Function({OVERLOAD(Modulo), OVERLOAD(DoubleModulo)})};
const Callable BuiltinFunctions::not_{Function({OVERLOAD(Not)})};
#undef OVERLOAD
