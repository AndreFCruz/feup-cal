//
//  SubwayStop.hpp
//  CAL_Proj
//
//  Created by Andre Cruz on 14/05/2017.
//  Copyright © 2017 Andre Cruz. All rights reserved.
//

#ifndef SubwayStop_hpp
#define SubwayStop_hpp

#include "Node.hpp"
#include "TransportStop.hpp"

class SubwayStop {
private:
    Node * closest_node;
    TransportStop * stop;
    
public:
    SubwayStop(TransportStop * stop, Node * closest_node);
    
    Node * getClosestNode() const;
    
    TransportStop * getTransportStop() const;
};

#endif /* SubwayStop_hpp */
