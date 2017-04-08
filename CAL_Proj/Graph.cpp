//
//  Graph.cpp
//  CAL_GraphParser
//
//  Created by Andre Cruz on 28/03/2017.
//  Copyright © 2017 Andre Cruz. All rights reserved.
//

#include <stack>
#include <iostream>
#include <queue>
#include <list>
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include "Graph.hpp"


Graph::Graph(istream & nodes_in, istream & roads_in, istream & edges_in, istream & subway) {
    
    // Load Nodes
    while (!nodes_in.eof()) {
        Node * tmp = new Node(nodes_in);
        nodes.insert(make_pair(tmp->getID(), tmp));
    }
    
    string line;
    // Load Roads
    while ( getline(roads_in, line) ) {
        stringstream ss(line);
        Road * tmp = new Road(ss);
        roads.insert(make_pair(tmp->getID(), tmp));
    }
    
    // Load Edges
    while ( getline(edges_in, line) ) {
        unsigned long id;
        Node * origin, * dest;
        Road * road;
        stringstream ss(line);
        
        try {
            ss >> id; ss.ignore(3, ';');
            road = roads.at(id);
            ss >> id; ss.ignore(3, ';');
            origin = nodes.at(id);
            ss >> id; ss.ignore(3, ';');
            dest = nodes.at(id);
        } catch (out_of_range & e) {
            cout << e.what() << endl;
        }
        
        Edge * tmp = new Edge(origin, dest, road);
        this->addEdge(tmp);
    }
    
    // Load Subway Edges
    while ( getline(subway, line) ) {
        unsigned long id;
        Node * origin, * dest;
        stringstream ss(line);
        
        try {
            ss >> id; ss.ignore(3, ';');
            origin = nodes.at(id);
            ss >> id; ss.ignore(3, ';');
            dest = nodes.at(id);
        } catch (out_of_range & e) {
            cout << e.what() << endl;
        }
        
        this->addEdge(new Edge(origin, dest, nullptr, Transport::SUBWAY));
        this->addEdge(new Edge(dest, origin, nullptr, Transport::SUBWAY));
    }
    
    /** Graph PreProcessing **/
    // Handle Two Way Roads
    for (auto & r : roads) {
        Road * road = r.second;
        if (road->isTwoWay()) {
            auto current_edges = road->getEdges();
            for (Edge * ptr : current_edges) {
                Edge * new_edge = new Edge(ptr->getDest(), ptr->getOrigin(), ptr->getRoad());
                this->addEdge(new_edge);
            }
        }
    }
    
    // TODO
    // add edges with different types of transportation

    // Initiate Points from min/max latitude/longitude
    for (auto & n : nodes) {
        n.second->initiatePoint(Node::getLatRange(), Node::getLonRange());
    }

    // TODO
    // Check Graph conectivity; eliminate non-reachable nodes ?
    
    
//    /** TEST **/
//    
//    cout << "END NODE: " << nodes.at(4737169812)->getID() << endl;
//    cout << "END ROAD: " << roads.at(480140404)->getID() << endl;
//    
//    auto vec = vector< pair<node_id, Node*> >(nodes.begin(), nodes.end());
//    sort(vec.begin(), vec.end(), [](const pair<node_id, Node*>& p1, const pair<node_id, Node*>& p2) {
//        return p1.second->getNumEdges() > p2.second->getNumEdges();
//    });
//    
//    cout << "** test end **" << endl;
//
    
//    for (auto p : edges)
//        if (p.second->getType() == Transport::SUBWAY)
//            cout << *(p.second) << endl;
}

Graph::~Graph() {
    
    // Delete nodes
    for (auto p : nodes)
        delete p.second;
    
    // Delete roads
    for (auto p : roads)
        delete p.second;
    
    // Delete edges
    for (auto p : edges)
        delete p.second;
}

