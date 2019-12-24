#include <unordered_map>
#include "dijkstra.h"
#include "skewheap.h"
using namespace std;

template <class L, class W>
vector<pair<W, LabeledVertex<L>>> dijkstra(LabeledWeightedGraph<L,W> g, Vertex & start) {
	unordered_map<L, W> distances;
	unordered_map<L, LabeledVertex<L> *> path;
	SkewHeap<W, LabeledVertex<L> *> pq;

	// First we create the distances and paths lists. These are hashmaps so
	// access time should be O(1)
	for (auto & v : g._adjList) {
		if (v == start) distances[v._label] = 0;
		else distances[v._label] = numeric_limits<W>::max;

		path[v._label] = nullptr;
	}

    auto * act;
    while (!pq.empty()) {
        act = pq.getMin();

        pq.delete(); 

        pq.deleteMin();
    }
}
