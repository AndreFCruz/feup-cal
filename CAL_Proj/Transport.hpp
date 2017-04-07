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
    
private:
    Transport() = default;
    
    static Transport * singleton_instance;
        
    void initializeVelocities();
    
    unsigned int velocities[3] {    // in km/h
        6, 35, 55
    };
    
};

#endif /* Transport_hpp */
