# Write a program that, given a graph with costs and two vertices, finds a lowest cost walk between the given vertices, or prints a message if there are negative cost cycles accessible from the starting vertex. The program will use a matrix defined as d[x,k]=the cost of the lowest cost walk from s to x and of length equal to k, where s is the starting vertex.

# Author: Rares Cotoi, @ 912

import numpy as np
import sys

def read_data():
    f = open("input.txt", "r")
    n, m = map(int, f.readline().split())
    graph = []
    for i in range(n+1):
        graph.append([0]*(n+1))
    for i in range(m):
        x, y, c = map(int, f.readline().split())
        graph[x][y] = c
    return n, graph

def bellman_ford(n, graph):
    d = np.zeros((n+1, n+1))
    for i in range(1, n+1):
        d[i][0] = sys.maxsize
    d[1][0] = 0
    for k in range(1, n+1):
        for x in range(1, n+1):
            d[x][k] = d[x][k-1]
            for y in range(1, n+1):
                if graph[y][x] != 0 and d[y][k-1] != sys.maxsize:
                    d[x][k] = min(d[x][k], d[y][k-1] + graph[y][x])
    for i in range(1, n+1):
        if d[i][n] != d[i][n-1]:
            return "Negative cost cycle"
    result = []
    for i in range(1, n+1):
        result.append(d[i])
    return result

def print_result(result):
    if result == "Negative cost cycle":
        print(result)
    else:
        for i in range(len(result)):
            print(result[i][len(result[i])-1], end=" ")

def main():
    n, graph = read_data()
    result = bellman_ford(n, graph)
    print_result(result)

main()
