#include "boost/property_map/property_map.hpp"
#include "dijkstra.h"
#include "skewheap.h"

using namespace std;
using namespace boost;
using namespace dijkstra;

void dijkstra::hw() {
    printf("hw\n");
}


// Exterior properties from 
// https://www.boost.org/doc/libs/1_72_0/libs/graph/doc/using_property_maps.html
// std::unordered_map<vertex_descriptor, pair<int, vertex_descriptor>> dijkstra_shortest(
namespace dijkstra {
    void dijkstra_shortest(
            const dijkstra::Graph & g, dijkstra::vertex_descriptor start) {
        fprintf(stdout, "Hi\n");
        // return std::unordered_map<vertex_descriptor, pair<int, vertex_descriptor>>();
    }
}

/*
template <class L, class W>
vector<pair<LabeledVertex<L> *, W>> dijkstra(LabeledWeightedGraph<L,W> g, Vertex * start) {
	unordered_map<LabeledVertex<L> *, W> distances;
	unordered_map<LabeledVertex<L> *, LabeledVertex<L> *> path;
	SkewHeap<W, LabeledVertex<L> *> pq;

	// First we create the distances and paths lists. These are hashmaps so
	// access time should be O(1)
	for (auto v : g._adjList) {
		if (v == start) distances[v->_label] = 0;
		else distances[v->_label] = numeric_limits<W>::max;

		path[v->_label] = nullptr;
        pq.insert(distances[v->_label], v);
	}

    auto * act;
    while (!pq.empty()) {
        act = pq.getMin();

        for(auto e : act.edges->_edges) {
            W tmpdst;

            tmpdst = distances[act] + e->_weight;
            if (tmpdst < distances[e->_to]) {
                distances[e->_to] = tmpdst;
                path[e->_to] = act;
                pq.decreaseKey(e->_to, tmpdst);
            }
        }

        pq.deleteMin();
    }

    // Ahora convertirlo todo a un vector de pares
}
*/
