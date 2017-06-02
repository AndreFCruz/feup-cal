//
//  Graph.cpp
//
//  Created by Andre Cruz on 28/03/2017.
//

#include <set>
#include <numeric>
#include <stack>
#include <iostream>
#include <queue>
#include <list>
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <map>
#include "Graph.hpp"


Graph::Graph(istream & nodes_in, istream & edges_in, istream & roads_in, istream & subway_edges,
             istream & bus_edges, istream & transport_stops, istream & subway_nodes) {

    // Load Nodes
    while (!nodes_in.eof()) {
        Node * tmp = new Node(nodes_in);
        nodes.insert(make_pair(tmp->getID(), tmp));
        nodeIDs.insert(make_pair(tmp->getParserID(), tmp->getID()));
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

    string name;
    // Load Transport Stops
    while (! transport_stops.eof() ) {
        node_id id;
        transport_stops >> id;
        transport_stops.ignore(1, ';');
        getline(transport_stops, name);

        stops.insert(make_pair(nodes.at(id), new TransportStop(nodes.at(id), name)));
    }

    // Load Subway Nodes/Stops
    while (! subway_nodes.eof() ) {
        node_id idStop, idClosest;

        subway_nodes >> idStop;
        subway_nodes.ignore();
        subway_nodes >> idClosest;

        try {
            TransportStop * stop = stops.at(nodes.at(idStop));
            subway_stops.insert(make_pair(stop, new SubwayStop(stop, nodes.at(idClosest))));
        } catch (out_of_range & e) {
            cout << "Load sybway nodes: " << e.what() << endl;
        }
    }

    // Add access edges to SubwayStops
    for (auto pair : subway_stops) {
        TransportStop * stop = pair.first;
        Node * closest = pair.second->getClosestNode();

        if (stop != pair.second->getTransportStop()) {
            cerr << "Invalid transport stop association!\n";
            throw logic_error::exception();
        }

        this->addEdge(new Edge(closest, stop->getNode(), nullptr, Transport::ACCESS));
        this->addEdge(new Edge(stop->getNode(), closest, nullptr, Transport::FOOT));

    }

    // Load Subway Edges
    loadTransportEdges(subway_edges, Transport::SUBWAY);

    // Load Bus Edges
    loadTransportEdges(bus_edges, Transport::BUS);

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

    // Initiate Points from min/max latitude/longitude
    for (auto & n : nodes) {
        n.second->initiatePoint(Node::getLatRange(), Node::getLonRange());
    }

    // Check Graph conectivity
    if (this->isConnected())
        cerr << "Graph is connected.\n";
    else
        cerr << "Graph is NOT connected.\n";

}

Graph::Graph(const Graph & obj) {
    for (auto p : obj.nodes) {
        Node * n = p.second;
        nodes.insert(make_pair(p.first, new Node(n->getID(), n->getCoords())));
    }

    for (auto p : obj.edges) {
        Edge * edg = p.second;
        Node * origin = nodes.at(edg->getOrigin()->getID());
        Node * dest = nodes.at(edg->getDest()->getID());

        addEdge(new Edge(origin, dest, nullptr, edg->getType()));
    }
}

Graph::~Graph() {

    // Delete Nodes
    for (auto p : nodes)
        delete p.second;

    // Delete Roads
    for (auto p : roads)
        delete p.second;

    // Delete Edges
    for (auto p : edges)
        delete p.second;

    // Delete TransportStops
    for (auto p : stops)
        delete p.second;

    // Delete SubwayStops
    for (auto p : subway_stops)
        delete p.second;
}

void Graph::loadTransportEdges(istream &input, Transport::Type type) {

    string line;
    while ( getline(input, line) ) {
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

        this->addEdge(new Edge(origin, dest, nullptr, type));
        this->addEdge(new Edge(dest, origin, nullptr, type));
    }

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
        p.second->edgePath = nullptr;
        p.second->processing = false;
        p.second->dist = numeric_limits<float>::infinity();
    }

    nodesReset = true;
}

