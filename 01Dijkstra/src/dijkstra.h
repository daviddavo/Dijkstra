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

    // Primero poblamos la tabla de distancias (con 0 si es la fuente y infinito en caso contrario
    // También rellenamos la tabla de caminos (el antecesor será indeterminado al comenzar -> vértice nulo)
    // Y la tabla de referencias a los nodos para evitar la búsqueda
    // Como insertar en el montículo tiene un coste de O(logn) este bucle tendrá un coste de O(nlogn)
    for (vertex_descriptor i = 1; i < g.size(); ++i) {
    	distances[i] = (i==vd)?0:std::numeric_limits<W>::max();

        path[i] = 0;
        nodes[i] = pq.insert(distances[i], i);
    }

    // Realizamos el algoritmo de Dijkstra
    while(!pq.empty()) {
    	vertex_descriptor currentV = pq.getMin()->getVal();
    	// No hay implementado un método "pop", por lo que obtenemos el mínimo
    	// y acto seguido lo borramos de la pila
    	// Al marcarlo en la tabla de referencias como "nulo", lo estamos marcando como "visitado"
        pq.deleteMin();
        nodes[currentV] = nullptr;

        // Recorremos todos los vecinos del vértice que no hayamos visitado ya
        for (Edge<W> e : g[currentV].edges) {
        	if (nodes[e.to] == nullptr) continue;

        	// Si la distancia hasta ese vecino es menor que la que tenemos guardada
        	// Actualizamos los datos (camino y distancia) y aumentamos su prioridad en la cola
        	// (Decrementamos el valor de la clave)
        	W tmpdst = distances[currentV] + e.weight;
            if (tmpdst < distances[e.to]) {
                distances[e.to] = tmpdst;
                path[e.to] = currentV;
                pq.decreaseKey(nodes[e.to], tmpdst);
            }
        }
    }

    // Hacemos y retornamos el equivalente a zip(distances, path)
    std::vector<std::pair<W, vertex_descriptor>> ret(g.size());
    ret[0] = std::pair<W, vertex_descriptor>(std::numeric_limits<W>::max(), 0); // We put the null node
    for(vertex_descriptor i = 1; i < g.size(); ++i) {
        ret[i] = std::pair<W, vertex_descriptor>(distances[i], path[i]);
    }

    return ret;
}
