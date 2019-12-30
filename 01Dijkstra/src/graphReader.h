#pragma once
#include <istream>
#include <string>
#include "graph.h"

// https://gephi.org/users/supported-graph-formats/pajek-net-format/
// http://vlado.fmf.uni-lj.si/pub/networks/pajek/doc/pajekman.pdf

/** This implements a simple pajek reader
 * supporting only *Vertices (without labels) and *arcs with weights */

void readGraph(const std::string & filename, Graph<unsigned> & g);
void readGraph(std::istream & f, Graph<unsigned> & g);

void readCSVGraph(const std::string & filename, Graph<unsigned> & g, const char delimiter=';');
void readCSVGraph(std::istream & f, Graph<unsigned> & g, const char delimiter=';');
