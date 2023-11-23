#ifndef BUILD_GRAPH_H
#define BUILD_GRAPH_H

const double M_PI = 3.14159265358979323846;

#include <tinyxml2.h>
#include<vector>
#include<fstream>
#include<sstream>
#include<cmath>
#include<math.h>
#include<algorithm>
#include<unordered_map>
using namespace std;

struct Graph_Node {
    long long int id;
    double lat;
    double lon;

    Graph_Node() : id(0), lat(0.0), lon(0.0) {}  // default constructor

    Graph_Node(long long int id, double lat, double lon) : id(id), lat(lat), lon(lon) {}
};

struct Graph_Edge {
    Graph_Node start_node;
    Graph_Node end_node;
    double distance;

    Graph_Edge(Graph_Node start_node, Graph_Node end_node, double distance) 
    : start_node(start_node),end_node(end_node),distance(distance) {}
};

bool isRoadway(const tinyxml2::XMLElement *way);

double calculateDistance(double lat1, double lon1, double lat2, double lon2);

vector<Graph_Node> process_nodes(const string &xml_file);

unordered_map<long long int, Graph_Node> create_node_map(const vector<Graph_Node>& graph_nodes);

vector<Graph_Edge> process_ways(const string &xml_file, unordered_map<long long int, Graph_Node>& node_map);

unordered_map<long long int, vector<long long int>> create_Graph(const vector<Graph_Node> &graph_nodes,
                                                       const unordered_map<long long int, Graph_Node> &node_map,
                                                       const vector<Graph_Edge> &graph_edges);


#endif