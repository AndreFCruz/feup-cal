//
//  Road.hpp
//  CAL_GraphParser
//
//  Created by Andre Cruz on 01/04/2017.
//  Copyright © 2017 Andre Cruz. All rights reserved.
//

#ifndef Road_hpp
#define Road_hpp

#include <set>
#include "Edge.hpp"

typedef unsigned long road_id;

using namespace std;

class Edge;

class Road {
private:
    road_id id;
    string name;
    bool twoWay;
    
    set<Edge *> edges;
    
public:
    Road(road_id id, string name, bool twoWay);
    
    Road(istream & input);
    
    road_id getID() const;
    
    string getName() const;
    
    bool isTwoWay() const;
    
    bool addEdge(Edge * ptr);
    
    const set<Edge *> getEdges();
};


#endif /* Road_hpp */
