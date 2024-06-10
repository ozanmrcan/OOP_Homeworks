#include "and_gate.h"
#include "pin.h"

// gates in this assignment have fixed number of inputs, you can't increase it
ANDGate::ANDGate(const std::string& id) 
    :Gate{id, 2}
{ }

void ANDGate::evaluate() {
    output->setSignal(inputs[0]->getSignal() && inputs[1]->getSignal()); // output/inputs are protected, reachable
}