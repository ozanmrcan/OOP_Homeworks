#include "or_gate.h"
#include "pin.h"

ORGate::ORGate(const std::string& id)
    :Gate{id, 2} 
{ }

void ORGate::evaluate() {
    output->setSignal(inputs[0]->getSignal() || inputs[1]->getSignal());
}