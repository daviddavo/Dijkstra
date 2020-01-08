#!/usr/bin/python3

import subprocess
from subprocess import PIPE
import sys
from networkx.generators.random_graphs import *
from random import randint

CSV_SEPARATOR = ','
MAX_WEIGHT = 1
START_RANGE = 50
END_RANGE = 10000
STEP_RANGE = 100
SEED = 42

def writeNETFile(g):
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
            # 0.01, 0.05, 
            0.1, 0.2, 0.5]
    for p in probabilities:
        fname = f"./out/gnp_{SEED}_{str(p).split('.')[1]}.csv"
        with open(fname, 'a+') as f:
            for i in range(START_RANGE, END_RANGE, STEP_RANGE):
                g = fast_gnp_random_graph(i, p, directed=True, seed=42)
    # p = subprocess.Popen(["build/Release/time", "-", "-", "0"], stdin=PIPE)
    # p.communicate(input=writeNETFile(g).encode())
    # p.stdin.close()
                print(f"P: {p:.3f}, V: {i:06d}, E: {len(g.edges):06d}", end='', flush=True)
                res = subprocess.run(["build/Release/time", "-", "-", "1"], input=writeNETFile(g), encoding='ascii', stdout=PIPE)
                f.write((CSV_SEPARATOR.join([str(i), str(len(g.edges)), res.stdout.strip('\n')])) + '\n')
                print(f" t: {int(res.stdout):012d}")

