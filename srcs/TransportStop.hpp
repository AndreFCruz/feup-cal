//
//  TransportStop.hpp
//
//  Created by Andre Cruz on 14/05/2017.
//

#ifndef TransportStop_hpp
#define TransportStop_hpp

#include "Node.hpp"


/**
 * Class used to store information for a Transport Stop.
 * Every stop has a name and an associated Node.
 */
class TransportStop {
private:
    string name;    /**< string name. The TransportStop's name. */
    Node * node;    /**< Node * node. Pointer to the TransportStop's node. */

public:

    /**
     * TransportStop's constructor.
     * Creates a TransportStop associated with the given Node.
     *
     * @param node The Node associated with this stop.
     * @param name This stop's name.
     */
    TransportStop(Node * node, string name);

    /**
     * Getter for the TransportStop's name.
     *
     * @return String with the stop's name.
     */
    string getName() const;

    /**
     * Getter for the TransportStop's Node.
     *
     * @return Node pointer.
     */
    Node * getNode() const;
};

#endif /* TransportStop_hpp */
