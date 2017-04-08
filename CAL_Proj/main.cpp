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

const string HOME = "/Users/andre/Documents/CAL_Proj/map2/";

const string EDGES_PATH = HOME + "edges.txt";
const string NODES_PATH = HOME + "nodes.txt";
const string ROADS_PATH = HOME + "roads.txt";
const string SUBWAY_PATH = HOME + "subway.txt";
const string BUS_PATH = HOME + "bus.txt";

int main() {
    
    ifstream nodes_ifs(NODES_PATH), roads_ifs(ROADS_PATH), edges_ifs(EDGES_PATH), subway(SUBWAY_PATH), bus(BUS_PATH);
    
    if ( nodes_ifs.is_open() && roads_ifs.is_open() && edges_ifs.is_open() )
        cerr << "Valid Parser Input\n";
    else {
        cerr << "Invalid Parser Input Files\n";
        return 1;
    }
    
    if ( subway.is_open() && bus.is_open() )
        cerr << "Valid Transports Input\n";
    else {
        cerr << "Invalid Transports Input Files\n";
        return 1;
    }
    
    Graph g(nodes_ifs, roads_ifs, edges_ifs, subway, bus);

    GraphViewer * gv = viewGraphComplete(g);
    
//    node_id origin, dest;
//    cout << "Start node: "; cin >> origin;
//    cout << "Destination node: "; cin >> dest;
//    
//    g.dijkstraShortestPath(origin, dest);
//    auto path = g.getPath(origin, dest);
//    
//    viewGraphPath(gv, path);
    
//    g.dijkstraShortestPath(430006697LL, 4773399285LL); unsigned i = 1;
//    for (auto elem : g.getPath(430006697LL, 4773399285LL))
//        cout << i++ << ". " << elem->getID() << endl;
    
    
    return 0;
}
