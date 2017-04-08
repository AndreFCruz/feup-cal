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
    
    unordered_map<int, node_id> nodeIDs;
    
    void addEdge(Edge * ptr);
    
    void resetNodes();
    
    void loadTransportEdges(istream & input, Transport::Type type);
    
    bool nodesReset = true;
    
public:
    Graph(istream & nodes, istream & edges, istream & roads, istream & subway, istream & bus);
    
    ~Graph();
    
    node_id getNodeIDFromParserID(int parserID) const;
    
    unordered_map<node_id, Node *> getNodes() const;
    unordered_map<edge_id, Edge *> getEdges() const;
    unordered_map<road_id, Road *> getRoads() const;
    
//    unordered_map<Node *, float> dijkstraTree(node_id src_id) const;
//    unordered_map<Node *, float> dijkstraTree(Node * src) const;
//    
//    float dijkstra(node_id src_id, node_id dest_id) const;
//    float dijkstra(Node * src, Node * end_node) const;
//    
//    unordered_map<Node*, Edge*> dijkstraEdges(node_id src_id, node_id dest_id) const;
//    unordered_map<Node*, Edge*> dijkstraEdges(Node * src, Node * end_node) const;
    
    void dijkstraShortestPath(node_id src_id, node_id dest_id = 0);
    void dijkstraShortestPath(Node * src, Node * destination = nullptr);
    
    void dijkstraShortestPath(node_id src_id, node_id dest_id, Transport::Type type, unsigned int scale = 7);
    void dijkstraShortestPath(Node * src, Node * dest, Transport::Type type, unsigned int scale = 7);
    
    /**
     * Altered implementation of Dijkstra's shortest path algorithm,
     * takes into account a maximum cost, which must not be breached.
     *
     * @param src node_id of the start/source node
     * @param dest node_id of the end/destination node
     * @param maxCost Maximum cost, in cents, of the path
     */
    void dijkstraShortestPathWithMaxCost(node_id src, node_id dest, unsigned maxCost);
    
    /**
     * Altered implementation of Dijkstra's shortest path algorithm,
     * takes into account a maximum cost, which must not be breached.
     *
     * @param src Node* to start/source node
     * @param destination Node* to end/destination node
     * @param maxCost Maximum cost, in cents, of the path
     */
    void dijkstraShortestPathWithMaxCost(Node * src, Node * destination, unsigned maxCost);
    
    vector<Edge *> getEdgesFromPath(const vector<Node*> & path);
    vector<Node *> getPath(node_id src_id, node_id dest_id);
    
    vector<Edge *> getPathEdges(node_id src_id, node_id dest_id);
    
    //dijkstra, A-star
    //avaliar conectividade TODO
};


#endif /* Graph_h */
