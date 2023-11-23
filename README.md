# OSM Routing Project

This project implements an A* routing algorithm to find the shortest path between two points on a map, using Open Street Map data.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

- CMake
- A C++ compiler (e.g., GCC, Clang, MSVC)
- Visual Studio Code (optional, but recommended for building with this guide)

### Building the Project

1. Steps to build the project

```bash
mkdir -p build
cd build
cmake ..
cmake --build . --config Debug
```




### Running Unit Tests

To run unit tests, execute the following in the `build/Debug` directory:


```bash
./Debug/osm_routing_tests
```


### Running A* Algorithm

To run the A* algorithm with the main file, execute the following in the `build/Debug` directory:

```bash
./Debug/astar_main
```


### Visualizing the Route

The project generates a GeoJSON file in the `build/Debug` folder. To visualize the route:

1. Open [geojson.io](http://geojson.io).
2. Drag and drop the GeoJSON file onto the map.


