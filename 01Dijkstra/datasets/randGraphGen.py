#!/usr/env/python3

import sys
import networkx as nx
from networkx.generators.random_graphs import *
from random import randint

MAX_INT = 1

def writeNETFile(g):
    print(f"*Vertices {len(g.nodes)}")
    print("*Arcs")
    print("*Edges")
    for e in g.edges:
        print(f"{e[0]+1} {e[1]+1} {randint(1, MAX_INT)}")

functions = [
    lambda x, y : erdos_renyi_graph(int(x), float(y), directed=True),
    lambda x, y : fast_gnp_random_graph(int(x), float(y), directed=True)
]

if __name__ == "__main__":
    writeNETFile(functions[int(sys.argv[1])](sys.argv[2], sys.argv[3]))
