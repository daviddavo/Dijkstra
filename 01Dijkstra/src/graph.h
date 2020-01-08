#pragma once
#include <vector>
#include <stdexcept>
#include <cassert>

/** Type declarations */

// Identificador o descriptor de arista
// Es la posición de la arista en la lista de aristas de un vértice
typedef unsigned edge_descriptor;
// Identificador o descriptor de vértice
// Es la posición de un vértice en la lista de adyacencia del grafo
typedef unsigned vertex_descriptor;

// Con el descriptor de arista y el descriptor "from" podemos identificar la posición de
// la arista en la estructura del grafo, si fuese necesario.
// El descriptor "to" nos indica hacia quién se conecta la arista
template <class W> 
struct Edge {
    edge_descriptor ed;
    vertex_descriptor to;
    vertex_descriptor from;
    W weight;
    Edge (edge_descriptor ed, vertex_descriptor from, vertex_descriptor to, W weight = 1) :
        ed(ed), to(to), from(from), weight(weight) {}
};

// Usado solo en los tests, no nos sirve para saber si dos grafos son isomorfos
template <class W>
inline bool operator== (const Edge<W> & e1, const Edge<W> & e2) {
    return e1.ed == e2.ed && e1.to == e2.to && e1.from == e2.from && e1.weight == e2.weight;
}

template <class W>
struct Vertex {
    vertex_descriptor vd; // Posición del grafo en el vector que forma la lista de adyacencia
    std::string label;
    std::vector<Edge<W>> edges;
    Vertex (vertex_descriptor vd, std::string label) : vd(vd), label(label) {}
};

// No nos permite saber si dos grafos son isomorfos, solo comparar su estructura
template <class W>
inline bool operator==(const Vertex<W> & v1, const Vertex<W> & v2) {
    return v1.vd == v2.vd && v1.edges == v2.edges;
}

// Lista de adayacencia
template <class W> using Graph = std::vector<Vertex<W>>;

/*
 *FUNCTION DECLARATIONS
 */

// Añadimos un vertice al grafo g
template <class W>
vertex_descriptor add_vertex(Graph<W> & g, std::string label = "") {   
    if (g.size() == 0) g.push_back(Vertex<W>(0, "null"));
    g.push_back(Vertex<W>(g.size(), label));
    return g.size() - 1;
}

// Añadimos un número de vertices al grafo.
template <class W>
void add_vertices(Graph<W> & g, unsigned nvertices) {
    if (g.size() == 0) g.push_back(Vertex<W>(0, "null"));
    g.reserve(g.size() + nvertices);
    vertex_descriptor offset = g.size();
    for (vertex_descriptor i = 0; i < nvertices; ++i) {
        g.push_back(Vertex<W>(offset + i, "null"));
    }
}

// Añadimos una arista entre dos vértices
template <class W>
edge_descriptor add_edge(Vertex<W> & from, const Vertex<W> & to, W weight = 1) {
    if (from.vd == 0 || to.vd == 0) throw std::range_error("Can't connect to null");
    auto & edges = from.edges;
    edges.push_back(Edge<W>(edges.size(), from.vd, to.vd, weight));
    return edges.size() - 1;
}

// Añadimos una arista entre dos vértices, dado el grafo y sus dos descriptores
template <class W>
edge_descriptor add_edge(Graph<W> & g, vertex_descriptor from, vertex_descriptor to, W weight = 1) {
    assert(g[from].vd == from && g[to].vd == to);
    return add_edge(g[from], g[to], weight);
}

