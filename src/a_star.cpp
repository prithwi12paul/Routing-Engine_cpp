// Purpose: A* algorithm implementation to find the shortest path between two points on the map (road network graph). The 2 points are
// in terms of latitude and longtitude which is of struct type Graph Node. The edges are of struct type Graph Edge. The graph is stored as an unordered map and considered undirected.

#include"a_star.h"
#include<iostream>
#include<cmath>
#include<vector>
#include<array>
#include<queue>
#include<unordered_set>
using namespace std;


AStarNode::AStarNode(long long int id, double lat, double lon) : node(id, lat, lon), g_val(INFINITY), h_val(0) {}

AStar::AStar(long long int id, double lat, double lon, float &epsilon_val, vector<Graph_Node> graph_nodes, unordered_map<long long int, Graph_Node> node_map, vector<Graph_Edge> graph_edges)
: AStarNode(id, lat, lon), graph_nodes(graph_nodes), node_map(node_map), graph_edges(graph_edges), max_iters(10000) 
{
    float epsilon = epsilon_val;
    create_roadmap_graph();
}

 double AStar::stage_cost(AStarNode* node_1, AStarNode* node_2)
    {
        double lat_1 = node_1->node.lat;
        double lon_1 = node_1->node.lon;
        double lat_2 = node_2->node.lat;
        double lon_2 = node_2->node.lon;
        return calculateDistance(lat_1, lon_1, lat_2, lon_2);
    }
