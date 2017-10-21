#include "../include/number.h"
#include "../include/atom.h"
#include "../include/variable.h"
#include <typeinfo>

Number::Number(double value)
{
    std::stringstream ss;
    ss << value;
    this->_value = this->_symbol = ss.str();
    this->_type = "Number";
}
