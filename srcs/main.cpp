//
//  main.cpp
//
//  Created by Andre Cruz on 28/03/2017.
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
//const string HOME = "./map/";
const string HOME = "../map/";

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
    cout << "\n\tPress ENTER to continue...";
    string trail; getline(cin, trail);

    // Initiate Main Menu
    mainMenu(g);


    return 0;
}
