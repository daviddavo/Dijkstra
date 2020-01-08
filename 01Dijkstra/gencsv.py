#!/usr/bin/python3

import subprocess
from subprocess import PIPE, DEVNULL
import sys
from networkx.generators.random_graphs import *
from random import randint

CSV_SEPARATOR = ','
MAX_WEIGHT = 1
START_RANGE = 50
BATCH_SIZE = 1000
END_RANGE = 50000
STEP_RANGE = 100
SEED = 42

def writeNETFile(g, f):
    f.write(f"*Vertices {len(g.nodes)}\n")
    f.write("*Arcs\n")
    f.write("*Edges\n")
    for e in g.edges:
        f.write(f"{e[0]+1} {e[1]+1} {randint(1, MAX_WEIGHT)}\n")

def writeNETString(g):
    """
    f.write("# WTF")
    f.write(f"*Vertices {len(g.nodes)}\n")
    f.write("*Arcs\n")
    f.write("*Edges\n")
    for e in g.edges:
        f.write(f"{e[0]+1} {e[1]+1} {randint(1, MAX_WEIGHT)}\n")
    """
    return f"*Vertices {len(g.nodes)}\n*Arcs\n*Edges\n"+''.join([f"{e[0]+1} {e[1]+1} {randint(1, MAX_WEIGHT)}\n" for e in g.edges]) 

if __name__ == "__main__":
    probabilities = [
            0.01, 0.05, 
            0.1, 0.2, 0.5]
    offset = START_RANGE
    while (offset < END_RANGE):
        end = min(offset+BATCH_SIZE, END_RANGE)
        for p in probabilities:
            fname = f"./out/gnp2_{SEED}_{str(p).split('.')[1]}.csv"
            with open(fname, 'a+') as f:
                for i in range(offset, end, STEP_RANGE):
                    g = fast_gnp_random_graph(i, p, directed=True, seed=42)

                    with open("tmpfile.net", 'w+') as ftmp:
                        writeNETFile(g, ftmp)
                        
                    print(f"P: {p:.3f}, V: {i:06d}, E: {len(g.edges):06d}", end='', flush=True)
                    res = subprocess.run(["build/Release/time", "tmpfile.net", "-", "1"], encoding='ascii', stdout=PIPE, stderr=DEVNULL)
                    f.write((CSV_SEPARATOR.join([str(i), str(len(g.edges)), res.stdout.strip('\n')])) + '\n')
                    f.flush()
                    print(f" t: {int(res.stdout):012d}")

        offset = end
