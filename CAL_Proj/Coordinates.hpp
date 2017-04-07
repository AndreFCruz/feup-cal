//
//  Coordinates.hpp
//  CAL_GraphParser
//
//  Created by Andre Cruz on 28/03/2017.
//  Copyright © 2017 Andre Cruz. All rights reserved.
//

#ifndef Coordinates_hpp
#define Coordinates_hpp

#include <utility>

using namespace std;

class Point {
private:
    float x, y;
    
public:
    Point() = default;
    
    Point(float x, float y);
    
    float getX() const;
    
    float getY() const;
    
    static float getDistance(const Point & p1, const Point & p2);
};

class GeographicCoords {
private:
    static const unsigned int EarthRadius;

    float longitude;    // in radians
    float latitude;     // in radians
    
public:
    GeographicCoords() = default;
    
    GeographicCoords(float lat, float lon);
    
    float getLon() const;
    
    float getLat() const;
    
    Point getPoint(pair<float,float> latRange, pair<float,float> lonRange) const;
    
    static float getDistance(const GeographicCoords & p1, const GeographicCoords & p2);
};



#endif /* Coordinates_hpp */
