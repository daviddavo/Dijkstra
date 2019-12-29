#include "graphReader.h"
#include <fstream>
using namespace std;

#define DELIMITER_VERTICES "*vertices"
#define DELIMITER_EDGES "*arcs"

// Graph<unsigned> & readGraph(std::string &);
// Graph<int> & readGraph(std::string &);

void readGraph(const std::string & filename, Graph<unsigned> & g) {
    ifstream f;
    f.open(filename);
    readGraph(f, g);
    f.close();
}

void readGraph(istream & f, Graph<unsigned> & g) {
    string vertices;
    unsigned nvertices;
    string arcs;
    unsigned narcs;
    unsigned from, to;
    unsigned weight;

    do {
        f >> vertices;
    } while(vertices != DELIMITER_VERTICES);
    f >> nvertices;

    for (unsigned i = 0; i < nvertices; ++i)
        add_vertex(g);

    do {
        f >> arcs;
    } while (arcs != DELIMITER_EDGES);

    int i = 0;
    while (f >> from >> to >> weight) {
        add_edge(g, from, to, weight);
        ++i;
    }
}

