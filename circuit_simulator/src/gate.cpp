#include "gate.h"
#include "pin.h"

Gate::Gate(const std::string& id, int numberOfInputs) 
    :Component{id} {
    // input pins
    for (int i = 0; i < numberOfInputs; i++) {
        inputs.push_back(new Pin("input_" + std::to_string(i))); // ids are not important probably but still...
    }
    // output pin
    output = new Pin("output"); 
}

Gate::~Gate() {
    // since vector has pointers to Pin objects, i have to deallocate Pins first, then clear the vector to get rid of everything
    int inputs_size = inputs.size(); // can't compare .size() to int (its long long unsigned int) 
    // (could also do for (Pin* i : inputs) )
    for (int i = 0; i < inputs_size; i++) {
        delete inputs[i];
    }
    inputs.clear();
    delete output;
}

Pin* Gate::getOutputPin()
{
    return output;
}

Pin* Gate::getInputPin(int i)
{
    return inputs[i]; // assuming input pins have 0-based indexing too i.e. input0, input1, ...
}
