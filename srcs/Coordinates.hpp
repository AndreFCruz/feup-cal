//
//  Coordinates.hpp
//
//  Created by Andre Cruz on 28/03/2017.
//

#ifndef Coordinates_hpp
#define Coordinates_hpp

#include <utility>

using namespace std;

/**
 * A class used to represent a Point in a 2D Plane.
 * Every Point is represented as (x, y) in cartesian coordinates.
 */
class Point {
private:
    float x;	/**< float x. Point's coordinate value on the horizontal axis. */
    float y;	/**< float y. Point's coordinate value on the vertical axis. */
    
public:

    /**
     * Explicit Default constructor.
     */
    Point() = default;
    
    /**
     * Point's constructor.
     * Creates a Point with the given coordinates.
     *
     * @param x Point's coordinate value on the horizontal axis.
     * @param y Point's coordinate value on the vertical axis.
     */
    Point(float x, float y);
    
    /**
     * Getter for coordinate value on the horizontal axis.
     *
     * @return coordinate value on the horizontal axis.
     */
    float getX() const;
    
    /**
     * Getter for coordinate value on the vertical axis.
     *
     * @return coordinate value on the vertical axis.
     */
    float getY() const;
    
    /**
     * Function used to calculate the distance between two given Points.
     * Makes use of the Pythagorean Theorem Formula
     *
     * @param p1 Point to be used in the calculus.
     * @param p2 Point to be used in the calculus.
     *
     * @return the distance between the two Points.
     */
    static float getDistance(const Point & p1, const Point & p2);
};


/**
 * Class used to represent Geographical Coordinates.
 * Therefore, every Coordinate is represented with longitude and latitude.
 */
class GeographicCoords {
private:
    static const unsigned int EarthRadius;	/**< const unsigned EarthRadius. Value of Earth's radius in kilometers. */

    float longitude;    /**< float longitude. Longitude value of the Geographical Coordinate, in radians. */
    float latitude;     /**< float latitude. Latitude value of the Geographical Coordinate, in radians. */
    
public:

    /**
     * Explicit Default constructor
     */
    GeographicCoords() = default;
    
    /**
     * Geographic Coordinates constructor.
     * Creates a Geographic Coordinate with the given Latitude and Longitude.
     *
     * @param lat Latitude value, in radians.
     * @param lon Longitude value, in radians.
     */
    GeographicCoords(float lat, float lon);
    
    /**
     * Getter for longitude value of the Geographic Coordinate.
     *
     * @return longitude value.
     */
    float getLon() const;
    
    /**
     * Getter for latitude value of the Geographic Coordinate.
     *
     * @return latitude value.
     */
    float getLat() const;
    
    /**
     * Parser from a Geographic Coordinate to a Point.
     * This parser takes in consideration the Latitude and Longitude range, so that it can map the 2D Referential.
     *
     * @param latRange Pair of floats containing the Latitude range, where the first element is the minimum and the second the maximum.
     * @param lonRange Pair of floats containing the Longitude range, where the first element is the minimum and the second the maximum.
     *
     * @return the Point gotten from parsing the Geographic Coordinate.
     */
    Point getPoint(pair<float,float> latRange, pair<float,float> lonRange) const;
    
    /**
     * Mathematical formula for the projected (2D) distance between two points in space,
 	 * defined by their Geographic Coordinates.
 	 * https://en.wikipedia.org/wiki/Geographical_distance#Spherical_Earth_projected_to_a_plane
     *
     * @param p1 Geographic Coordinate to be used in the calculus.
     * @param p2 Geographic Coordinate to be used in the calculus.
     *
     * @return the distance between the two Geographic Coordinates.
     */
    static float getDistance(const GeographicCoords & p1, const GeographicCoords & p2);
};



#endif /* Coordinates_hpp */
