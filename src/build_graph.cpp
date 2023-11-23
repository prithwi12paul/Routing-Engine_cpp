#include"build_graph.h"
#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

bool isRoadway(const tinyxml2::XMLElement *way) {
    const tinyxml2::XMLElement *tag = way->FirstChildElement("tag");
    while (tag != nullptr) {
        if (strcmp(tag->Attribute("k"), "highway") == 0) {
            return true;
        }
        tag = tag->NextSiblingElement("tag");
    }
    return false;
}

// Constants
const double a = 6378137;      // Semi-major axis (meters)
const double b = 6356752.314245; // Semi-minor axis (meters)
const double f = 1 / 298.257223563; // Flattening
const double pi = 3.141592653589793;

// Convert degrees to radians
double deg2rad(double degrees) {
    return degrees * (pi / 180.0);
}

// // Vincenty Formula
// double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
//     lat1 = deg2rad(lat1);
//     lon1 = deg2rad(lon1);
//     lat2 = deg2rad(lat2);
//     lon2 = deg2rad(lon2);

//     double U1 = atan((1 - f) * tan(lat1));
//     double U2 = atan((1 - f) * tan(lat2));
//     double L = lon2 - lon1;
//     double Lambda = L;
//     double sinSigma, cosSigma, sigma, sinAlpha, cos2SigmaM, C;
//     double Lambda_prev;
//     int iterLimit = 100;

//     do {
//         double sinLambda = sin(Lambda);
//         double cosLambda = cos(Lambda);
//         sinSigma = sqrt((cos(U2) * sinLambda) * (cos(U2) * sinLambda) + 
//                         (cos(U1) * sin(U2) - sin(U1) * cos(U2) * cosLambda) * 
//                         (cos(U1) * sin(U2) - sin(U1) * cos(U2) * cosLambda));
//         if (sinSigma == 0) return 0; // co-incident points

//         cosSigma = sin(U1) * sin(U2) + cos(U1) * cos(U2) * cosLambda;
//         sigma = atan2(sinSigma, cosSigma);
//         sinAlpha = cos(U1) * cos(U2) * sinLambda / sinSigma;
//         cos2SigmaM = cosSigma - 2 * sin(U1) * sin(U2) / (sinAlpha * sinAlpha);
//         C = f / 16 * (sinAlpha * sinAlpha) * (4 + f * (4 - 3 * (sinAlpha * sinAlpha)));
//         Lambda_prev = Lambda;
//         Lambda = L + (1 - C) * f * sinAlpha * 
//                  (sigma + C * sinSigma * (cos2SigmaM + C * cosSigma * 
//                  (-1 + 2 * cos2SigmaM * cos2SigmaM)));

//     } while (abs(Lambda - Lambda_prev) > 1e-12 && --iterLimit > 0);

//     if (iterLimit == 0) return -1; // formula failed to converge

//     double uSq = cos2SigmaM * (a * a - b * b) / (b * b);
//     double A = 1 + uSq / 16384 * (4096 + uSq * (-768 + uSq * (320 - 175 * uSq)));
//     double B = uSq / 1024 * (256 + uSq * (-128 + uSq * (74 - 47 * uSq)));
//     double deltaSigma = B * sinSigma * (cos2SigmaM + B / 4 * (cosSigma * 
//                      (-1 + 2 * cos2SigmaM * cos2SigmaM) - 
//                      B / 6 * cos2SigmaM * (-3 + 4 * sinSigma * sinSigma) * 
//                      (-3 + 4 * cos2SigmaM * cos2SigmaM)));

//     double s = b * A * (sigma - deltaSigma);

//     return s; // distance in meters
// }

// Function to calculate distance between two points
double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    // Constants
    const double R = 6371.0; // Radius of the Earth in km
    const double TO_RAD = M_PI / 180.0;

    // Convert latitudes and longitudes from degrees to radians
    lat1 *= TO_RAD;
    lon1 *= TO_RAD;
    lat2 *= TO_RAD;
    lon2 *= TO_RAD;

    // Haversine formula
    double dlon = lon2 - lon1;
    double dlat = lat2 - lat1;
    double a = std::pow(std::sin(dlat / 2), 2) + std::cos(lat1) * std::cos(lat2) * std::pow(std::sin(dlon / 2), 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    return R * c * 1000.0; // Distance in m
}



