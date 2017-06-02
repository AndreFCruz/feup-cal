//
//  Graph.hpp
//
//  Created by Andre Cruz on 28/03/2017.
//

#ifndef Graph_h
#define Graph_h

#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <unordered_map>
#include "Coordinates.hpp"
#include "Node.hpp"
#include "Edge.hpp"
#include "Road.hpp"
#include "TransportStop.hpp"
#include "SubwayStop.hpp"


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
    
    unordered_map<Node*, TransportStop*> stops;   /**< unordered_map<Node*, TransportStop*> stops. Hash map containing all the Graph's TransportStops. */
    unordered_map<TransportStop*, SubwayStop*> subway_stops;  /**< unordered_map<TransportStop*, SubwayStop*> subway_stops. Hash map containing all the Graph's SubwayStops. */
    
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
     * @param input Input stream containing the Edge's whose mean of transport is the one given.
     * @param type Mean of transport that is going to be assigned to the Edges.
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
    
    /**
     * Minimum edit distance between a string and each of the space
     * seperated words in the string sentence.
     *
     * @param word String to compare.
     * @param sentence Text to compare.
     * @return Minimum edit distance.
     */
    unsigned minEditDistance(string word, string sentence) const;

    /**
     * Edit distance between given strings.
     * 
     * @param p Pattern string.
     * @Param t Text string.
     * @return Edit distance between the given strins.
     */
    unsigned editDistance(string p, string t) const;
    
    /**
     * Auxiliary function for pre-processing of KMP algorithm (prefix function).
     *
     * @param pattern Pattern to match.
     * @param f Array of integers to store prefix table.
     */
    void preKMP(string pattern, int f[]) const;
    
    /**
     * Exact string matching with Knuth–Morris–Pratt algorithm.
     *
     * @param str Pattern string to match.
     * @param text Text to be matched in.
     * @return Whether or not it matches.
     */
    bool KMP(string str, string text) const;
    
public:
    /**
     * Graph's constructor.
     * Creates a Graph with the data passed by the arguments input streams.
     *
     * @param nodes_in The input stream to read from in order to populate the Nodes' Hash map.
     * @param edges_in The input stream to read from in order to populate the Edges' Hash map.
     * @param roads_in The input stream to read from in order to populate the Roads' Hash map.
     * @param subway_edges The input stream containing the Edges whose means of transport is the Subway.
     * @param bus_edges The input stream containing the Edges whose mean of transport is the Bus.
     * @param transport_stops The input stream containing the TransportStops' names.
     * @param subway_nodes The input stream containing the Nodes which are subway stops.
     */
    Graph(istream & nodes_in, istream & edges_in, istream & roads_in, istream & subway_edges,
          istream & bus_edges, istream & transport_stops, istream & subway_nodes);
    
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
     * Getter for a specific TransportStop
     *
     * @param node The given node.
     *
     * @return Correspondent TransportStop pointer.
     */
    TransportStop * getTransportStop(Node * node) const;
    
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
     * @param src_id The id of the origin Node.
     * @param dest_id The id of the destiny Node.
     * @param type Mean of Transport used.
     * @param scale Mean of transport preference scale (bigger scale means higher preference). If no value is given it defaults to 6.
     */
    void dijkstraShortestPath(node_id src_id, node_id dest_id, Transport::Type type, unsigned int scale = 6);

    /**
     * Implementation of Dijkstra's shortest path algorithm.
     * The shortest path will be the fastest one that takes less time to go through.
     * This Dijkstra implementation takes into consideration the mean of Transport used.
     *
     * @param src The origin Node.
     * @param dest The destiny Node.
     * @param type Mean of Transport used.
     * @param scale Mean of transport preference scale (bigger scale means higher preference). If no value is given it defaults to 6.
     */
    void dijkstraShortestPath(Node * src, Node * dest, Transport::Type type, unsigned int scale = 6);
    
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
    
    /**
     * Runs Depth-First Search from the node pointed to by v,
     * and pushes visited nodes into the res vector, in order.
     *
     * @param v Node * to start node
     * @param res Vector to be filled
     */
    void dfs(Node * v, vector<Node*> & res);
    
    /* Performs approximate string matching with the Graph's TransportStops.
     *
     * @param str The string pattern to match.
     */
    map<unsigned,string> approximateMatch(string str) const;
    
    /* Performs exact string matching with the Graph's TransportStops.
     *
     * @param str The string pattern to match.
     */
    vector<string> exactMatch(string str) const;
    
};


#endif /* Graph_h */
