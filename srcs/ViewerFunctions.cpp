//
//  ViewerFunctions.cpp
//
//  Created by Andre Cruz on 06/04/2017.
//

#include <iostream>
#include <iomanip>
#include "Graph.hpp"
#include "Edge.hpp"
#include "Node.hpp"
#include "Road.hpp"
#include "graphviewer.h"
#include "ViewerFunctions.hpp"

using namespace std;

float getPathLength(const vector<Node *> & path) {
    float len = 0;
    for (size_t i = 1; i < path.size(); i++)
        len += GeographicCoords::getDistance(path[i-1]->getCoords(), path[i]->getCoords());
    
    return len == 0 ? numeric_limits<float>::infinity() : len;
}

vector<Node*> getPathFromEdges(const vector<Edge *> & edges) {
    vector<Node*> res; res.reserve(edges.size() + 1);
    res.push_back(edges.front()->getOrigin());
    
    auto it = edges.begin();
    for ( ; it != edges.end(); it++)
        res.push_back((*it)->getDest());
    
    res.push_back((*it)->getDest());
    
    return res;
}

GraphViewer * viewGraphComplete(Graph & g) {
    
    GraphViewer * gv = new GraphViewer(600000, 600000, false);
    
    gv->setBackground("background.jpg");
    gv->createWindow(1400, 1200);

    gv->defineVertexColor("yellow");
    gv->defineEdgeColor("black");
    
    // Add all nodes
    for (auto p : g.getNodes()) {
        Node * node = p.second;

//        cout << id << ". " << node->getPoint().getX() << " . " << node->getPoint().getY() << endl;
        gv->addNode(node->getParserID(), node->getPoint().getX(), node->getPoint().getY());
        
        TransportStop * stop;
        if ( (stop = g.getTransportStop(node)) != nullptr )
            gv->setVertexLabel(node->getParserID(), stop->getName());
        
    }
    gv->defineVertexSize(1);
    
    // helper for displaying road names only once
    unordered_map<road_id, bool> roadNameDisplayed;
    for (auto p : g.getRoads()) {
        Road * road = p.second;
        roadNameDisplayed.insert(make_pair(road->getID(), false));
    }
    
    // Add all edges
    for (auto & p : g.getEdges()) {
        Edge * edg = p.second;
        gv->addEdge(edg->getID(), edg->getOrigin()->getParserID(), edg->getDest()->getParserID(), EdgeType::DIRECTED);
        
        switch (edg->getType()) {
            case Transport::FOOT:
                gv->setEdgeColor(edg->getID(), "black");
                break;
            case Transport::BUS:
                gv->setEdgeColor(edg->getID(), "blue");
                gv->setEdgeThickness(edg->getID(), 4);
                break;
            case Transport::SUBWAY:
                gv->setEdgeColor(edg->getID(), "red");
                gv->setEdgeThickness(edg->getID(), 5);
                break;
            case Transport::ACCESS:
                gv->setEdgeColor(edg->getID(), "green");
                gv->setEdgeThickness(edg->getID(), 3);
                break;
        }
        
        Road * road = edg->getRoad();
        if (road != nullptr && ! roadNameDisplayed[road->getID()]) {
            gv->setEdgeLabel(edg->getID(), road->getName());
            roadNameDisplayed[road->getID()] = true;
        }
    }
    
    gv->rearrange();
    
    cout << "Finished Loading GraphViewer." << endl << endl;
        
    return gv;
}

GraphViewer * viewGraphPath(GraphViewer * gv, const vector<Node *> & path) {
    
    for (const Node * node : path) {
        gv->setVertexSize(node->getParserID(), 75);

        if (node->edgePath == nullptr) {
            gv->setVertexIcon(node->getParserID(), "../imgs/walking.png");
            continue;
        }
        
        switch (node->edgePath->getType()) {
            case Transport::FOOT:
            case Transport::ACCESS:
                gv->setVertexIcon(node->getParserID(), "../imgs/walking.png");
                break;
            case Transport::BUS:
                gv->setVertexIcon(node->edgePath->getOrigin()->getParserID(), "../imgs/stcp.png");
                gv->setVertexIcon(node->getParserID(), "../imgs/stcp.png");
                break;
            case Transport::SUBWAY:
                gv->setVertexIcon(node->edgePath->getOrigin()->getParserID(), "../imgs/metro.png");
                gv->setVertexIcon(node->getParserID(), "../imgs/metro.png");
                break;
        }
        
    }
    
    gv->rearrange();
    
    return gv;
}

GraphViewer * widenGraphPathEdges(GraphViewer * gv, const vector<Edge *> & edges) {
    
    for (const Edge * edg : edges) {
        gv->setEdgeThickness(edg->getID(), 12);
        gv->setEdgeDashed(edg->getID(), true);
    }
    
    gv->rearrange();
    
    return gv;
}

