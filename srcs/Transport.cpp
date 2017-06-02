//
//  Transport.cpp
//
//  Created by Andre Cruz on 01/04/2017.
//

#include "Transport.hpp"

using namespace std;

Transport * Transport::singleton_instance = nullptr;

Transport * Transport::getInstance() {
    if (singleton_instance == nullptr)
        singleton_instance = new Transport();
    
    return singleton_instance;
}

unsigned int Transport::getVel(Transport::Type t) const {
    return velocities[t];
}

unsigned int Transport::getCost(Type t) const {
    return costs[t];
}
