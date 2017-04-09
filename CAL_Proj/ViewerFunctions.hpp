//
//  ViewerFunctions.hpp
//  CAL_Proj
//
//  Created by Andre Cruz on 06/04/2017.
//  Copyright Â© 2017 Andre Cruz. All rights reserved.
//

#ifndef ViewerFunctions_hpp
#define ViewerFunctions_hpp

#include <vector>
#include "Graph.hpp"
#include "graphviewer.h"

/**
 * Function used to display an entire Graph on the screen.
 * In this case, the visual representation of the map will be similar to a geographic map.
 * All the Edges in Red are Subway routes.
 * All the Edges in blue are Bus routes.
 * All the Edges in black are Walking routes.
 * All the yellow circles represent Nodes.
 *
 * @param g Graph to be interpreted.
 *
 * @return GraphViewer containing data regarding the given Graph.
 */
GraphViewer * viewGraphComplete(Graph & g);

/**
 * Function used to update the GraphViewer with the path optimized path for the User.
 * Red circles represent the path the User should be taking according to his needs.
 *
 * @param gv GraphViewer to be updated.
 * @param path Optimal path for the User.
 *
 * @return GraphViewer containing the updated data.
 */
GraphViewer * viewGraphPath(GraphViewer * gv, const vector<Node *> & path);

/**
 * Function used to update the GraphViewer, by thickening the Edges used in the User's path.
 *
 * @param gv GraphViewer to be updated.
 * @param edges Edges was visual representation will be updated.
 *
 * @return GraphViewer containing the updated data.
 */
GraphViewer * widenGraphPathEdges(GraphViewer * gv, const vector<Edge *> & edges);

/**
 * Function used to calculated the User's Path given a certain Graph.´
 * This function calls function viewGraphPath, so that the visual representation of the Graph is also updated with the User's path.
 *
 * @param gv GraphViewer to be updated.
 * @param g Graph used on the User's path calculation
 *
 * @return GraphViewer containing the updated data.
 */
GraphViewer * askForPath(GraphViewer * gv, Graph & g);

/**
 * Getter for Path Length.
 *
 * @param path Vector of Nodes, representing the User's path, from where length is calculated.
 *
 * @return The path length value.
 */
float getPathLength(const vector<Node *> & path);

/**
 * Getter for Path Length.
 *
 * @param edges Vector of edges, representing the User's path, from where length is calculated.
 *
 * @return The path length value.
 */
float getPathLength(const vector<Edge *> & edges);

/**
 * Getter for Path duration.
 * Duration is in Hours.
 *
 * @param edges Vector of edges, representing the User's path, from where duration is calculated.
 *
 * @return The path duration value, in hours.
 */
float getPathDuration(const vector<Edge *> & edges);

/**
 * Getter for Path cost.
 * Cost is in Cents.
 *
 * @param edges Vector of edges, representing the User's path, from where cost is calculated.
 *
 * @return The path cost value, in cents.
 */
unsigned getPathCost(const vector<Edge *> & edges);

/**
 * User's Path Parser.
 * Instead of representing the User's path with a vector of Edges, represents the path with a vector of Nodes.
 *
 * @param edges Vector of edges, representing the User's path, that will be parsed.
 *
 * @return The User's path, now represented in a vector of Nodes.
 */
vector<Node*> getPathFromEdges(const vector<Edge *> & edges);

/**
 * Function used to display on the screen the Statistics from the User's Path.
 * The statistics are: the path length, the path duration and the path cost.
 *
 * @param edges Vector of edges, representing the User's path.
 */
void printPathStats(const vector<Edge *> & edges);

#endif /* ViewerFunctions_hpp */