//  

//  process all the nodes and the ways from the xml file and create graph nodes and edges on the fly

//  store the graph nodes and edges in a vector

//  process all the nodes and store them in a vector

vector<Graph_Node> process_nodes(const string &xml_file)
{
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(xml_file.c_str()) != tinyxml2::XML_SUCCESS) {
        std::cerr << "Failed to load file" << std::endl;
        exit(1);
    }
    const tinyxml2::XMLElement *osm = doc.FirstChildElement("osm");
    const tinyxml2::XMLElement *node = osm->FirstChildElement("node");    
    vector<Graph_Node> graph_nodes;
    while (node != nullptr) 
    {
        long long int id = atoll(node->Attribute("id"));
        double lat = atof(node->Attribute("lat"));
        double lon = atof(node->Attribute("lon"));
        graph_nodes.emplace_back(id, lat, lon);
        node = node->NextSiblingElement("node");
    }
    return graph_nodes;
}

// Function to create a map for quick node lookup by ID
unordered_map<long long int, Graph_Node> create_node_map(const vector<Graph_Node>& graph_nodes) 
{
    unordered_map<long long int, Graph_Node> node_map;
    for (const Graph_Node& node : graph_nodes) {
        node_map[node.id] = node;
    }

    return node_map;
}




vector<Graph_Edge> process_ways(const string &xml_file, unordered_map<long long int, Graph_Node>& node_map)
{  
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(xml_file.c_str()) != tinyxml2::XML_SUCCESS) {
        std::cerr << "Failed to load file" << std::endl;
        exit(1);
    }
    const tinyxml2::XMLElement *osm = doc.FirstChildElement("osm");
    const tinyxml2::XMLElement *way = osm->FirstChildElement("way");


   //  process all the ways and store them in a vector
    vector<Graph_Edge> graph_edges;
    while (way != nullptr) 
    {
    if (isRoadway(way)) {
        const tinyxml2::XMLElement *nd = way->FirstChildElement("nd");
        // store the edges in each way
        while (nd != nullptr && nd->NextSiblingElement("nd") != nullptr) {
            long long int start_node_id = atoll(nd->Attribute("ref"));
            long long int end_node_id = atoll(nd->NextSiblingElement("nd")->Attribute("ref"));
            Graph_Node start_node = node_map[start_node_id];
            Graph_Node end_node = node_map[end_node_id];
            double distance = calculateDistance(start_node.lat,
                                          start_node.lon,
                                          end_node.lat,
                                          end_node.lon);
            graph_edges.emplace_back(start_node, end_node, distance);
            nd = nd->NextSiblingElement("nd");
        }
    }
    way = way->NextSiblingElement("way");
    }
    return graph_edges;
}

unordered_map<long long int, vector<long long int>> create_Graph(const vector<Graph_Node> &graph_nodes,
                                                       const unordered_map<long long int, Graph_Node> &node_map,
                                                       const vector<Graph_Edge> &graph_edges)
{

    //  now we create the graph in unordered_map
    unordered_map<long long int, vector<long long int>> graph_map;
    for (const Graph_Edge &edge : graph_edges) 
    {
        Graph_Node start_node = edge.start_node;
        Graph_Node end_node = edge.end_node;
        auto n1 = find_if(node_map.begin(), node_map.end(), [&](const auto& entry) {
        return entry.second.id == start_node.id;
        });
        auto n2 = find_if(node_map.begin(), node_map.end(), [&](const auto& entry) {
        return entry.second.id == end_node.id;
        });
        if (n1 == node_map.end() || n2 == node_map.end()) {
        std::cerr << "Error: Node not found in map" << std::endl;
        exit(1);
        }
        // prevent adding duplicate nodes
        if (std::find(graph_map[n1->first].begin(), graph_map[n1->first].end(), n2->first) == graph_map[n1->first].end()) {
            graph_map[n1->first].push_back(n2->first);
        }
        if (std::find(graph_map[n2->first].begin(), graph_map[n2->first].end(), n1->first) == graph_map[n2->first].end()) {
            graph_map[n2->first].push_back(n1->first);
        }
        
    }

    return graph_map;

}



