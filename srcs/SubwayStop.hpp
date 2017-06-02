//
//  SubwayStop.hpp
//
//  Created by Andre Cruz on 14/05/2017.
//

#ifndef SubwayStop_hpp
#define SubwayStop_hpp

#include "Node.hpp"
#include "TransportStop.hpp"

/**
 * Class used to store information for a Subway Stop.
 * Every subway stop has an associated TransportStop and its closest in-road Node.
 */
class SubwayStop {
private:
    Node * closest_node;    /**< Node * closest_node. Pointer to the road Node closest to this stop. */
    TransportStop * stop;   /**< TransportStop * stop. Pointer to the TransportStop information associated with this stop. */

public:

    /**
     * SubwayStop's constructor.
     * Creates a SubwayStop associated with the given TransportStop and Node.
     *
     * @param stop Pointer to associated TransportStop.
     * @param closest_node Pointer to associated Node, closest do the stop's Node.
     */
    SubwayStop(TransportStop * stop, Node * closest_node);

    /**
     * Getter for the closest road node to this subway stop.
     *
     * @return Node associated with this instance.
     */
    Node * getClosestNode() const;

    /**
     * Getter for the TransportStop which has this SubwayStop's information.
     *
     * @return TransportStop associated with this instance.
     */
    TransportStop * getTransportStop() const;
};

#endif /* SubwayStop_hpp */
