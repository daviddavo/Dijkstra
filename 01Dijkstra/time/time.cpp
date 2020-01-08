#include <sys/stat.h>
#include <string>
#include <chrono>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include "graph.h"
#include "graphReader.h"
#include "dijkstra.h"

#define FILE_INDEX_START 1
#define COMMENTS_CHAR '#'
#define SEPARATOR_CHAR ','

using namespace std;
using namespace std::chrono;

bool fileExists(const char * fname) {
    struct stat st;
    return (stat(fname, &st) == 0);
}

bool inline fileExists(const string & str) {
    return fileExists(str.c_str());
}

long int timeDijkstra(const Graph<unsigned> & g, vertex_descriptor source) {
    time_point<high_resolution_clock> start, end;

    start = high_resolution_clock::now();
    dijkstra(g, source);
    end = high_resolution_clock::now();
    long int diff = duration_cast<nanoseconds>(end-start).count();
    if (diff < 10000) fprintf(stderr, "Warning: Test took less than 10 ms\n");
    return diff;
}

long int timeDijsktraWrapper(const Graph<unsigned> & g, vertex_descriptor source) {
	long int S = timeDijkstra(g, source);
	if (S < 10000000) {
		// 99 + 1 = 100
		for (int i = 1; i < 100; ++i) S += timeDijkstra(g, source);
		S = S / 100;
	}

	return S;
}

bool readFile(Graph<unsigned> & g, const string & filename) {
    size_t i = filename.rfind('.', filename.length());
    unsigned nedges = 0;

    if (i == -1) return false;
    string ext = filename.substr(i+1, filename.length() - i);
    if (ext == "csv" || ext == "edges") {
        fprintf(stderr, "Reading CSV file %s\n", filename.c_str());
        readCSVGraph(filename, g, nedges);
    } else if (ext == "net") {
        fprintf(stderr, "Reading Pajek NET file %s\n", filename.c_str(), nedges);
        readNETGraph(filename, g, nedges);
    } else {
        printf("Unknown extension: %s\n", ext.c_str());
        return false;
    }

    fprintf(stderr, "Read %d vertices and %d edges\n", g.size()-1, nedges);

    return true;
}

void writeHeader(ostream & s, const string & filename, unsigned nvertex, unsigned nedges) {
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	s << COMMENTS_CHAR << " File created at " << put_time(&tm, "%Y-%m-%d %H:%M:%S%z") << " from file " << filename << '\n';
	s << COMMENTS_CHAR << " Vertices: " << nvertex << " Edges: " << nedges << '\n';
}

void writeCSVBody(ostream & s, const Graph<unsigned> & g) {
	for (vertex_descriptor i = 1; i < g.size(); ++i) {
		s << setw(8) << i << SEPARATOR_CHAR << setw(12) << timeDijsktraWrapper(g, i) << '\n';
	}
}

int main(int argc, char * argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return 1;
    }

    if (fileExists(argv[2])) {
    	fprintf(stderr, "Output file already %s exists\n", argv[1]);
    	return 2;
    }

    Graph<unsigned> g;
    unsigned nedges;
    bool success;
    if (argv[1][0] == '-') {
    	success = readNETGraph(cin, g, nedges);
    } else {
    	success = readFile(g, argv[1]);
    }

    if (!success) {
    	fprintf(stderr, "Error reading file\n");
    	return 3;
    }

    vertex_descriptor source = 0; // If source = 0 then we do every vertex
    if (argc == 4) source = stoul(argv[3]);

    if (source) {
    	printf("%d\n", timeDijsktraWrapper(g, source));
    } else {
		if (argv[2][0] == '-') {
			writeHeader(cout, argv[1], g.size()-1, nedges);
			writeCSVBody(cout, g);
		} else {
			ofstream f;
			f.open(argv[2]);
			writeHeader(f, argv[1], g.size()-1, nedges);
			writeCSVBody(f, g);
			f.close();
		}
    }

    return 0;
}
