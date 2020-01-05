#include <sys/stat.h>
#include <string>
#include <chrono>
#include <iostream>
#include "graph.h"
#include "graphReader.h"
#include "dijkstra.h"

#define FILE_INDEX_START 1

using namespace std;
using namespace std::chrono;

bool fileExists(const char * fname) {
    struct stat st;
    return (stat(fname, &st) == 0);
}

bool inline fileExists(const string & str) {
    return fileExists(str.c_str());
}

long int timeDijkstra(Graph<unsigned> & g, vertex_descriptor source) {
    time_point<high_resolution_clock> start, end;

    start = high_resolution_clock::now();
    dijkstra(g, source);
    end = high_resolution_clock::now();
    long int diff = duration_cast<nanoseconds>(end-start).count(); 
    if (diff < 10000) fprintf(stderr, "Warning: Test took less than 10 ms\n");
    return diff;
}

bool readFile(Graph<unsigned> & g, const string & filename) {
    size_t i = filename.rfind('.', filename.length());
    unsigned nedges = 0;

    if (i == -1) return false;
    string ext = filename.substr(i+1, filename.length() - i);
    if (ext == "csv" || ext == "edges") {
        printf("Reading CSV file %s\n", filename.c_str());
        readCSVGraph(filename, g, nedges);
    } else if (ext == "net") {
        printf("Reading Pajek NET file %s\n", filename.c_str(), nedges);
        readNETGraph(filename, g, nedges);
    } else {
        printf("Unknown extension: %s\n", ext.c_str());
        return false;
    }

    printf("Read %d vertices and %d edges\n", g.size()-1, nedges);

    return true;
}

int main(int argc, char * argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return 1;
    }
    Graph<unsigned> g1;
    readFile(g1, argv[1]);
    // printf("%s %d\n", timeDijkstra(g1, 1));
    cout << "nanoseconds: " << timeDijkstra(g1, 1) << "\n";
    return 0;
}
