# ADT for the graph of the domain

class Domain:
    def __init__(self):
        self.list_of_edges = {}
        self.data_map = {}

    def add(self, node):
        self.list_of_edges[node] = []

    def add_edge(self, node1, node2):
        if node1 not in self.list_of_edges:
            self.list_of_edges[node1] = []
        self.list_of_edges[node1].append(node2)
        self.list_of_edges[node2].append(node1)
        if node1 not in self.data_map:
            self.data_map[node1] = {}
        self.data_map[node1][node2] = 0
        if node2 not in self.data_map:
            self.data_map[node2] = {}
        self.data_map[node2][node1] = 0

    def remove_edge(self, node1, node2):
        self.list_of_edges[node1].remove(node2)
        self.data_map[node1].pop(node2)

    def remove_vertex(self, node):
        self.list_of_edges.pop(node)
        self.data_map.pop(node)
        for key in self.list_of_edges:
            if node in self.list_of_edges[key]:
                self.list_of_edges[key].remove(node)
                self.data_map[key].pop(node)

    def add_vertex(self, node):
        self.list_of_edges[node] = []
        self.data_map[node] = {}

    def add_data_to_certain_edge(self, node1, node2, data):
        if node1 not in self.data_map:
            self.data_map[node1] = {}
        self.data_map[node1][node2] = data
        if node2 not in self.data_map:
            self.data_map[node2] = {}
        self.data_map[node2][node1] = data

    def get_domain(self):
        return self.list_of_edges


    def __str__(self):
        return str(self.list_of_edges)