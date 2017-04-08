//
//  Node.hpp
//  CAL_GraphParser
//
//  Created by Andre Cruz on 01/04/2017.
//  Copyright © 2017 Andre Cruz. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <iostream>
#include <vector>
#include "Coordinates.hpp"
#include "Edge.hpp"
#include "Transport.hpp"

using namespace std;

typedef unsigned long node_id;

class Edge;

class Node {
private:
    static int count;
    
    static pair<float,float> latRange;
    static pair<float,float> lonRange;
    
    int parserID;
    node_id id;
    GeographicCoords coords;
    Point point;
    
    vector<Edge *> edges; // initially ordered by weight (?)
    
    void setStaticRange() const;
    
public:
    
    bool visited = false;
    bool processing = false;
    float dist = numeric_limits<float>::infinity();
    Node * path = nullptr;
    Edge * edgePath = nullptr;
    
    static pair<float,float> getLatRange();
    static pair<float,float> getLonRange();
    
    Node(istream & input);
    
    node_id getID() const;
    int getParserID() const;
    
    Edge * getEdge() const; // first order in vec - smallest weight
    Edge * getEdge(Transport::Type type) const;
    
    bool isVisited() const;
    void setVisited(bool state = true);
    
    void initiatePoint(pair<float,float> latRange, pair<float,float> lonRange);
    
    GeographicCoords getCoords() const;
    Point getPoint() const;
    
    void addEdge(Edge * ptr);
    bool removeEdge(Edge * ptr);
    void removeEdgesTo(node_id id);
    
    size_t getNumEdges() const;
    
    const vector<Edge*> & getEdges() const;
    
};


#endif /* Node_hpp */
