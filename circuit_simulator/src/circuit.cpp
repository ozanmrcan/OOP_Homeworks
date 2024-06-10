#include "circuit.h"
#include <iostream>

Circuit::~Circuit() {
    // delete components
    int components_size = components.size(); // vector.size() returns long long unsigned int, cant compare it to a normal int
    for (int i = 0; i < components_size; i++) {
        delete components[i];
    }
    components.clear();
    // delete wires
    int wires_size = wires.size();
    for (int i = 0; i < wires_size; i++) {
        delete wires[i];
    }
    wires.clear();
}

void Circuit::addComponent(Component *comp)
{
    components.push_back(comp);
}

void Circuit::addWire(Wire* wire) {
    wires.push_back(wire);
}

void Circuit::simulate() {
    // Hint/Attention: Think simple and before each component evaluation iterate over all wires and propagate signal
    for (Component* c : components) {
        for (Wire* w : wires) {
            w->propagateSignal();
        }
        c->evaluate();
    }
}
