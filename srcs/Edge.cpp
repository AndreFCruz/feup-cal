//
//  Edge.cpp
//
//  Created by Andre Cruz on 01/04/2017.
//

#include <iomanip>
#include "Edge.hpp"

edge_id Edge::edge_count = 0;

Edge::Edge(Node * origin, Node * dest, Road * road, Transport::Type type) : origin(origin), dest(dest), road(road), type(type), edgeID(edge_count++) {
    length = GeographicCoords::getDistance(origin->getCoords(), dest->getCoords());
    
    if (type == Transport::ACCESS) {
        weight = Transport::MEAN_WAIT_TIME;
        cost = Transport::getInstance()->getCost(type);
    } else {
        weight = this->length / Transport::getInstance()->getVel(type);
        cost = this->length * Transport::getInstance()->getCost(type);
    }
}

unsigned Edge::getCost() const {
    return cost;
}

edge_id Edge::getID() const {
    return edgeID;
}

Node * Edge::getDest() const {
    return dest;
}

Road * Edge::getRoad() const {
    return road;
}

Node * Edge::getOrigin() const {
    return origin;
}

Transport::Type Edge::getType() const {
    return type;
}

float Edge::getWeight() const {
    return weight;
}

float Edge::getLength() const {
    return length;
}

ostream& operator<<(ostream & out, const Edge & edg) {
    out << "Edge from " << setw(8) << edg.getOrigin()->getID()
        << " to " << setw(8) << edg.getDest()->getID() << ".\n";
    
    if ( edg.getRoad() != nullptr && ! edg.getRoad()->getName().empty() )
        out << "Road: " << setw(25) << edg.getRoad()->getName() << ". ";
    
    out << "Transport type: ";
    switch (edg.getType()) {
        case Transport::FOOT:
            out << "by feet.";
            break;
        case Transport::BUS:
            out << "by bus.";
            break;
        case Transport::SUBWAY:
            out << "by subway.";
            break;
        default:
            out << "Transport type not catalogued.\n";
    }
    out << "\nLength: " << edg.getLength() << ". Weight (in mins): " << edg.getWeight() * 60 << ". Cost: " << edg.getCost() << endl;
    
    return out;
}

