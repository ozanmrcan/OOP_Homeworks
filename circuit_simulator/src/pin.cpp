#include "pin.h"

Pin::Pin(const std::string &id) 
    :Component{id}
{ }

void Pin::setSignal(bool val) {
    value = val;
}

bool Pin::getSignal() const {
    return value;
}

void Pin::evaluate() { }
