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
    
    bool isConnected();
    
    /**
     * Altered implementation of Dijkstra's shortest path algorithm,
     * takes into account a seeked cost.
     *
     * @param src Node* to start/source node
     * @param destination Node* to end/destination node
     * @param seekedCost Path's seekedCost, may be above/under the actual cost.
     */
    void dijkstraShortestPathWithCost(Node * src, Node * destination, unsigned seekedCost);
    
public:
    Graph(istream & nodes, istream & edges, istream & roads, istream & subway, istream & bus);
    
    ~Graph();
    
    node_id getNodeIDFromParserID(int parserID) const;
    
    unordered_map<node_id, Node *> getNodes() const;
    unordered_map<edge_id, Edge *> getEdges() const;
    unordered_map<road_id, Road *> getRoads() const;
    
    void dijkstraShortestPath(node_id src_id, node_id dest_id = 0);
    void dijkstraShortestPath(Node * src, Node * destination = nullptr);
    
    void dijkstraShortestPath(node_id src_id, node_id dest_id, Transport::Type type, unsigned int scale = 5);
    void dijkstraShortestPath(Node * src, Node * dest, Transport::Type type, unsigned int scale = 5);
    
    void dijkstraShortestPathWithMaxCost(node_id src_id, node_id dest_id, unsigned maxCost);
    
    vector<Node *> getPath(node_id src_id, node_id dest_id) const;
    
    vector<Edge *> getPathEdges(node_id src_id, node_id dest_id) const;
    
    /**
     * Calculates path length, in kilometers.
     *
     * @param src_id node_id of the start/source node.
     * @param dest_id node_id of the end/destination node.
     *
     * @return The path's length, in km.
     */
    float getPathLength(node_id src_id, node_id dest_id) const;
    
    /**
     * Calculates path duration, in hours.
     *
     * @param src_id node_id of the start/source node.
     * @param dest_id node_id of the end/destination node.
     *
     * @return The path's duration, in hours.
     */
    float getPathDuration(node_id src_id, node_id dest_id) const;
    
    /**
     * Calculates path cost, in cents.
     *
     * @param src_id node_id of the start/source node.
     * @param dest_id node_id of the end/destination node.
     *
     * @return The path's cost, in cents.
     */
    unsigned getPathCost(node_id src_id, node_id dest_id) const;
    
    vector<Node*> dfs();
    
    void dfs(Node * v, vector<Node*> & res) const;
    
};


#endif /* Graph_h */