void Graph::addEdge(Edge * ptr) {
    edges.insert(make_pair(ptr->getID(), ptr));
    ptr->getOrigin()->addEdge(ptr);
    
    if (ptr->getRoad() != nullptr)
        ptr->getRoad()->addEdge(ptr);
}

void Graph::resetNodes() {
    if (nodesReset)
        return;
    
    for (auto p : nodes) {
        p.second->setVisited(false);
        p.second->path = nullptr;
        p.second->processing = false;
        p.second->dist = numeric_limits<float>::infinity();
    }
}

unordered_map<node_id, Node *> Graph::getNodes() const {
    return nodes;
}

unordered_map<edge_id, Edge *> Graph::getEdges() const {
    return edges;
}

unordered_map<road_id, Road *> Graph::getRoads() const {
    return roads;
}

unordered_map<Node *, float> Graph::dijkstraTree(node_id src_id) const {
    return dijkstraTree(nodes.at(src_id));
}

// TODO use fibonacci heap as priority queue ?
unordered_map<Node *, float> Graph::dijkstraTree(Node * src) const {
    const float INF = numeric_limits<float>::infinity();
    typedef pair<unsigned int, Node *> nPair;   // pair of weight - node
    
    // Initialize distances HashMap
    auto distances = unordered_map<Node *, float> ();
    distances.reserve(nodes.size());
    for (const auto & p : nodes)
        distances.insert(make_pair(p.second, INF));
    distances.at(src) = 0;
        
    
    priority_queue<nPair, vector<nPair>, greater<nPair> > pq;
    pq.push(make_pair(0, src));
    
    while (! pq.empty()) {
        Node * current = pq.top().second; pq.pop();
        
        for (Edge * ptr : current->getEdges()) {
            float w = ptr->getWeight();
            Node * dest = ptr->getDest();
            
            // If there's a shortest path to dest through current
            if ( distances[dest] > distances[current] + w ) {
                distances[dest] = distances[current] + w;
                pq.push(make_pair(distances[dest], dest));
            }
        }
    }
    
    return distances;
}

float Graph::dijkstra(node_id src_id, node_id dest_id) const {
    return dijkstra(nodes.at(src_id), nodes.at(dest_id));
}

float Graph::dijkstra(Node * src, Node * end_node) const {
    const float INF = numeric_limits<float>::infinity();
    typedef pair<unsigned int, Node *> nPair;   // pair of weight - node
    
    // Initialize distances HashMap
    auto distances = unordered_map<Node *, float> ();
    distances.reserve(nodes.size());
    for (const auto & p : nodes)
        distances.insert(make_pair(p.second, INF));
    distances.at(src) = 0;
    
    
    priority_queue<nPair, vector<nPair>, greater<nPair> > pq;
    pq.push(make_pair(0, src));
    
    while (! pq.empty()) {
        Node * current = pq.top().second; pq.pop();
        
        if (current == end_node)
            return distances[end_node];
        
        for (Edge * ptr : current->getEdges()) {
            float w = ptr->getWeight();
            Node * dest = ptr->getDest();
            
            // If there's a shortest path to dest through current
            if ( distances[dest] > distances[current] + w ) {
                distances[dest] = distances[current] + w;
                pq.push(make_pair(distances[dest], dest));
            }
        }
    }
    
    return INF; // node not reachable
}

unordered_map<Node*, Edge*> Graph::dijkstraEdges(node_id src_id, node_id dest_id) const {
    return dijkstraEdges(nodes.at(src_id), nodes.at(dest_id));
}