double AStar::heuristic(AStarNode* node_1, AStarNode* node_2)
    {
        return stage_cost(node_1, node_2);
    }


    


    // Graph is already created and stored in an unordered map called create_graph

    // need to write a function to get acces of the children of a node from the graph

    

    void AStar::create_roadmap_graph()
    {
        unordered_map<long long int, vector<long long int>> graph_map = create_Graph(graph_nodes, node_map, graph_edges);
        cout << "Graph created successfully" << endl;
        this->road_network_graph = graph_map;
    }
       

    

    vector<Graph_Node> AStar::route(const Graph_Node& start, const Graph_Node& goal)
    {
        // Define the OPEN Set and the CLOSED set
        // OPEN set is a priority queue/ dictionary that maps the nodes to their f values
        // CLOSED set is an unordered set
        cout<<"Planning the shortest route from start node to goal node"<<endl;

        priority_queue<pair<AStarNode*,double>, vector<pair<AStarNode*,double>>, greater<pair<AStarNode*,double>>> OPEN;

        unordered_set<AStarNode*> CLOSED;

        AStarNode* start_node = new AStarNode(start.id, start.lat, start.lon);
        AStarNode* goal_node = new AStarNode(goal.id, goal.lat, goal.lon);
        start_node->g_val = 0.0;
        start_node->h_val = heuristic(start_node, goal_node);
        cout<<"The h value of the start node is: "<<start_node->h_val<<endl;
        goal_node->h_val = heuristic(goal_node, goal_node);

        cout<<"The f value of the start node is: "<<start_node->g_val + start_node->h_val<<endl;

        OPEN.push(make_pair(start_node, start_node->g_val + start_node->h_val));

        int iter = 0;

        AStarNode* current_node = nullptr;

        cout<< "Starting to plan...."<<endl;

        while (CLOSED.find(goal_node) == CLOSED.end() && !OPEN.empty() && iter <= max_iters)
    
        {   
            cout<<"Iteration: "<<iter<<endl;
            cout<<"OPEN size: "<<OPEN.size()<<endl;
            cout<<"CLOSED set initial size : "<<CLOSED.size()<<endl;
            iter++;
            current_node = OPEN.top().first;
            double current_node_f_val = OPEN.top().second;
            OPEN.pop();
            cout <<" The size of OPEN after popping the min f value node is: "<<OPEN.size()<<endl;
            CLOSED.insert(current_node);
            cout<<"CLOSED set size after inserting the min f value node from OPEN set: "<<CLOSED.size()<<endl;

            // get the distance of the current node to the goal node
            double current_node_to_goal_node_distance = heuristic(current_node, goal_node);

            cout<< "The distance of current node to goal node is: "<<current_node_to_goal_node_distance<<endl;

            if (current_node_to_goal_node_distance <= 1)
            {
                cout << "Goal node reached" << endl;
                cout<<"The current_node is: "<<current_node->node.id<<endl;
                cout<< (current_node != nullptr)<<endl;
                break;
            }

            // get the children of the current node
            vector<long long int> children_nodes = this->road_network_graph[current_node->node.id];

            for (const auto& child_node_id : children_nodes)
            {

                // find the node with the same child node id in the CLOSED set
                for (const auto& closed_node : CLOSED)
                {
                    if (closed_node->node.id == child_node_id)
                    {
                        continue;
                    }
                }

                // find the node with the same child node id in the OPEN set
                // cant use range based for loop for priority queue

                bool nodeFound = false;
                vector<pair<AStarNode*,double>> temp_storage;

                while (!OPEN.empty())
                {
                    AStarNode* temp_node = OPEN.top().first;
                    OPEN.pop();

                    if (temp_node->node.id == child_node_id)
                    // if the node is already found in the OPEN set
                    {
                        cout<<"Child Node" << child_node_id<<" already present in OPEN set"<<endl;
                        if (temp_node->g_val > current_node->g_val + stage_cost(current_node, temp_node))
                        {
                            temp_node->g_val = current_node->g_val + stage_cost(current_node, temp_node);
                            temp_node->parent_node.insert(current_node);
                            double temp_node_f_val = temp_node->g_val + temp_node->h_val;
                            temp_storage.push_back(make_pair(temp_node, temp_node_f_val));
                            nodeFound = true;
                            break;
                        }
                        else
                        {
                            temp_storage.push_back(make_pair(temp_node, temp_node->g_val + temp_node->h_val));
                        }
                        
                    }
                }

                if (!nodeFound)
                {
                    cout<< "Child Node" << child_node_id<<" not present in OPEN set"<<endl;
                    cout<<"Creating a new node for the child node"<<endl;
                    AStarNode* child_node = new AStarNode(node_map[child_node_id].id, node_map[child_node_id].lat, node_map[child_node_id].lon);
                    child_node->g_val = current_node->g_val + stage_cost(current_node, child_node);
                    child_node->h_val = heuristic(child_node, goal_node);
                    child_node->parent_node.insert(current_node);
                    double child_node_f_val = child_node->g_val + child_node->h_val;
                    temp_storage.push_back(make_pair(child_node, child_node_f_val));
                }

                // Re-insert the temporarily removed nodes back into OPEN set
                for (const auto& temp_node : temp_storage)
                {
                    OPEN.push(temp_node);
                }

            }

        }

        // get the shortest path
        vector<Graph_Node> shortest_path;
        //  retrace the path from the current_node to the start_node
        cout<<(current_node!=nullptr)<<endl;

        if (current_node != nullptr)
        {
            cout << " Shortest Path found" << endl;
            while (current_node != nullptr)
            {   
                shortest_path.push_back(node_map[current_node->node.id]);
                cout<<(!current_node->parent_node.empty())<<endl;
                if (!current_node->parent_node.empty()) 
                {
                    cout << "The parent node of current node is: " << (*(current_node->parent_node.begin()))->node.id << endl;
                    current_node = *(current_node->parent_node.begin());
                }
                else
                {
                    current_node = nullptr;
                }
            }
        }
        else
        {
            cout << "No path found" << endl;
        }

        vector<Graph_Node> shortest_path_reversed(shortest_path.rbegin(), shortest_path.rend());

        return shortest_path_reversed;
    }


// int main()
// {
//     string xml_file = "../../maps/map_1.osm";
//     float epsilon_val = 1.0;
//     long long int start_node_id = 373537073;
//     long long int goal_node_id = 2001978491;
//     vector<Graph_Node> graph_nodes = process_nodes(xml_file);
//     cout << "Nodes processed successfully" << endl;
//     // create node map
//     unordered_map<long long int, Graph_Node> node_map = create_node_map(graph_nodes);
//     cout << "Node map created successfully" << endl;
//     // create edges
//     vector<Graph_Edge> graph_edges = process_ways(xml_file, node_map);
//     cout << "Edges processed successfully" << endl;
    
//     AStar astar(start_node_id, node_map[start_node_id].lat, node_map[start_node_id].lon, epsilon_val, graph_nodes, node_map, graph_edges);
//     // plan the shortest route from start node to goal node
//     vector<Graph_Node> shortest_path = astar.route(node_map[start_node_id], node_map[goal_node_id]);
//     cout << "Shortest path planned successfully" << endl;
//     // print the shortest path
//     for (const auto& node : shortest_path)
//     {
//         cout << node.id << " ";

//     }
// }





