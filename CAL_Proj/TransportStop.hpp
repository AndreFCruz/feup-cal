//
//  TransportStop.hpp
//  CAL_Proj
//
//  Created by Andre Cruz on 14/05/2017.
//  Copyright © 2017 Andre Cruz. All rights reserved.
//

#ifndef TransportStop_hpp
#define TransportStop_hpp

#include "Node.hpp"

class TransportStop {
private:
    string name;
    Node * node;
    
public:
    TransportStop(Node * node, string name);
    
    string getName() const;
    
    Node * getNode() const;
};


#endif /* TransportStop_hpp */