unordered_map<Node*, Edge*> Graph::dijkstraEdges(Node * src, Node * end_node) const {
    const float INF = numeric_limits<float>::infinity();
    typedef pair<unsigned int, Node *> nPair;   // pair of weight - node
    
    unordered_map<Node *, Edge*> parentEdges;
    
    // Initialize distances HashMap
    unordered_map<Node *, float> distances;
    distances.reserve(nodes.size());
    for (const auto & p : nodes)
        distances.insert(make_pair(p.second, INF));
    distances.at(src) = 0;
    
    
    priority_queue<nPair, vector<nPair>, greater<nPair> > pq;
    pq.push(make_pair(0, src));
    
    while (! pq.empty()) {
        Node * current = pq.top().second; pq.pop();
        
        if (current == end_node)
            break;
        
        for (Edge * ptr : current->getEdges()) {
            float w = ptr->getWeight();
            Node * dest = ptr->getDest();
            
            // If there's a shortest path to dest through current
            if ( distances[dest] > distances[current] + w ) {
                distances[dest] = distances[current] + w;
                pq.push(make_pair(distances[dest], dest));
                
                if (parentEdges.find(dest) == parentEdges.end())
                    parentEdges.insert(make_pair(dest, ptr));
                else
                    parentEdges[dest] = ptr;
            }
        }
    }
    
    return parentEdges;
}

void Graph::dijkstraShortestPath(node_id src_id, node_id dest_id) {
    dijkstraShortestPath(nodes[src_id], dest_id == 0 ? nullptr : nodes[dest_id]);
}

struct node_greater_than {
    bool operator()(Node * a, Node * b) const {
        return a->dist > b->dist;
    }
};

void Graph::dijkstraShortestPath(Node * src, Node * destination) {
    resetNodes();
    
    Node * v = src;
    v->dist = 0;
    
    vector< Node * > pq;
    pq.push_back(v);
    make_heap(pq.begin(), pq.end());
    
    nodesReset = false;
    
    while( !pq.empty() ) {
        v = pq.front();
        pop_heap(pq.begin(), pq.end()); pq.pop_back();
        
        if (v == destination)
            break;
        
        for(Edge * edg : v->getEdges()) {
            Node * w = edg->getDest();
            
            // Shortest path to w found ?
            if(v->dist + edg->getWeight() < w->dist ) {
                
                w->dist = v->dist + edg->getWeight();
                w->path = v;
                
                // if already in pq only update
                if(!w->processing)
                {
                    w->processing = true;
                    pq.push_back(w);
                }
                
                make_heap(pq.begin(), pq.end(), node_greater_than());
            }
        }
    }
}

vector<Node *> Graph::getPath(node_id src_id, node_id dest_id){
    
    list<Node*> buffer;
    Node * v = nodes.at(dest_id);
    Node * origin = nodes.at(src_id);
    
    buffer.push_front(v);
    while ( v->path != nullptr &&  v->path != origin) {
        v = v->path;
        buffer.push_front(v);
    }
    if( v->path != nullptr )
        buffer.push_front(v->path);
    
    
    vector<Node*> res;
    while( !buffer.empty() ) {
        res.push_back( buffer.front() );
        buffer.pop_front();
    }
    return res;
}


void Graph::printShortestPath(node_id src_id, node_id dest_id) const {
    
    unordered_map<Node*, Edge*> ret = dijkstraEdges(src_id, dest_id);
    
    if (ret.size() == 0) {
        cerr << "No Path Found" << endl;
        return;
    }
    
    Node * src = nodes.at(src_id);
    Node * dest = nodes.at(dest_id);
    
    stack<Edge *> path;
    // Trace-back Path
    for (Edge * edg = ret[dest]; edg != nullptr; edg = ret[ edg->getOrigin() ]) {
        path.push(edg);
    }
    
    cout << "Path from " << src->getID() << " to " << dest->getID() << ":\n\n";
    
    float distance = 0, weight = 0; unsigned i = 1;
    while (! path.empty()) {
        Edge * edg = path.top(); path.pop();
        
        cout << i++ << ". " << *edg << endl;
        
        distance += edg->getLength();
        weight += edg->getWeight();
    }

    cout << "\nDistance (in km): " << distance << endl;
    cout << "Weight (time in mins): " << weight * 60 << endl;
}



