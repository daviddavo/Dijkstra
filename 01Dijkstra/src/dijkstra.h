#pragma once
#include "skewheap.h"
#include "graph.h"

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
