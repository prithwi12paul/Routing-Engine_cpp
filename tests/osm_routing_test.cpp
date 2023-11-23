#include <gtest/gtest.h>
#include "a_star.h"
#include <iostream>
#include <vector>
#include<fstream>
#include<sstream>
#include<cmath>
#include<math.h>
#include<algorithm>
#include<unordered_map>
#include<cstdlib>
using namespace std;




// Test case for the AStar routing algorithm
TEST(OsmRouting, ShortestPathTest)
{

  string xml_file = "../../maps/map_1.osm";
vector<Graph_Node> graph_nodes = process_nodes(xml_file);
unordered_map<long long int, Graph_Node> node_map = create_node_map(graph_nodes);
vector<Graph_Edge> graph_edges = process_ways(xml_file, node_map);

  long long int start_node_id = 65435128;
  long long int end_node_id = 1440068249;
  float epsilon = 1.0;
  AStar astar(start_node_id, node_map[start_node_id].lat, node_map[start_node_id].lon, epsilon, graph_nodes, node_map, graph_edges);
  vector<Graph_Node> shortest_path = astar.route(node_map[start_node_id], node_map[end_node_id]);

  ASSERT_FALSE(shortest_path.empty());
  // since there exists a direct path from start node to end node
  ASSERT_EQ(shortest_path.size(), 2); // start and end node

}

// // Test case for invalid inputs

TEST(OsmRouting, InvalidInputs)
{

 string xml_file = "../../maps/map_1.osm";
vector<Graph_Node> graph_nodes = process_nodes(xml_file);
unordered_map<long long int, Graph_Node> node_map = create_node_map(graph_nodes);
vector<Graph_Edge> graph_edges = process_ways(xml_file, node_map);
  long long int invalid_start_node_id = 100; // doesnot exist in map
  long long int invalid_end_node_id = 200; // doesnot exist in map
  float epsilon = 1.0;
  
  AStar astar(invalid_start_node_id, node_map[invalid_start_node_id].lat, node_map[invalid_start_node_id].lon, epsilon, graph_nodes, node_map, graph_edges);
  vector<Graph_Node> shortest_path = astar.route(node_map[invalid_start_node_id], node_map[invalid_end_node_id]);

  ASSERT_TRUE(shortest_path.size()==1); // since no path exists between start and end node, only start node present in shortest pa
}

// Test for the Nodes processing from the Map


TEST(MapProcessing, ProcessNodes)
{
string xml_file = "../../maps/map_1.osm";
vector<Graph_Node> graph_nodes = process_nodes(xml_file);
unordered_map<long long int, Graph_Node> node_map = create_node_map(graph_nodes);
vector<Graph_Edge> graph_edges = process_ways(xml_file, node_map);
  ASSERT_FALSE(graph_nodes.empty()); // since there are nodes in the map
}

// Test for the Edges processing from the Map

TEST(MapProcessing, ProcessEdges)
{
  string xml_file = "../../maps/map_1.osm";
vector<Graph_Node> graph_nodes = process_nodes(xml_file);
unordered_map<long long int, Graph_Node> node_map = create_node_map(graph_nodes);
vector<Graph_Edge> graph_edges = process_ways(xml_file, node_map);
  ASSERT_FALSE(graph_edges.empty()); // since there are edges in the map
}

// Test for the RoadNetwork garph creation from the Map

TEST(MapProcessing, CheckGraph)
{
  string xml_file = "../../maps/map_1.osm";
vector<Graph_Node> graph_nodes = process_nodes(xml_file);
unordered_map<long long int, Graph_Node> node_map = create_node_map(graph_nodes);
vector<Graph_Edge> graph_edges = process_ways(xml_file, node_map);
unordered_map<long long int, vector<long long int>> graph_map = create_Graph(graph_nodes, node_map, graph_edges);
ASSERT_FALSE(graph_map.empty()); // since there are nodes in the map
}

// TEST(OsmRouting, CalculateDistanceLatitudeChange) {
//     double lat1 = 0.0, lon1 = 0.0; // Coordinates of Point 1
//     double lat2 = 10.0, lon2 = 0.0; // Coordinates of Point 2
//     double expected_distance = 1111.95 * 1000.0; // Expected distance in meters
//     double error_margin = 5.0; // Margin of error in meters

//     double distance = calculateDistance(lat1, lon1, lat2, lon2);
//     ASSERT_NEAR(expected_distance, distance, error_margin);
// }

// TEST(OsmRouting, CalculateDistanceLongitudeChange) {
//     double lat1 = 0.0, lon1 = 0.0; // Coordinates of Point 1
//     double lat2 = 0.0, lon2 = 10.0; // Coordinates of Point 2
//     double expected_distance = 1113.20 * 1000.0; // Expected distance in meters, adjusted for longitude
//     double error_margin = 50; // Margin of error in meters

//     double distance = calculateDistance(lat1, lon1, lat2, lon2);
//     ASSERT_NEAR(expected_distance, distance, error_margin);
// }

// TEST(OsmRouting, CalculateDistanceDiagonal) {
//     double lat1 = 0.0, lon1 = 0.0; // Coordinates of Point 1
//     double lat2 = 10.0, lon2 = 10.0; // Coordinates of Point 2
//     double expected_distance = 1568.5 * 1000.0; // Expected distance in meters, adjusted for longitude
//     double error_margin = 50; // Margin of error in meters

//     double distance = calculateDistance(lat1, lon1, lat2, lon2);
//     ASSERT_NEAR(expected_distance, distance, error_margin);
// }


int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS(); 
}