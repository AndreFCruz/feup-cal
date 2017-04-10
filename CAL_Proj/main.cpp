//
//  main.cpp
//  CAL_GraphParser
//
//  Created by Andre Cruz on 28/03/2017.
//  Copyright © 2017 Andre Cruz. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Graph.hpp"
#include "Node.hpp"
#include "Edge.hpp"
#include "Road.hpp"
#include "ViewerFunctions.hpp"

using namespace std;

// Work Directory must be set to $PROJECT_DIR
const string HOME = "./map2/";

const string EDGES_PATH = HOME + "edges.txt";
const string NODES_PATH = HOME + "nodes.txt";
const string ROADS_PATH = HOME + "roads.txt";
const string SUBWAY_PATH = HOME + "subway.txt";
const string BUS_PATH = HOME + "bus.txt";

int main() {
    
    ifstream nodes_ifs(NODES_PATH), roads_ifs(ROADS_PATH), edges_ifs(EDGES_PATH), subway_ifs(SUBWAY_PATH), bus_ifs(BUS_PATH);
    
    if ( not (nodes_ifs.is_open() && roads_ifs.is_open() && edges_ifs.is_open()) ) {
        cerr << "Invalid Parser Input Files\n";
        return 1;
    }
    
    if ( not (subway_ifs.is_open() && bus_ifs.is_open()) ) {
        cerr << "Invalid Transports Input Files\n";
        return 1;
    }

    Graph g(nodes_ifs, roads_ifs, edges_ifs, subway_ifs, bus_ifs);
    
    // User Interface
//    GraphViewer * gv = viewGraphComplete(g);
//    askForPath(gv, g);
    
    // Tests
    node_id origin, dest;
    origin = 430006697LL;
    dest = 4773399285LL;
    
//    g.dijkstraShortestPath(origin, dest, Transport::FOOT, 12);
    g.dijkstraShortestPath(origin, dest, Transport::BUS);
//    g.dijkstraShortestPathWithMaxCost(origin, dest, 80); // comparar com preferencia de autocarro
//    g.dijkstraShortestPathWithMaxCost(origin, dest, 105);
    
    auto path = g.getPath(origin, dest);
    auto edges = g.getPathEdges(origin, dest);
    
    GraphViewer * gv = viewGraphComplete(g);
    viewGraphPath(gv, path);
    widenGraphPathEdges(gv, edges);

    // Print edges
//    for (auto ptr : edges)
//        cout << *ptr << endl;
    
    printPathStats(g, origin, dest);
    
    return 0;
}