bool Graph::isConnected() {

    Graph copy(*this);

    // Simulate Undirected
    for (auto p : copy.edges) {
        Edge * edg = p.second;
        copy.addEdge(new Edge(edg->getDest(), edg->getOrigin(), nullptr));
    }

    // Find Clusters Through DFS
    auto it = copy.nodes.begin();
    vector<size_t> clusters;

    unsigned accumulated = 0;
    while ( accumulated < copy.nodes.size() && it != copy.nodes.end()) {
        Node * start = (it++)->second;

        if (start->visited)
            continue;

        vector<Node *> res;
        copy.dfs(start, res);
        clusters.push_back(res.size());
        accumulated += res.size();

    }

    cerr << "Nodes:\t\t" << accumulated << " == " << copy.nodes.size() << endl;
    cerr << "Cluster(s):\t";
    for (auto it = clusters.begin(); it != clusters.end(); ++it)
        cerr << " " << *it;
    cerr << ".\n";

    return clusters.size() <= 1;
}
unsigned Graph::minEditDistance(string word, string sentence) const {
    stringstream ss(sentence);
    string str;
    unsigned min = editDistance(word, sentence);

    while (ss >> str) {
        unsigned tmp;
        if ( (tmp = editDistance(word, str)) < min)
            min = tmp;
    }

    return min;
}

unsigned Graph::editDistance(string str1, string str2) const {
    auto min_el = [](int el1, int el2, int el3) {
        return min(min(el1, el2), el3);
    };

    int m = str1.length();
    int n = str2.length();

    // Create a table to store results of subproblems
    int dp[m+1][n+1];

    // Fill d[][] in bottom up manner
    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            // If first string is empty, only option is to
            // isnert all characters of second string
            if (i == 0)
                dp[i][j] = j;  // Min. operations = j

            // If second string is empty, only option is to
            // remove all characters of second string
            else if (j == 0)
                dp[i][j] = i; // Min. operations = i

            // If last characters are same, ignore last char
            // and recur for remaining string
            else if (str1[i-1] == str2[j-1])
                dp[i][j] = dp[i-1][j-1];

            // If last characters are different, consider all
            // possibilities and find minimum
            else
                dp[i][j] = 1 + min_el(dp[i][j-1],   // Insert
                                      dp[i-1][j],   // Remove
                                      dp[i-1][j-1]); // Replace
        }
    }

    return dp[m][n];
}

void Graph::preKMP(string pattern, int f[]) const
{
    int m = pattern.length(), k;
    f[0] = -1;
    for (int i = 1; i < m; i++)
    {
        k = f[i - 1];
        while (k >= 0)
        {
            if (pattern[k] == pattern[i - 1])
                break;
            else
                k = f[k];
        }
        f[i] = k + 1;
    }
}

bool Graph::KMP(string pattern, string target) const {
    int m = pattern.length();
    int n = target.length();
    int f[m];

    preKMP(pattern, f);
    int i = 0;
    int k = 0;

    while (i < n)
    {
        if (k == -1) {
            i++;
            k = 0;
        } else if (target[i] == pattern[k]) {
            i++;
            k++;
            if (k == m)
                return true;
        } else
            k = f[k];
    }

    return false;
}


TransportStop * Graph::getTransportStop(Node * node) const {
    try {
        return stops.at(node);
    } catch (out_of_range & e) {
        return nullptr;
    }
}

