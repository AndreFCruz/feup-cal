//
//  Coordinates.cpp
//
//  Created by Andre Cruz on 28/03/2017.
//

#include <cmath>
#include "Coordinates.hpp"

Point::Point(float x, float y) : x(x), y(y) {}
    
float Point::getX() const {
    return x;
}
    
float Point::getY() const {
    return y;
}
    
float Point::getDistance(const Point & p1, const Point & p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

/**
 * Value of Earth's radius in kilometers.
 */
const unsigned int GeographicCoords::EarthRadius = 6371;

GeographicCoords::GeographicCoords(float lat, float lon) : longitude(lon), latitude(lat) {}

float GeographicCoords::getLat() const {
    return latitude;
}

float GeographicCoords::getLon() const {
    return longitude;
}
    
Point GeographicCoords::getPoint(pair<float,float> latRange, pair<float,float> lonRange) const {
    static float scaleY = 8000000;
    static float scaleX = 1600000;
    
    float x = floor( ((float) longitude - lonRange.first) * scaleX / (lonRange.second - lonRange.first) );
    float y = scaleY - floor( ((float) latitude - latRange.first) * scaleY / (latRange.second - latRange.first) );
    
    return Point(x, y);
}

/**
 * Mathematical formula for the projected (2D) distance between two points in space,
 * defined by their Geographic Coordinates.
 * https://en.wikipedia.org/wiki/Geographical_distance#Spherical_Earth_projected_to_a_plane
 */
float GeographicCoords::getDistance(const GeographicCoords & p1, const GeographicCoords & p2) {
    return EarthRadius * sqrt(pow(p1.getLat() - p2.getLat(), 2) + pow(cos((p1.getLat() + p2.getLat()) / 2) * (p1.getLon() - p2.getLon()), 2));
}
