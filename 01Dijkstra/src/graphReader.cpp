#include "graphReader.h"
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <sstream>

using namespace std;
using boost::iequals;

#define DELIMITER_VERTICES "*vertices"
#define DELIMITER_ARCS "*arcs"
#define DELIMITER_EDGES "*edges"

bool readNETGraph(istream & f, Graph <unsigned> & g) {
    unsigned i;
    return readNETGraph(f, g, i);
}

bool readNETGraph(const std::string & filename, Graph<unsigned> & g) {
    unsigned i;
    return readNETGraph(filename, g, i);
}

bool readNETGraph(const std::string & filename, Graph<unsigned> & g, unsigned & cntedges) {
    ifstream f;
    f.open(filename);
    bool s = readNETGraph(f, g, cntedges);
    f.close();
    return s;
}

inline bool isBlank(const string & s) {
    for (int i = 0; i < s.size(); ++i) {
        // fprintf(stderr, "char %d, %d, %d\n", i, isblank(s[i]), s[i]);
        if (!isblank(s[i]) && s[i] != '\r') return false;
    }

    return true;
}

bool readNETGraph(istream & f, Graph<unsigned> & g, unsigned & cntedges) {
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
    }

    stringstream(line) >> edges;
    if (!iequals(edges, DELIMITER_EDGES)) {
        stringstream(line) >> from >> to >> weight;
        // printf(">>  %5d: f: %d, t: %d, w: %d\n", cntedges, from, to, weight);
        add_edge(g, from, to, weight);
        ++cntedges;
    }

    while(!f.eof()) {
        getline(f, line, '\n');
        // printf("%s (%d)\n", line.c_str(), f.eof());
        if (!f.eof() && f.peek() == '\n') f.ignore();
        stringstream(line) >> from >> to >> weight;
        // printf(">>> %5d: f: %d, t: %d, w: %d\n", cntedges, from, to, weight);
        add_edge(g, from, to, weight);
        ++cntedges;
    };

    return !f.fail();
}

bool readCSVGraph(const std::string & filename, Graph<unsigned> & g, const char delimiter) {
    unsigned i;
    return readCSVGraph(filename, g, i, delimiter);
}
bool readCSVGraph(std::istream & f, Graph<unsigned> & g, const char delimiter) {
    unsigned i;
    return readCSVGraph(f, g, i, delimiter);
}

bool readCSVGraph(const std::string & filename, Graph<unsigned> & g, unsigned & cnt, const char delimiter) {
    ifstream f;
    f.open(filename);
    readCSVGraph(f, g, cnt, delimiter);
    bool ret = !f.fail();
    f.close();
    return ret;
}

bool readCSVGraph(std::istream & f, Graph<unsigned> & g, unsigned & cnt, const char delimiter) {
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

    return !f.fail();
}
