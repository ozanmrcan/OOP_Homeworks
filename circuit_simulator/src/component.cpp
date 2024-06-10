#include "component.h"

Component::Component(const std::string& id)
        :id{id}        
{ }

// stays empty, we wrote it because we need a virtual base destructor for derived classes 
Component::~Component() {} 