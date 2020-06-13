#include "operator.h"

Operator::Operator(int _oper_type): oper_type(_oper_type) {}

Keyboard_oper::Keyboard_oper(): Operator(INTERACTIVE_OPER), filter_type(filter_none) {}