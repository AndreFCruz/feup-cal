//
//  Road.cpp
//
//  Created by Andre Cruz on 01/04/2017.
//

#include <string.h>
#include "Road.hpp"

Road::Road(road_id id, string name, bool twoWay) : id(id), name(name), twoWay(twoWay) {};

Road::Road(istream & input) {
    input >> id;
    input.ignore(1, ';');
    
    getline(input, name, ';');
    
    string tmp;
    getline(input, tmp);
    if (strncmp("False", tmp.c_str(), 5) == 0)
        twoWay = false;
    else if (strncmp("True", tmp.c_str(), 4) == 0)
        twoWay = true;
    else
        throw ios_base::failure("Bad input from stream");
}

road_id Road::getID() const {
    return id;
}

string Road::getName() const {
    return name;
}

bool Road::isTwoWay() const {
    return twoWay;
}

bool Road::addEdge(Edge * ptr) {
    return edges.insert(ptr).second;
}

const set<Edge *> Road::getEdges() {
    return edges;
}
