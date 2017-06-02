//
//  TransportStop.cpp
//
//  Created by Andre Cruz on 14/05/2017.
//

#include "TransportStop.hpp"

TransportStop::TransportStop(Node * node, string name) : node(node), name(name) {}

string TransportStop::getName() const {
    return name;
}

Node * TransportStop::getNode() const {
    return node;
}
