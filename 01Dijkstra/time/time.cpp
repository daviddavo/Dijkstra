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

/**
 * For small numbers, is faster to check with stat if a file exists
 * than getting the DIR entry and iterating over it
 */ 
string getNextFileName(string path, string fname) {
    int i = 1;
    while(fileExists(fname + to_string(i))) ++i;

    return fname + to_string(i);
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

int main(int argc, char * argv[]) {
    printf("%s\n", argv[0]);
    printf("%s\n", getNextFileName("", argv[1]).c_str());
    Graph<unsigned> g1;
    add_vertex(g1);
    add_vertex(g1);
    add_edge(g1, 1, 2);
    // printf("%s %d\n", timeDijkstra(g1, 1));
    cout << "nanoseconds: " << timeDijkstra(g1, 1) << "\n";
    return 0;
}
