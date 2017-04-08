//
//  Transport.hpp
//  CAL_GraphParser
//
//  Created by Andre Cruz on 01/04/2017.
//  Copyright © 2017 Andre Cruz. All rights reserved.
//

#ifndef Transport_hpp
#define Transport_hpp

#include <unordered_map>

class Transport {
public:
    enum Type {
        FOOT,
        BUS,
        SUBWAY
    };
    
    static Transport * getInstance();
    
    unsigned int getVel(Type t) const;
    
    unsigned int getCost(Type t) const;
    
private:
    Transport() = default;
    
    static Transport * singleton_instance;
            
    unsigned int velocities[3] {    // in km/h
        6, 32, 45
    };
    
    // Costs per Transport, in Cents per Kilometer
    unsigned int costs[3] {
        0, 20, 30
    };
    
};

#endif /* Transport_hpp */
