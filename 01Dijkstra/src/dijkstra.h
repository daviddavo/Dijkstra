#pragma once

#include "boost/graph/adjacency_list.hpp"

// https://www.boost.org/doc/libs/1_72_0/libs/graph/doc/using_adjacency_list.html
namespace dijkstra {
    typedef boost::adjacency_list<
        boost::vecS, // OutEdgeList (vecS -> std::vector
        boost::vecS, // VertexList
        boost::directedS, // Directed graph, but not bidirectional
        boost::no_property, // Vertex properties
        boost::property<boost::edge_weight_t, int>, // Edge properties, distance to node
        boost::no_property // Graph Properties
    > Graph;

    void hw();

    typedef boost::graph_traits<Graph>::vertex_descriptor vertex_descriptor;

    void dijkstra_shortest(
            dijkstra::Graph & g, // The graph to explore
            dijkstra::vertex_descriptor start // Starting point
        );
}