node_id Graph::getNodeIDFromParserID(int parserID) const {
    return nodeIDs.at(parserID);
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

void Graph::dijkstraShortestPath(node_id src_id, node_id dest_id) {
    dijkstraShortestPath(nodes.at(src_id), dest_id == 0 ? nullptr : nodes.at(dest_id));
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
                w->edgePath = edg;

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

void Graph::dijkstraShortestPath(node_id src_id, node_id dest_id, Transport::Type type, unsigned int scale) {
    dijkstraShortestPath(nodes.at(src_id), nodes.at(dest_id), type, scale);
}

void Graph::dijkstraShortestPath(Node * src, Node * destination, Transport::Type type, unsigned int scale) {
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
            unsigned int edgScale = type == edg->getType() ? scale : 1;

            Node * w = edg->getDest();

            // Shortest path to w found ?
            float combinedWeight = v->dist + edg->getWeight() / edgScale;
            if( combinedWeight < w->dist ) {

                w->dist = combinedWeight;
                w->path = v;
                w->edgePath = edg;

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

struct node_pair_greater_than {
    bool operator() (const pair<Node*, unsigned> & p1, const pair<Node*, unsigned> & p2) {
        return p1.first->dist > p2.first->dist;
    }
};


void Graph::dijkstraShortestPathWithCost(Node * src, Node * destination, unsigned cost) {
    resetNodes();

    Node * v = src;
    v->dist = 0;

    vector< pair<Node*, unsigned> > pq;
    pq.push_back(make_pair(v, 0));
    make_heap(pq.begin(), pq.end());

    nodesReset = false;

    // Order predicate in heap
/*
    auto greater_than = [=] (const pair<Node*, unsigned> & p1, const pair<Node*, unsigned> & p2) {
        if (p1.second <= cost && p2.second <= cost)
            return p1.first->dist > p2.first->dist;
        else if (p1.second < cost && p2.second > cost)
            return false;
        else if (p1.second > cost && p2.second < cost)
            return true;
        else
            return p1.first->dist > p2.first->dist;
    };
*/

    while( !pq.empty() ) {
        auto p = pq.front();
        v = p.first;
        pop_heap(pq.begin(), pq.end()); pq.pop_back();

        if (v == destination)
            break;

        for(Edge * edg : v->getEdges()) {
            Node * w = edg->getDest();

            // Edge addition exceeds maximum cost ?
            if (p.second + edg->getCost() > cost)
                continue;

            // Shortest path to w found ?
            float combinedWeight = v->dist + edg->getWeight();
            if( combinedWeight < w->dist ) {

                w->dist = combinedWeight;
                w->path = v;
                w->edgePath = edg;

                // if already in pq only update
                if(!w->processing)
                {
                    w->processing = true;
                    pq.push_back(make_pair(w, p.second + edg->getCost()));
                }

                make_heap(pq.begin(), pq.end(), node_pair_greater_than());
            }
        }
    }
}

void Graph::dijkstraShortestPathWithMaxCost(node_id src_id, node_id dest_id, unsigned maxCost) {
    Node * src = nodes.at(src_id);
    Node * dest = nodes.at(dest_id);

    unsigned cost = maxCost;

    do {
        dijkstraShortestPathWithCost(src, dest, cost--);
    } while (getPathCost(src_id, dest_id) > maxCost);

}

vector<Node *> Graph::getPath(node_id src_id, node_id dest_id) const {

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

vector<Edge *> Graph::getPathEdges(node_id src_id, node_id dest_id) const {
    Node * src = nodes.at(src_id);
    Node * node = nodes.at(dest_id);

    stack<Edge *> tmp;
    while ( node->edgePath != nullptr && node != src ) {
        Edge * edg = node->edgePath;
        tmp.push(edg);
        node = edg->getOrigin();
    }

    vector<Edge *> res; res.reserve(tmp.size());
    while (! tmp.empty()) {
        res.push_back(tmp.top()); tmp.pop();
    }

    return res;
}

float Graph::getPathLength(node_id src_id, node_id dest_id) const {
    float len = 0;
    for (const Edge * edg : getPathEdges(src_id, dest_id))
        len += edg->getLength();

    return len == 0 ? numeric_limits<float>::infinity() : len;
}

float Graph::getPathDuration(node_id src_id, node_id dest_id) const {
    float duration = 0;
    for (const Edge * edg : getPathEdges(src_id, dest_id)) {
        duration += edg->getWeight();
    }

    return duration;
}

unsigned Graph::getPathCost(node_id src_id, node_id dest_id) const {
    unsigned cost = 0;
    for (const Edge * edg : getPathEdges(src_id, dest_id))
        cost += edg->getCost();

    return cost;
}

void Graph::dfs(Node * v, vector<Node*> & res) {
    v->visited = true;
    res.push_back(v);

    auto it = v->getEdges().begin();
    auto ite = v->getEdges().end();

    for (; it != ite; it++)
        if ( (*it)->getDest()->visited == false ){
            dfs((*it)->getDest(), res);
        }

    nodesReset = false;
}

map<unsigned,string> Graph::approximateMatch(string str) const {
    map< unsigned, string > matches;
    transform(str.begin(), str.end(), str.begin(), ::tolower);

    for (auto p : stops) {
        string cmp = p.second->getName();
        transform(cmp.begin(), cmp.end(), cmp.begin(), ::tolower);
        
        matches.insert(make_pair(minEditDistance(str, cmp), p.second->getName()));
    }

    return matches;
}

vector<string> Graph::exactMatch(string str) const {
    vector<string> matches;
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    
    for (auto p : stops) {
        string cmp = p.second->getName();
    	transform(cmp.begin(), cmp.end(), cmp.begin(), ::tolower);
        
        if (KMP(str, cmp))
            matches.push_back(p.second->getName());
    }

    return matches;
}
