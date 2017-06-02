//
//  Road.hpp
//
//  Created by Andre Cruz on 01/04/2017.
//

#ifndef Road_hpp
#define Road_hpp

#include <set>
#include "Edge.hpp"

/**
 * Type used to represent the ID of a Road.
 */
typedef unsigned long road_id;

using namespace std;

class Edge;

/**
 * Class used to represent a Road.
 * Every Road has a unique ID, a name, and a flag regarding the direction of the Road.
 * Roads can also be associated to different Edges.
 */
class Road {
private:
    road_id id;			/**< road_id id. Road's unique ID, used to represent itself. */
    string name;		/**< string name. Road's name. */
    bool twoWay;		/**< bool twoWay. Flag regarding Road's direction. If set traffic goes both ways, otherwise traffic only goes one way. */
    
    set<Edge *> edges;	/**< set <Edge *> edges. Set that contains all the edges associated to the Road. */

public:

    /**
     * Road's constructor.
     * Creates a Road with the given ID, name and flag
     * If the flag is set traffic goes both ways, otherwise traffic only goes one way.
     *
     * @param id Road's unique ID.
     * @param name Road's Name.
     * @param twoWay Flag regarding Road's traffic direction.
     */
    Road(road_id id, string name, bool twoWay);
    
    /**
     * Road's constructor from file.
     * Creates a Road with the data passed by the argument input stream.
     *
     * @param input The input stream to read from in order to build a Road object.
     */
    Road(istream & input);
    
    /**
     * Getter for Road's ID.
     * The ID is used to represent a Road, since there are no two Roads with the same ID.
     *
     * @return The Road's ID.
     */
    road_id getID() const;
    
    /**
     * Getter for Road's Name.
     *
     * @return The Road's name.
     */
    string getName() const;
    
    /**
     * Getter for Road's flag regarding its direction.
	 * If the flag is set traffic goes both ways, otherwise traffic only goes one way.
     *
     * @return flag regarding Road's direction.
     */
    bool isTwoWay() const;
    
    /**
     * Function used to associate an Edge to the Road.
     *
     * @param ptr to be associated
     *
     * @return true if the Edge was added to the container of all associated Edges, false otherwise.
     */
    bool addEdge(Edge * ptr);
    
    /**
     * Getter for all Edges associated to the Road.
     *
     * @return Set that contains all Edges associated to the Road.
     */
    const set<Edge *> getEdges();
};


#endif /* Road_hpp */