bool askForPath(GraphViewer * gv, Graph & g) {
    int originParserID, destParserID;
    cout << "Start node: "; cin >> originParserID;
    cout << "Destination node: "; cin >> destParserID;
    
    node_id origin, dest;
    origin = g.getNodeIDFromParserID((int) originParserID);
    dest = g.getNodeIDFromParserID((int) destParserID);
    
    /* Get input from user */
    string ans;
    cout << "\n** Preferences **\n";
    cout << "Shortest, Transport, Cost\n";
    cin >> ans;
    
    if (ans == "shortest" or ans == "Shortest" or ans == "no") {
        g.dijkstraShortestPath(origin, dest);
    }
    else if (ans == "transport" or ans == "Transport") {
        cout << "\n\tType: ";
        cin >> ans;
        
        Transport::Type t = Transport::FOOT;
        unsigned preference = 10;
        
        if (ans == "walk" or ans == "foot")
            t = Transport::FOOT;
        else if (ans == "bus")
            t = Transport::BUS;
        else if (ans == "subway" or ans == "tram")
            t = Transport::SUBWAY;
        else
            cout << "\n\tUnrecognized means of transportation\n";
        
        cout << "\n\tPreference (integer): "; cin >> preference;
        
        g.dijkstraShortestPath(origin, dest, t, preference);
    }
    else if (ans == "cost" or ans == "Cost") {
        unsigned cost = 0;
        
        cout << "\n\tMaximum cost: "; cin >> cost;
        g.dijkstraShortestPathWithMaxCost(origin, dest, cost);
    }
    else {
        cout << "\nUnrecognized Option.\n";
        return false;
    }
    
    auto path = g.getPath(origin, dest);
    auto edges = g.getPathEdges(origin, dest);
    
    viewGraphPath(gv, path);
    widenGraphPathEdges(gv, edges);
    
    printPathStats(g, origin, dest);
    
    cin.get();

    return true;
}

void askExactMatch(const Graph & g) {
    cout << "\n** Exact Match **" << endl;
    cout << "Transport stop's name: ";
    string s;
    getline(cin, s);
    
    cout << "\nMatches:\n";
    auto ret = g.exactMatch(s);
    for (string s : ret)
        cout << s << endl;
    
    if (ret.empty())
        cout << "No match was found for \"" << s << "\"." << endl;}

void askApproximateMatch(const Graph & g, unsigned max_dist) {
    cout << "\n** Approximate Match **" << endl;
    cout << "Transport stop's name: ";
    string s;
    getline(cin, s);
    
    unsigned match = false;
    
    cout << "\nMatches per proximity (w/ max. distance " << max_dist << ") :\n";
    auto ret = g.approximateMatch(s);
    for (auto p : ret) {
        if (p.first > max_dist)
            break;
        cout << p.first << " -- " << p.second << endl;
        match = true;
    }
    
    if (! match)
        cout << "No match was found for \"" << s << "\"." << endl;
}

void printPathStats(const Graph & g, node_id src, node_id dest) {
    if (g.getPath(src, dest).size() <= 1) {
        cout << "No Path found between the provided nodes." << endl;
        cout << "IDs were " << src << " and " << dest << ".\n\n";
        return;
    }
    
    cout << "\n** Path Stats **\n";
    cout << "Path Length (km):        " << setprecision(4) << g.getPathLength(src, dest) << endl;
    cout << "Path Cost (cents):       " << setprecision(4) << g.getPathCost(src, dest) << endl;
    cout << "Path Duration (minutes): " << setprecision(4) << g.getPathDuration(src, dest) * 60 << endl;
}

void clearScreen() {
    system("clear");
}

/******************************************
 * Main Menu
 ******************************************/
unsigned short int menuOptions() {
    unsigned short int option;
    
    const string TAB = "   ";
    
    clearScreen();
    
    cout << "\n** Main Menu **\n";
    cout << TAB << "1 - View Graph" << endl;
    cout << TAB << "2 - Ask for path" << endl;
    cout << TAB << "3 - Exact string matching" << endl;
    cout << TAB << "4 - Approximate string matching" << endl;
    cout << TAB << "5 - Exit program" << endl << endl;
    string msg = TAB; msg += "Your option: ";
    
    string trail;
    do {
        if (cin.fail())
            cin.clear();
        cout << TAB << "-> ";
        cin >> option;
        getline(cin, trail);
    } while (cin.fail() || (option < 1 && option > 5));
    
    cout << endl << endl;
    
    if (option == 5) {
        cout << TAB << "Exiting program..." << endl;
        return false;
    }
    
    return option;
}

void mainMenu(Graph & g) {
    unsigned int option;
    GraphViewer * gv = nullptr;
    
    while ((option = menuOptions())) {
        switch (option) {
            case 1:
                viewGraphComplete(g);
                break;
            case 2:
                if (gv == nullptr)
                    gv = viewGraphComplete(g);
                askForPath(gv, g);
                break;
            case 3:
                askExactMatch(g);
                break;
            case 4:
                askApproximateMatch(g, 3);
                break;
        }
        
        cout << "\n\tPress ENTER to continue...";
        string trail;
        getline(cin, trail);
    }
    
}

