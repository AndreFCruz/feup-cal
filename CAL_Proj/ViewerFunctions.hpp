//
//  ViewerFunctions.hpp
//  CAL_Proj
//
//  Created by Andre Cruz on 06/04/2017.
//  Copyright © 2017 Andre Cruz. All rights reserved.
//

#ifndef ViewerFunctions_hpp
#define ViewerFunctions_hpp

#include <vector>
#include "Graph.hpp"
#include "graphviewer.h"

GraphViewer * viewGraphComplete(Graph & g);

GraphViewer * viewGraphPath(GraphViewer * gv, const vector<Node *> & path);

GraphViewer * askForPath(GraphViewer * gv, Graph & g);

float getPathLength(const vector<Node *> & path);

float getPathDuration(const vector<Edge *> & edges);

unsigned getPathCost(const vector<Edge *> & edges);

vector<Node*> getPathFromEdges(const vector<Edge *> & edges);

#endif /* ViewerFunctions_hpp */
