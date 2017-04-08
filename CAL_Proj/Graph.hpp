//
//  Graph.hpp
//  CAL_GraphParser
//
//  Created by Andre Cruz on 28/03/2017.
//  Copyright © 2017 Andre Cruz. All rights reserved.
//

#ifndef Graph_h
#define Graph_h

#include <set>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "Coordinates.hpp"
#include "Node.hpp"
#include "Edge.hpp"
#include "Road.hpp"

using namespace std;


class Graph {
private:
    unordered_map<node_id, Node *> nodes;
    unordered_map<edge_id, Edge *> edges;
    unordered_map<road_id, Road *> roads;
    
    void addEdge(Edge * ptr);
    
    void resetNodes();
    
    bool nodesReset = true;
    
public:
    Graph(istream & nodes, istream & edges, istream & roads, istream & subway);
    
    ~Graph();
    
    unordered_map<node_id, Node *> getNodes() const;
    unordered_map<edge_id, Edge *> getEdges() const;
    unordered_map<road_id, Road *> getRoads() const;
    
    unordered_map<Node *, float> dijkstraTree(node_id src_id) const;
    unordered_map<Node *, float> dijkstraTree(Node * src) const;
    
    float dijkstra(node_id src_id, node_id dest_id) const;
    float dijkstra(Node * src, Node * end_node) const;
    
    unordered_map<Node*, Edge*> dijkstraEdges(node_id src_id, node_id dest_id) const;
    unordered_map<Node*, Edge*> dijkstraEdges(Node * src, Node * end_node) const;
    
    void dijkstraShortestPath(node_id src_id, node_id dest_id = 0);
    void dijkstraShortestPath(Node * src, Node * destination = nullptr);
    
    vector<Node *> getPath(node_id src_id, node_id dest_id);
    
    void printShortestPath(node_id src_id, node_id dest_id) const;
    //dijkstra, A-star
    //avaliar conectividade TODO
};


#endif /* Graph_h */
