//
//  Edge.hpp
//
//  Created by Andre Cruz on 01/04/2017.
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

/**
 * Type used to represent the ID of an Edge.
 */
typedef unsigned int edge_id;


/**
 * A class used to represent a Edge in a Graph, therefore used to join two Nodes.
 * Every Edge has a unique ID, used to represent itself; a Node as Origin and a Node as Destiny.
 * Every Edge is also associated to a Road, that contains more information about it.
 */
class Edge {
private:
    static edge_id edge_count;	/**< edge_id edge_count. Counter for assuring edges' IDs are sequential and unique. */

    edge_id edgeID;				/**< edge_id edgeID. The Edge's unique ID. */

    Node * origin = nullptr;	/**< Node * origin. The Edge's origin Node. */
    Node * dest = nullptr;		/**< Node * dest. The Edge's destiny Node. */
    
    Road * road = nullptr;		/**< Road * road. The Road associated to this Edge, containing additional information about it. */
    
    float length;				/**< float length. The physical distance between the two Nodes linked by this Edge. */
    
    float weight;				/**< float weight. The average time (in seconds - SI unit) needed to traverse this Edge. Dependent of the mean of transport used. */
    
    unsigned cost;				/**< unsigned cost. Monetary cost of traversing this Edge. Dependent of the mean of transport used. */
    
    Transport::Type type;		/**< Transport::Type type. The type of transport used to traverse this Edge. */
    
public:

    /**
     * Edge's constructor.
     * Creates a Edge with a given origin Node, destiny Node and associated Rode.
     * A transport mean may be provided, otherwise defaults to FOOT (walking).
     *
     * @param origin Edge's origin Node.
     * @param dest Edge's destiny Node.
     * @param road Rode associated to the Edge that is being created.
     * @param type Type of transport used to traverse the Edge that is being created.
     */
    Edge(Node * origin, Node * dest, Road * road, Transport::Type type = Transport::FOOT);
    
    /**
     * Getter for Edge's cost.
     * Corresponds to the monetary cost it takes to traverse this Edge.
     *
     * @return The cost of traversing this Edge.
     */
    unsigned getCost() const;
    
    /**
     * Getter for Edge's ID.
     * The ID is used to represent an Edge, since there are no two Edges with the same ID.
     *
     * @return The Edge's ID.
     */
    edge_id getID() const;

    /**
     * Getter for Edge's destiny Node.
     *
     * @return Edge's destiny Node.
     */
    Node * getDest() const;

    /**
     * Getter for Edge's origin Node.
     *
     * @return Edge's origin Node.
     */
    Node * getOrigin() const;

    /**
     * Getter for Edge's Road.
     * Road's contain additional information regarding the Edges.
     *
     * @return Road associated to this Edge.
     */
    Road * getRoad() const;
    
    /**
     * Getter for Edge's length.
     * Corresponds to the physical distance between the two Nodes linked by this edge.
     *
     * @return Distance of the two nodes linked by this Edge.
     */
    float getLength() const;
    
    /**
     * Getter for Edge's weight.
     * Corresponds to the average time (in seconds - SI unit) needed to traverse this Edge.
     *
     * @return Average time needed to traverse this Edge.
     */
    float getWeight() const;
    
    /**
     * Getter for Edge's type of transport.
     * The type of transport used can be one out of three options: bus, subway or walking.
     *
     * @return The type of transport used to traverse this Edge.
     */
    Transport::Type getType() const;
    
    /**
     * Overload of operator << for Class Edge.
     * Writes the Edge passed as second argument to the outstream passed as first argument.
     *
     * @param out Output stream to write to.
     * @param e Edge the will be written.
     *
     * @return The output stream, therefore allowing chaining.
     */
    friend ostream& operator<<(ostream & out, const Edge & e);
};

#endif /* Edge_hpp */
