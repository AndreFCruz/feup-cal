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

/**
 * Class used to represent a Graph.
 * Every Graph has a set Nodes as well as a set of Edges, linking the Nodes.
 * The Graphs are also associated to Rodes.
 */
class Graph {
private:
    
    unordered_map<node_id, Node *> nodes;	/**< unordered_map<node_id, Node *> nodes. Hash map containing all the Graph's Nodes. */
    unordered_map<edge_id, Edge *> edges;	/**< unordered_map<edge_id, Edge *> edges. Hash map containing all the Graph's Edges. */
    unordered_map<road_id, Road *> roads;	/**< unordered_map<road_id, Road *> roads. Hash map containing all the Graph's Roads. */
    
    unordered_map<int, node_id> nodeIDs;	/**< unordered_map<int, node_id> nodeIDs. Hash map containing all the Graph's node IDs. */
    
    /**
     * Function that adds an Edge to the Hash map containing all Edges.
     *
     * @param ptr Edge to be added.
     */
    void addEdge(Edge * ptr);
    
    /**
     * Function that clears all the data generated in the Graph Nodes when running the Dijkstra algorithm.
     * This function should be called before running the Dijkstra algorithm.
     */
    void resetNodes();
    
    /**
     * Function that updates the Graph's Edges with the given mean of transport.
     *
     * @param input. Input stream containing the Edge's whose mean of transport is the one given.
     * @param type. Mean of transport that is going to be assigned to the Edges.
     */
    void loadTransportEdges(istream & input, Transport::Type type);
    
    bool nodesReset = true;	/**< bool nodeReset. Flag: If true, Graph Nodes have been reset, otherwise have not. */
    
    /**
     * Function that evaluates the Graph's connectivity.
     *
     * @return True if the Graph is connected, false otherwise.
     */
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

    /**
     * Graph's constructor.
     * Creates a Graph with the data passed by the arguments input streams.
     *
     * @param nodes The input stream to read from in order to populate the Nodes' Hash map.
     * @param edges The input stream to read from in order to populate the Edges' Hash map.
     * @param roads The input stream to read from in order to populate the Roads' Hash map.
     * @param subway The input stream containing the Edges whose mean of transport is the Subway.
     * @param bus The input stream containing the Edges whose mean of transport is the Bus.
     */
    Graph(istream & nodes, istream & edges, istream & roads, istream & subway, istream & bus);
    
    /**
     * Graph's Copy constructor.
     * Creates a new Graph with the same attributes as the given Graph.
     *
     * @param obj The Graph that will be copied.
     */
    Graph(const Graph & obj);
    
    /**
     * Graph's Destructor.
     * Deallocates all the memory used by a Graph.
     */
    ~Graph();
    
    /**
     * Parser function that parses a parserID into its correspondent nodeID.
     *
     * @param parserID parserID that will be parsed.
     *
     * @return Correspondent nodeID to the given parserID.
     */
    node_id getNodeIDFromParserID(int parserID) const;
    
    /**
     * Getter for the Graph's Nodes.
     *
     * @return Hash map containing all the Graph's Nodes.
     */
    unordered_map<node_id, Node *> getNodes() const;

    /**
     * Getter for the Graph's Edges.
     *
     * @return Hash map containing all the Graph's Edges.
     */
    unordered_map<edge_id, Edge *> getEdges() const;

    /**
     * Getter for the Graph's Roads.
     *
     * @return Hash map containing all the Graph's Roads.
     */
    unordered_map<road_id, Road *> getRoads() const;
    
    /**
     * Implementation of Dijkstra's shortest path algorithm.
     * The shortest path will be the fastest one.
     *
     * @param src_id The id of the origin Node.
     * @param dest_id The id of the destiny Node. If no value is given, it defaults to 0.
     */
    void dijkstraShortestPath(node_id src_id, node_id dest_id = 0);

    /**
     * Implementation of Dijkstra's shortest path algorithm.
     * The shortest path will be the fastest one.
     *
     * @param src The origin Node
     * @param destination The destiny Node. If no value is given, it defaults to nullptr.
     */
    void dijkstraShortestPath(Node * src, Node * destination = nullptr);
    
    /**
     * Implementation of Dijkstra's shortest path algorithm.
     * The shortest path will be fastest one.
     * This Dijkstra implementation takes into consideration the mean of Transport used.
     *
     * @param src The id of the origin Node.
     * @param dest The id of the destiny Node.
     * @param type Mean of Transport used.
     * @param scale Mean of transport scale .If no value is given it defaults to 5. The scale affects the weight of the Edge that was traversed with the given mean of transport.
     */
    void dijkstraShortestPath(node_id src_id, node_id dest_id, Transport::Type type, unsigned int scale = 5);

    /**
     * Implementation of Dijkstra's shortest path algorithm.
     * The shortest path will be the fastest one that takes less time to go through.
     * This Dijkstra implementation takes into consideration the mean of Transport used.
     *
     * @param src The origin Node.
     * @param dest The destiny Node.
     * @param type Mean of Transport used.
     * @param scale Mean of transport scale .If no value is given it defaults to 5. The scale affects the weight of the Edge that was traversed with the given mean of transport.
     */
    void dijkstraShortestPath(Node * src, Node * dest, Transport::Type type, unsigned int scale = 5);
    
    /**
     * Altered implementation of Dijkstra's shortest path algorithm, takes into account a maximum cost.
     * The shortest path will be the fastest one, but without never costing more than the maximum Cost.
     *
     * @param src_id The id of the source Node.
     * @param dest_id The id o destiny Node.
     * @param maxCost Path's maximum cost.
     */
    void dijkstraShortestPathWithMaxCost(node_id src_id, node_id dest_id, unsigned maxCost);
    
    /**
     * Calculates the path between to given nodes, represented by their IDs.
     *
     * @param src_id The id of the origin Node.
     * @param dest_id The id of the destiny Node.
     *
     * @return The calculated path (vector of Nodes).
     */
    vector<Node *> getPath(node_id src_id, node_id dest_id) const;
    
    /**
     * Calculates the path between to given nodes, represented by their IDs and returns the Edges that make the path.
     *
     * @param src_id The id of the origin Node.
     * @param dest_id The id of the destiny Node.
     *
     * @return The Edges of the calculated path.
     */
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
    
    void dfs(Node * v, vector<Node*> & res);
    
};


#endif /* Graph_h */
