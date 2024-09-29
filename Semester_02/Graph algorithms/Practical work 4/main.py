# 5. Write a program that, given an undirected connected graph, constructs a minumal spanning tree using the Kruskal's algorithm.
# The graph is given as a list of edges, each edge being a tuple of two nodes and a weight.

# Author: Rares Cotoi, @ 912

from collections import defaultdict

class Graph:
    def __init__(self):
        self.graph = defaultdict(list)
        self.edges = []

    def add_edge(self, u, v, w):
        self.graph[u].append((v, w))
        self.graph[v].append((u, w))
        self.edges.append((u, v, w))

    def find(self, parent, i):
        if parent[i] == i:
            return i
        return self.find(parent, parent[i])

    def union(self, parent, rank, x, y):
        xroot = self.find(parent, x)
        yroot = self.find(parent, y)
        if rank[xroot] < rank[yroot]:
            parent[xroot] = yroot
        elif rank[xroot] > rank[yroot]:
            parent[yroot] = xroot
        else:
            parent[yroot] = xroot
            rank[xroot] += 1

    def kruskal(self):
        result = []
        i = 0
        e = 0
        self.edges = sorted(self.edges, key=lambda item: item[2])
        parent = []
        rank = []
        for node in self.graph:
            parent.append(node)
            rank.append(0)
        while e < len(self.graph) - 1:
            u, v, w = self.edges[i]
            i += 1
            x = self.find(parent, u)
            y = self.find(parent, v)
            if x != y:
                e += 1
                result.append((u, v, w))
                self.union(parent, rank, x, y)
        return result

    def print_result(self, result):
        for u, v, w in result:
            print(u, v, w)

def main():
    graph = Graph()
    graph.add_edge(0, 1, 10)
    graph.add_edge(0, 2, 6)
    graph.add_edge(0, 3, 5)
    graph.add_edge(1, 3, 15)
    graph.add_edge(2, 3, 4)
    result = graph.kruskal()
    graph.print_result(result)

main()
