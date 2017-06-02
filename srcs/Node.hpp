//
//  Node.hpp
//
//  Created by Andre Cruz on 01/04/2017.
//

#ifndef Node_hpp
#define Node_hpp

#include <iostream>
#include <vector>
#include "Coordinates.hpp"
#include "Edge.hpp"
#include "Transport.hpp"

using namespace std;

/**
 * Type used to represent the ID of a Node.
 */
typedef unsigned long node_id;

class Edge;

/**
 * A class used to represent a Node in a Graph.
 * Every Node has a unique ID, used to represent itself.
 * Every Edge is also associated to a Road, that contains more information about it.
 */
class Node {
private:
    static int count;						/**< int count. Counter for assuring Nodes' parserIDs are sequential and unique. */
    
    static pair<float,float> latRange;		/**< pair<float, float> latRange. Latitude range, where the first element is the minimum and the second the maximum. */
    static pair<float,float> lonRange;		/**< pair<float, float> lonRange. Longitude range, where the first element is the minimum and the second the maximum. */
    
    int parserID;							/**< int parserID. The correspondent ID of the Node in the parser. This ID is unique and sequential */
    node_id id;								/**< node_id id. The Node's ID. */
    GeographicCoords coords;				/**< GeographicCoords coords. Node's correspondent Geographic Coordinates in a real life map. */
    Point point;							/**< Point point. Node's correspondent Point in a 2D Plane. */
    
    vector<Edge *> edges; 					/**< vector<Edge*> edges. Vector containing all the Edges that have the Node as origin Node. Edges are initially ordered by weight. */
    
    /**
     * Function used to update the Latitude and Longitude ranges.
     * If a new Node Latitude or Longitude is not inside the ranges, than the ranges are updated.
     */
    void setStaticRange() const;
    
public:
    
    bool visited = false;			/**< bool visited. Flag: If true, Node was already visited in the path, otherwise was not. */
    bool processing = false;		/**< bool processing. Flag: If true, Node is being processed in the Dijkstra algorithm, otherwise is not. */
    float dist = numeric_limits<float>::infinity();		/**< float dist. Distance used for calculus in the Dijkstra algorithm. Represents the minimum distance from the Node to the origin Node. */
    Node * path = nullptr;			/**< Node* path. Pointer to the previous Node in the path. */
    Edge * edgePath = nullptr;		/**< Edge* path. Pointer to the Edge, linking the Node to the previous one in the path. */
    
    /**
     * Function the returns the Latitude Range.
     *
     * @return Latitude range, where the first element is the minimum and the second the maximum.
     */
    static pair<float,float> getLatRange();

    /**
     * Function the returns the Longitude Range.
     *
     * @return Longitude range, where the first element is the minimum and the second the maximum.
     */
    static pair<float,float> getLonRange();
    
    /**
     * Node's constructor from file.
     * Creates a Node with the data passed by the argument input stream.
     *
     * @param input The input stream to read from in order to build a Node object.
     */
    Node(istream & input);
    
    /**
     * Incomplete constructor for Node.
     * Used only for Graph's copy constructor, as all other attributes aren't needed
     */
    Node(node_id id, GeographicCoords coords);
    
    /**
     * Getter for Node's ID.
     * The ID is used to represent a Node, since there are no two Nodes with the same ID.
     *
     * @return Node's ID.
     */
    node_id getID() const;

    /**
     * Getter for Node's Parser ID.
     * The parser ID is also used to represent a Node, since there are no two Nodes with the same parser ID.
     * This ID is sequential.
     *
     * @return Node's parser ID.
     */
    int getParserID() const;
    
    /**
     * Getter for the Edge with the smallest weight, out of all the Edges associated to the Node.
     *
     * @return Edge associated to the Node, with the smallest weight.
     */
    Edge * getEdge() const; // first order in vec - smallest weight

    /**
     * Getter for the Edge with the mean of Transport given, out of all the Edges associated to the Node.
     *
     * @return Edge associated to the Node, whose mean of Transport is equal to the one given.
     */
    Edge * getEdge(Transport::Type type) const;
    
    /**
     * Getter for flag that if set Node's has already been visited in path, otherwise has not.
     *
     * @return Value of the Flag.
     */
    bool isVisited() const;

    /**
     * Function changes the correspondent flag value.
     * If set Node's has already been visited in path, otherwise has not.
     * If no value is given, it defaults to true.
     *
     * @param state State to change the flag to.
     */
    void setVisited(bool state = true);
    
    /**
     * Builds the Node's correspondent Point in a 2D Plane.
     *
     * @param latRange Latitude range, where the first element is the minimum and the second the maximum.
     * @param lonRange Longitude range, where the first element is the minimum and the second the maximum.
     */
    void initiatePoint(pair<float,float> latRange, pair<float,float> lonRange);
    
    /**
     * Getter for Node's Geographic Coordinates.
     *
     * @return Node's Geographic Coordinates.
     */
    GeographicCoords getCoords() const;

    /**
     * Getter for Node's correspondent Point in a 2D Plane.
     *
     * @return Node's correspondent Point.
     */
    Point getPoint() const;
    
    /**
     * Function that associates the given Edge to the Node.
     *
     * @param ptr Edge to be associated.
     */
    void addEdge(Edge * ptr);

    /**
     * Function that removes the Edge given from the Node's associated Edges.
     *
     * @param ptr Edge to be removed.
     *
     * @return True if the Edge was removed, false otherwise.
     */
    bool removeEdge(Edge * ptr);

    /**
     * Function that removes the Edges whose destiny Node is the given Node.
     *
     * @param id ID of the Node used to updated the Edges.
     */
    void removeEdgesTo(node_id id);
    
    /**
     * Getter for the number of Edges associated to the Node.
     *
     * @return Number of Edges associated to the Node.
     */
    size_t getNumEdges() const;
    
    /**
     * Getter for all the Edges associated to the Node.
     *
     * @return vector of all the Edges associated to the Node.
     */
    const vector<Edge*> & getEdges() const;
    
};


#endif /* Node_hpp */
