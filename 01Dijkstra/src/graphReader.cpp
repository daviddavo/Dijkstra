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

    add_vertices(g, nvertices);

    do {
        f >> arcs;
    } while (arcs != DELIMITER_EDGES);

    int i = 0;
    while (f >> from >> to >> weight) {
        add_edge(g, from, to, weight);
        ++i;
    }
}

void readCSVGraph(const std::string & filename, Graph<unsigned> & g, const char delimiter) {
    ifstream f;
    f.open(filename);
    readCSVGraph(f, g, delimiter);
    f.close();
}

void readCSVGraph(std::istream & f, Graph<unsigned> & g, const char delimiter) {
    string vdstr;
    vertex_descriptor vd, nvertices;
    unsigned w;
    // First thing should be empty
    getline(f, vdstr, delimiter);
    // Next we should get the number of vertices
    getline(f, vdstr, delimiter);
    nvertices = stoul(vdstr); // This is the number of vertices
    add_vertices(g, nvertices);
    // The rest of the line is useless
    getline(f, vdstr, '\n');

    // Now to read the "edges"
    for (vertex_descriptor row = nvertices; row > 0; row--) {
        getline(f, vdstr, delimiter); // This 1st column is "useless"
        if (stoul(vdstr) != row) fprintf(stderr,"Warning: Inconsistent file\n");
        for (vertex_descriptor col = nvertices; col > 0; col--) {
            getline(f, vdstr, (col == 1)?'\n':delimiter);
            w = stoul(vdstr);
            if (w > 0) add_edge(g, row, col, w);
        }
    }
}
