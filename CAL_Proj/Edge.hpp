//
//  Edge.hpp
//  CAL_GraphParser
//
//  Created by Andre Cruz on 01/04/2017.
//  Copyright © 2017 Andre Cruz. All rights reserved.
//

#ifndef Edge_hpp
#define Edge_hpp

#include <iostream>
#include "Node.hpp"
#include "Road.hpp"
#include "Transport.hpp"

using namespace std;

class Node;
class Road;

typedef unsigned int edge_id;

// TODO
// add different types of weight (cost, travel time, length)

// TODO ?
// remove type, graph calculates weight instead of potentially tripling edges (?)
// files with edges of bus, edges of tram, etc. (subway can travel off-road)

// Edges têm custo associado? tipo tarifas de determinado transporte ?
// SubClasses de Edges em vez de tipos?
class Edge {
private:
    static edge_id edge_count;

    edge_id edgeID;

    Node * origin = nullptr;
    Node * dest = nullptr;
    
    Road * road = nullptr;
    
    float length;
    
    Transport::Type type;
    
public:
    Edge(Node * origin, Node * dest, Road * road, Transport::Type type = Transport::FOOT);
    
    edge_id getID() const;

    Node * getDest() const;
    Node * getOrigin() const;
    Road * getRoad() const;
    
    /**
     * Getter for Edge's length.
     * Corresponds to the physical distance between the two Nodes linked by this edge.
     */
    float getLength() const;
    
    /**
     * Getter for Edge's weight.
     * Corresponds to the average time (in seconds - SI unit) needed to traverse this Edge.
     */
    float getWeight() const;
    
    Transport::Type getType() const;
    
    friend ostream& operator<<(ostream & out, const Edge & e);
};

#endif /* Edge_hpp */
