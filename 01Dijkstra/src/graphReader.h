#pragma once
#include <istream>
#include <string>
#include "graph.h"

// https://gephi.org/users/supported-graph-formats/pajek-net-format/
// http://vlado.fmf.uni-lj.si/pub/networks/pajek/doc/pajekman.pdf

/** This implements a simple pajek reader
 * supporting only *Vertices (without labels) and *arcs with weights */

bool readNETGraph(const std::string & filename, Graph<unsigned> & g);
bool readNETGraph(std::istream & f, Graph<unsigned> & g);
bool readNETGraph(const std::string & filename, Graph<unsigned> & g, unsigned & cntedges);
bool readNETGraph(std::istream & f, Graph<unsigned> & g, unsigned & cntedges);

bool readCSVGraph(const std::string & filename, Graph<unsigned> & g, unsigned & cnt, const char delimiter=';');
bool readCSVGraph(std::istream & f, Graph<unsigned> & g, unsigned & cnt, const char delimiter=';');
bool readCSVGraph(const std::string & filename, Graph<unsigned> & g, const char delimiter=';');
bool readCSVGraph(std::istream & f, Graph<unsigned> & g, const char delimiter=';');
