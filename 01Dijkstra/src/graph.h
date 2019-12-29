#pragma once
#include <vector>
#include <cassert>

/** Type declarations */

typedef unsigned edge_descriptor;
typedef unsigned vertex_descriptor;

template <class W> 
struct Edge {
    edge_descriptor ed;
    vertex_descriptor to;
    vertex_descriptor from;
    W weight;
    Edge (edge_descriptor ed, vertex_descriptor from, vertex_descriptor to, W weight = 1) :
        ed(ed), to(to), from(from), weight(weight) {}
};

template <class W>
inline bool operator== (const Edge<W> & e1, const Edge<W> & e2) {
    return e1.ed == e2.ed && e1.to == e2.to && e1.from == e2.from && e1.weight == e2.weight;
}

template <class W>
struct Vertex {
    vertex_descriptor vd;
    std::string label;
    std::vector<Edge<W>> edges;
    Vertex (vertex_descriptor vd, std::string label) : vd(vd), label(label) {}
};

template <class W>
inline bool operator==(const Vertex<W> & v1, const Vertex<W> & v2) {
    return v1.vd == v2.vd && v1.edges == v2.edges;
}

/** COMPARING TWO GRAPHS DOESN'T TELL YOU IF THEY ARE ISOMORPHS **/
template <class W> using Graph = std::vector<Vertex<W>>;

/*
 *FUNCTION DECLARATIONS
 */
template <class W>
vertex_descriptor add_vertex(Graph<W> & g, std::string label = "") {   
    if (g.size() == 0) g.push_back(Vertex<W>(0, "null"));
    g.push_back(Vertex<W>(g.size(), label));
    return g.size() - 1;
}

template <class W>
edge_descriptor add_edge(Vertex<W> & from, const Vertex<W> & to, W weight = 1) {
    if (from.vd == 0 || to.vd == 0) throw std::range_error("Can't connect to null");
    auto & edges = from.edges;
    edges.push_back(Edge<W>(edges.size(), from.vd, to.vd, weight));
    return edges.size() - 1;
}

template <class W>
edge_descriptor add_edge(Graph<W> & g, vertex_descriptor from, vertex_descriptor to, W weight = 1) {
    assert(g[from].vd == from && g[to].vd == to);
    return add_edge(g[from], g[to], weight);
}

