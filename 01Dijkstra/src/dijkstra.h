#pragma once
#include <vector>
#include "skewheap.h"

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
struct Vertex {
    vertex_descriptor vd;
    std::string label;
    std::vector<Edge<W>> edges;
    Vertex (vertex_descriptor vd, std::string label) : vd(vd), label(label) {}
};

void hw() {
    printf("Hello World\n");
}

template <class W> using Graph = std::vector<Vertex<W>>;

/*
 *FUNCTION DECLARATIONS
 */

template <class W>
vertex_descriptor add_vertex(Graph<W> & g, std::string label) {   
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

template <class W>
std::vector<std::pair<W, vertex_descriptor>> dijkstra(const Graph<W> & g, const Vertex<W> & source) {
    return dijkstra(g, source.vd);
}

template <class W>
std::vector<std::pair<W, vertex_descriptor>> dijkstra(const Graph<W> & g, vertex_descriptor vd) {
    if (vd == 0) throw std::range_error("vertex can't be 0 (NULL)");
    std::vector<W> distances(g.size());
    std::vector<vertex_descriptor> path(g.size());

    SkewHeap<W, vertex_descriptor> pq;
    using SHNode = typename SkewHeap<W, vertex_descriptor>::Node;
    std::vector<SHNode *> nodes(g.size());

    // First we populate the path, distances, nodes, etc table
    // O(V)
    for (vertex_descriptor i = 1; i < g.size(); ++i) {
        if (i == vd) distances[i] = 0;
        else distances[i] = std::numeric_limits<W>::max();

        path[i] = 0;
        nodes[i] = pq.insert(distances[i], i);
    }

    // Now we do the algoritm
    vertex_descriptor currentV;
    while(!pq.empty()) {
        assert(pq.getMin()->getKey() == distances[pq.getMin()->getVal()]);
        currentV = pq.getMin()->getVal();
        pq.deleteMin(); // <-- Here

        for (Edge<W> e : g[currentV].edges) {
            assert(e.from == currentV);
            W tmpdst;

            tmpdst = distances[currentV] + e.weight;
            if (tmpdst < distances[e.to]) {
                distances[e.to] = tmpdst;
                path[e.to] = currentV;
                /* We need to save the pointer to that node */
                // pq.decreaseKey(currentN, tmpdst);
                pq.decreaseKey(nodes[e.to], tmpdst);
            }
        }
    }

    // And now to put it in vector format
    // O(V)
    std::vector<std::pair<W, vertex_descriptor>> ret(g.size());
    ret[0] = std::pair<W, vertex_descriptor>(std::numeric_limits<W>::max(), 0); // We put the null node
    for(vertex_descriptor i = 1; i < g.size(); ++i) {
        ret[i] = std::pair<W, vertex_descriptor>(distances[i], path[i]);
    }

    return ret;
}
