#ifndef ASTAR_H
#define ASTAR_H

#include "build_graph.h" // Include the Graph Definition header file
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <cmath>



using namespace std;

struct AStarNode {
    AStarNode(long long int id, double lat, double lon);
    Graph_Node node;
    double g_val =INFINITY;
    double h_val;
    unordered_set<AStarNode*> parent_node;
};

class AStar : public AStarNode {
public:
    AStar(long long int id, double lat, double lon, float &epsilon_val, vector<Graph_Node> graph_nodes, unordered_map<long long int, Graph_Node> node_map, vector<Graph_Edge> graph_edges);
    vector<Graph_Node> route(const Graph_Node& start, const Graph_Node& goal);

private:
    vector<Graph_Node> graph_nodes;
    unordered_map<long long int, Graph_Node> node_map;
    vector<Graph_Edge> graph_edges;
    unordered_map<long long int,vector<long long int>> road_network_graph;
    int max_iters = 10000;

    double stage_cost(AStarNode* node_1, AStarNode* node_2);
    double heuristic(AStarNode* node_1, AStarNode* node_2);
    void create_roadmap_graph();
};

#endif // ASTAR_H
