import copy
import domain
from collections import deque


class Repository:
    def __init__(self):
        self.list_of_edges = domain.Domain()

    def add(self, node):
        self.list_of_edges.add(node)

    def init_list_of_nodes(self, length_of_list):
        for i in range(0, length_of_list):
            self.add(i)

    def add_edge(self, node1, node2):
        self.list_of_edges.add_edge(node1, node2)

    def remove_edge(self, node1, node2):
        self.list_of_edges.remove_edge(node1, node2)

    def remove_vertex(self, node):
        self.list_of_edges.remove_vertex(node)

    def add_vertex(self, node):
        self.list_of_edges.add_vertex(node)

    def make_copy_of_graph(self):
        new_graph = Repository()
        new_graph.list_of_edges = copy.deepcopy(self.list_of_edges)
        return new_graph

    def get_domain(self):
        return self.list_of_edges.get_domain()

    def edge_between_nodes(self, node1, node2):
        if node2 in self.list_of_edges.get_domain()[node1]:
            return True
        return False

    def get_in_degree(self, node):
        in_degree = 0
        for key in self.list_of_edges.get_domain():
            if node in self.list_of_edges.get_domain()[key] and key != node:
                in_degree += 1
        return in_degree

    def get_out_degree(self, node):
        if node not in self.list_of_edges.get_domain():
            raise KeyError("The node does not exist")
        return len(self.list_of_edges.get_domain()[node])

    def get_set_of_outbound_edges(self, node):
        return self.list_of_edges.get_domain()[node]

    def get_set_of_inbound_edges(self, node):
        in_edges = []
        for key in self.list_of_edges.get_domain():
            if node in self.list_of_edges.get_domain()[key] and key != node:
                in_edges.append(key)
        return in_edges

    def modify_data_of_certain_edge(self, node1, node2, new_data):
        self.list_of_edges.add_data_to_certain_edge(node1, node2, new_data)

    def dfs(self, start_node, visited, component):
        visited[start_node] = True
        component.append(start_node)
        for node in self.list_of_edges.get_domain()[start_node]:
            if not visited[node]:
                self.dfs(node, visited, component)

    def connected_components(self):
        visited = deque()
        for key in self.list_of_edges.get_domain():
            visited.append(False)
        components = deque()
        for key in self.list_of_edges.get_domain():
            if not visited[key]:
                component = deque()
                self.dfs(key, visited, component)
                components.append(component)
        return components

    def __str__(self):
        return str(self.list_of_edges)