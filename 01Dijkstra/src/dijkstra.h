#pragma once

#include <vector>

class Vertex;

class Edge {
	Vertex * _from;
	Vertex * _to;
};

template <class W>
class WeightedEdge : Edge {
private:
	W _weight;
};

class Vertex {
	std::vector<Edge> _edges;
};

template <class L>
class LabeledVertex : Vertex {
	L _label;
};

/**
 * Graph represented using a adjacency list
 * Each Vertex can have a label, each edge can have
 * a weight
 */
template <class L, class W>
class LabeledWeightedGraph {
private:
	std::vector<LabeledVertex<L>> _adjList;
};

template <class L, class W>
std::vector<std::pair<W, LabeledVertex<L>>> dijkstra(LabeledWeightedGraph<L, W> g, Vertex & source);
