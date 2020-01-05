#include "graphReader.h"
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <sstream>

using namespace std;
using boost::iequals;

#define DELIMITER_VERTICES "*vertices"
#define DELIMITER_ARCS "*arcs"
#define DELIMITER_EDGES "*edges"

void readNETGraph(istream & f, Graph <unsigned> & g) {
    unsigned i;
    readNETGraph(f, g, i);
}

void readNETGraph(const std::string & filename, Graph<unsigned> & g) {
    unsigned i;
    readNETGraph(filename, g, i);
}

void readNETGraph(const std::string & filename, Graph<unsigned> & g, unsigned & cntedges) {
    ifstream f;
    f.open(filename);
    readNETGraph(f, g, cntedges);
    f.close();
}

inline bool isBlank(const string & s) {
    for (int i = 0; i < s.size(); ++i) {
        printf("char %d, %d, %d\n", i, isblank(s[i]), s[i]);
        if (!isblank(s[i]) && s[i] != '\r') return false;
    }

    return true;
}

void readNETGraph(istream & f, Graph<unsigned> & g, unsigned & cntedges) {
    string vertices, arcs, edges, line = "";
    unsigned nvertices, narcs;
    unsigned from, to;
    unsigned weight;

    do {
        f >> vertices;
    } while(!iequals(vertices, DELIMITER_VERTICES));
    f >> nvertices;

    add_vertices(g, nvertices);

    do {
        f >> arcs;
    } while (!iequals(arcs, DELIMITER_ARCS));

    line.clear();
    while(isBlank(line)) {
        getline(f, line, '\n');
        printf("line: %s\n", line.c_str());
    }

    stringstream(line) >> edges;
    if (!iequals(edges, DELIMITER_EDGES)) {
        stringstream(line) >> from >> to >> weight;
        printf(">>  %5d: f: %d, t: %d, w: %d\n", cntedges, from, to, weight);
        add_edge(g, from, to, weight);
        ++cntedges;
    }

    while(!f.eof()) {
        getline(f, line, '\n');
        // printf("%s (%d)\n", line.c_str(), f.eof());
        if (!f.eof() && f.peek() == '\n') f.ignore();
        stringstream(line) >> from >> to >> weight;
        printf(">>> %5d: f: %d, t: %d, w: %d\n", cntedges, from, to, weight);
        add_edge(g, from, to, weight);
        ++cntedges;
    };
}

void readCSVGraph(const std::string & filename, Graph<unsigned> & g, const char delimiter) {
    unsigned i;
    readCSVGraph(filename, g, i, delimiter);
}
void readCSVGraph(std::istream & f, Graph<unsigned> & g, const char delimiter) {
    unsigned i;
    readCSVGraph(f, g, i, delimiter);
}

void readCSVGraph(const std::string & filename, Graph<unsigned> & g, unsigned & cnt, const char delimiter) {
    ifstream f;
    f.open(filename);
    readCSVGraph(f, g, cnt, delimiter);
    f.close();
}

void readCSVGraph(std::istream & f, Graph<unsigned> & g, unsigned & cnt, const char delimiter) {
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
            if (w > 0) {
                add_edge(g, row, col, w);
                cnt++;
            }
        }
    }
}
