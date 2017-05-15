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
//const string HOME = "/Users/andre/Downloads/CAL-PROJ1-4efdfdcd8a35724ef52125bf7f6ba6c7a4bf771f/map2/";
const string HOME = "./map/";

const string EDGES_PATH = HOME + "edges.txt";
const string NODES_PATH = HOME + "nodes.txt";
const string ROADS_PATH = HOME + "roads.txt";
const string SUBWAY_PATH = HOME + "subway_edges.txt";
const string BUS_PATH = HOME + "bus_edges.txt";
const string TRANSPORT_STOPS_PATH = HOME + "transport_stops.txt";
const string SUBWAY_NODES_PATH = HOME + "subway_nodes.txt";

int main() {
    
    ifstream nodes_ifs(NODES_PATH), edges_ifs(EDGES_PATH), roads_ifs(ROADS_PATH), subway_edges_ifs(SUBWAY_PATH),
            bus_edges_ifs(BUS_PATH), stops_ifs(TRANSPORT_STOPS_PATH), subway_nodes_ifs(SUBWAY_NODES_PATH);
    
    if ( not (nodes_ifs.is_open() && roads_ifs.is_open() && edges_ifs.is_open()) ) {
        cerr << "Invalid Parser Input Files\n";
        return 1;
    }
    
    if ( not (subway_edges_ifs.is_open() && bus_edges_ifs.is_open() && stops_ifs.is_open() && subway_nodes_ifs.is_open()) ) {
        cerr << "Invalid Transports Input Files\n";
        return 1;
    }
    
    Graph g(nodes_ifs, edges_ifs, roads_ifs, subway_edges_ifs, bus_edges_ifs, stops_ifs, subway_nodes_ifs);

/*
    
    GraphViewer * gv = viewGraphComplete(g);
    
    // User Interface
//    askForPath(gv, g);
    
    // Tests
    node_id origin, dest;
    origin = 430006697LL;
    dest = 4773399285LL;
    
//    g.dijkstraShortestPath(origin, dest, Transport::FOOT, 12);
    g.dijkstraShortestPath(origin, dest, Transport::BUS, 20);
//    g.dijkstraShortestPathWithMaxCost(origin, dest, 80); // comparar com preferencia de autocarro
//    g.dijkstraShortestPathWithMaxCost(origin, dest, 105);
    
    
    auto path = g.getPath(origin, dest);
    auto edges = g.getPathEdges(origin, dest);
    viewGraphPath(gv, path);
    widenGraphPathEdges(gv, edges);

    printPathStats(g, origin, dest);

    // Print edges
//    for (auto ptr : edges)
//        cout << *ptr << endl;
    
*/
    
    return 0;
}
