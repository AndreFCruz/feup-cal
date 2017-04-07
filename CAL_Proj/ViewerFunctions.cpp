//
//  ViewerFunctions.cpp
//  CAL_Proj
//
//  Created by Andre Cruz on 06/04/2017.
//  Copyright © 2017 Andre Cruz. All rights reserved.
//

#include "Edge.hpp"
#include "Node.hpp"
#include "graphviewer.h"
#include "ViewerFunctions.hpp"

using namespace std;

void viewGraphComplete(Graph & g) {
    
    GraphViewer * gv = new GraphViewer(600, 600, false);
    
    gv->setBackground("background.jpg");
    gv->createWindow(1200, 1200);

    gv->defineVertexColor("yellow");
    gv->defineEdgeColor("black");
    gv->defineVertexSize(5);
    
    // HashMap from imcompatible long IDs to int
    unordered_map<node_id, int> nodeIDs;
    int i = 0;
    for (auto & p : g.getNodes()) {
        Node * node = p.second;
        nodeIDs.insert( pair<node_id, int> (node->getID(), i++) );
    }
    
    for (auto p : g.getNodes()) {
        Node * node = p.second;
        int id = nodeIDs.at(node->getID());

//        cout << id << ". " << node->getPoint().getX() << " . " << node->getPoint().getY() << endl;
        gv->addNode(id, node->getPoint().getX(), node->getPoint().getY());
        
    }
    
    // Add all edges
    for (auto & p : g.getEdges()) {
        Edge * edg = p.second;
        gv->addEdge(edg->getID(), nodeIDs[edg->getOrigin()->getID()], nodeIDs[edg->getDest()->getID()], EdgeType::DIRECTED);
        
        switch (edg->getType()) {
            case Transport::FOOT:
                gv->setEdgeColor(edg->getID(), "black");
                break;
            case Transport::BUS:
                gv->setEdgeColor(edg->getID(), "blue");
                break;
            case Transport::SUBWAY:
                gv->setEdgeColor(edg->getID(), "red");
                break;
        }
    }
    
    
    cout << "finished GV functions" << endl;
    gv->rearrange();
    cout << "finished GV rearrange" << endl;
    
    
    getchar();
}
