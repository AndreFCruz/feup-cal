//
//  ViewerFunctions.cpp
//  CAL_Proj
//
//  Created by Andre Cruz on 06/04/2017.
//  Copyright © 2017 Andre Cruz. All rights reserved.
//

#include <iostream>
#include <iomanip>
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
        gv->setVertexSize(node->getParserID(), 80);

        if (node->edgePath == nullptr) {
            gv->setVertexIcon(node->getParserID(), "./images/walking.png");
            continue;
        }
        
        switch (node->edgePath->getType()) {
            case Transport::FOOT:
                gv->setVertexIcon(node->getParserID(), "./images/walking.png");
                break;
            case Transport::BUS:
                gv->setVertexIcon(node->edgePath->getOrigin()->getParserID(), "./images/stcp.png");
                gv->setVertexIcon(node->getParserID(), "./images/stcp.png");
                break;
            case Transport::SUBWAY:
                gv->setVertexIcon(node->edgePath->getOrigin()->getParserID(), "./images/metro.png");
                gv->setVertexIcon(node->getParserID(), "./images/metro.png");
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

    return true;
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


