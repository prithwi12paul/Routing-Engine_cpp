#include "a_star.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>

int main() {
    // Specify the file path relative to the executable's location
    std::string xml_file = "../../maps/map_1.osm"; 
    float epsilon_val = 1.0;

    // Define start and goal node IDs
    long long int start_node_id = 6135937005;
    long long int goal_node_id = 2001978491;
    // long long long int start_node_id = 65435128;
    // long long long int goal_node_id = 2147483647;

    // Process nodes and ways from XML
    std::vector<Graph_Node> graph_nodes = process_nodes(xml_file);
    std::unordered_map<long long int, Graph_Node> node_map = create_node_map(graph_nodes);
    std::vector<Graph_Edge> graph_edges = process_ways(xml_file, node_map);

    // Initialize AStar algorithm and find the shortest path
    AStar astar(start_node_id, node_map[start_node_id].lat, node_map[start_node_id].lon, epsilon_val, graph_nodes, node_map, graph_edges);
    std::vector<Graph_Node> shortest_path = astar.route(node_map[start_node_id], node_map[goal_node_id]);

    // store the coordinates of the nodes to create a geojson file
    
    std::ofstream geojson_file;
    geojson_file.open("map_1_geojson_file.geojson");
    geojson_file << std::fixed << std::setprecision(7);
    geojson_file << "{\n";
    geojson_file << "\"type\": \"FeatureCollection\",\n";
    geojson_file << "\"features\": [\n";
    geojson_file << "{\n";
    geojson_file << "\"type\": \"Feature\",\n";
    geojson_file << "\"properties\": {},\n";
    geojson_file << "\"geometry\": {\n";
    geojson_file << "\"type\": \"LineString\",\n";
    geojson_file << "\"coordinates\": [\n";
    for (const auto& node : shortest_path) {
        geojson_file << "[" << node.lon << "," << node.lat << "],\n";
    }
    geojson_file << "]\n";
    geojson_file << "}\n";
    geojson_file << "}\n";
    geojson_file << "]\n";
    geojson_file << "}\n";
    geojson_file.close();


    

    // Output the shortest path
    std::cout << "Shortest path:" << std::endl;
    for (const auto& node : shortest_path) {
        std::cout << "Node ID: " << node.id << std::endl;
    }

    return 0;
}
