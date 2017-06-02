//
//  Transport.hpp
//
//  Created by Andre Cruz on 01/04/2017.
//

#ifndef Transport_hpp
#define Transport_hpp

#include <unordered_map>

/**
 * Class used to represent means of Transport.
 * The difference between means of Transport is the velocity with which they can traverse a certain route.
 */
class Transport {
public:

	/**
	 * Enumeration containing the different means of transport.
	 */
    enum Type {
        FOOT,
        BUS,
        SUBWAY,
        ACCESS
    };

    /**
     * Getter for the current mean of Transport.
     * If no mean of transport exists, a new one is created.
     *
     * @return The current mean of Transport.
     */
    static Transport * getInstance();

    /**
     * Getter for the velocity of the current mean of Transport.
     *
     * @return Velocity of the current mean of Transport.
     */
    unsigned int getVel(Type t) const;

    /**
     * Getter for the cost of the current mean of Transport, in cents per Kilometer.
     *
     * @return Cost of the current mean of Transport.
     */
    unsigned int getCost(Type t) const;

    constexpr static const float MEAN_WAIT_TIME = 4. / 60;;  /**< unsigned int MEAN_WAIT_TIME. Mean wait time for a transport, in hours. */

private:

    /**
     * Explicit Default constructor.
     */
    Transport() = default;

    static Transport * singleton_instance;	/**< Transport * singleton_instance. Pointer to the current instance of Transport. */

    unsigned int velocities[3] {    // in km/h
        5, 38, 62
    };	/**< int[] velocities. Array containing the velocities of the different means of transport, in km/ h. */

    unsigned int costs[4] {
        0, 40, 0, 120
    };	/**< int[] costs. Array containing the costs of the different means of transport, in cents/km, or per entry if type is ACCESS. */

};

#endif /* Transport_hpp */
