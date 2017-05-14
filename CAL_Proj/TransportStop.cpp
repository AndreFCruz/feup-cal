//
//  TransportStop.cpp
//  CAL_Proj
//
//  Created by Andre Cruz on 14/05/2017.
//  Copyright © 2017 Andre Cruz. All rights reserved.
//

#include "TransportStop.hpp"

TransportStop::TransportStop(Node * node, string name) : node(node), name(name) {}

string TransportStop::getName() const {
    return name;
}

Node * TransportStop::getNode() const {
    return node;
}
