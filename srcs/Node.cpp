//
//  Node.cpp
//
//  Created by Andre Cruz on 01/04/2017.
//

#include "Node.hpp"

int Node::count = 0;
auto Node::latRange = make_pair((float) 0, (float) 0);
auto Node::lonRange = make_pair((float) 0, (float) 0);

pair<float,float> Node::getLatRange() {
    return Node::latRange;
}

pair<float,float> Node::getLonRange() {
    return Node::lonRange;
}

Node::Node(istream & input) : parserID(count++) {
    input >> id; input.get();
    
    // ignore degrees
    input.ignore(64, ';');
    input.ignore(64, ';');
    
    float lat, lon;
    input >> lat;
    input.ignore(1, ';');
    input >> lon;
    input.ignore(1, '\n');
    
    coords = GeographicCoords(lon, lat);
    
    setStaticRange();
}

Node::Node(node_id id, GeographicCoords coords) : id(id), coords(coords) {}


void Node::setStaticRange() const {
    float lat = coords.getLat();
    float lon = coords.getLon();
    
    if (lat < latRange.first)
        latRange.first = lat;
    else if (lat > latRange.second)
        latRange.second = lat;
    
    if (lon < lonRange.first)
        lonRange.first = lon;
    else if (lon > lonRange.second)
        lonRange.second = lon;
}

node_id Node::getID() const {
    return id;
}

int Node::getParserID() const {
    return parserID;
}

Edge * Node::getEdge() const {
    if (edges.empty())
        return nullptr;
    
    return edges.at(0);
}
Edge * Node::getEdge(Transport::Type type) const {
    for (Edge * e : edges)
        if (e->getType() == type)
            return e;
    return nullptr;
}

bool Node::isVisited() const {
    return visited;
}

void Node::setVisited(bool state) {
    this->visited = state;
}

GeographicCoords Node::getCoords() const {
    return coords;
}

Point Node::getPoint() const {
    return point;
}

void Node::addEdge(Edge * e) {
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if ( (*it)->getWeight() > e->getWeight() ) {
            edges.insert(it, e);
            return;
        }
    }
    
    edges.push_back(e);
}

bool Node::removeEdge(Edge * ptr) {
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if  ( (*it) == ptr ) {
            delete ptr;
            edges.erase(it);
            return true;
        }
    }
    
    return false;
}

void Node::removeEdgesTo(node_id id) {
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if  ( (*it)->getDest()->getID() == id ) {
            delete (*it);
            it = edges.erase(it);
            --it;
        }
    }
}

size_t Node::getNumEdges() const {
    return edges.size();
}

const vector<Edge*> & Node::getEdges() const {
    return edges;
}

void Node::initiatePoint(pair<float, float> latRange, pair<float, float> lonRange) {
    point = coords.getPoint(latRange, lonRange);
}
