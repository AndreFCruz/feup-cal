//
//  SubwayStop.cpp
//  CAL_Proj
//
//  Created by Andre Cruz on 14/05/2017.
//  Copyright © 2017 Andre Cruz. All rights reserved.
//

#include "SubwayStop.hpp"

SubwayStop::SubwayStop(TransportStop * stop, Node * closest_node) : stop(stop), closest_node(closest_node) {}

Node * SubwayStop::getClosestNode() const {
    return closest_node;
}

TransportStop * SubwayStop::getTransportStop() const {
    return stop;
}
