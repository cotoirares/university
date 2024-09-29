# UI for the graph operations

import repository
from collections import deque


class UI:
    def __init__(self):
        self.repo = repository.Repository()

    def print_menu(self):
        print("1. Add node")
        print("2. Add edge")
        print("3. Remove edge")
        print("4. Remove vertex")
        print("5. Add vertex")
        print("6. Check if there is an edge between two nodes")
        print("7. Get in degree of a node")
        print("8. Get out degree of a node")
        print("9. Get set of outbound edges of a node")
        print("10. Get set of inbound edges of a node")
        print("11. Modify data of a certain edge")
        print("12. Print the graph")
        print("13. Show the connected components using DFS")
        print("14. Exit")

    def get_graph_from_file(self):
        reading_file = open("graph_data.txt", "r")
        line = reading_file.readline()
        line = line.strip()
        line = line.split(" ")
        n = int(line[0])
        m = int(line[1])
        self.repo.init_list_of_nodes(n)
        for i in range(m):
            line = reading_file.readline()
            line = line.strip()
            line = line.split(" ")
            x = int(line[0])
            y = int(line[1])
            c = int(line[2])
            self.repo.add_edge(x, y)
            self.repo.modify_data_of_certain_edge(x, y, c)
        reading_file.close()

    def handle_user_input(self):
        self.get_graph_from_file()
        while(True):
            self.print_menu()
            user_input = input("Enter your choice: ")
            if user_input == "1":
                node = input("Enter the node: ")
                node = int(node)
                self.repo.add(node)
            elif user_input == "2":
                node1 = input("Enter the first node: ")
                node1 = int(node1)
                node2 = input("Enter the second node: ")
                node2 = int(node2)
                self.repo.add_edge(node1, node2)
            elif user_input == "3":
                node1 = input("Enter the first node: ")
                node1 = int(node1)
                node2 = input("Enter the second node: ")
                node2 = int(node2)
                self.repo.remove_edge(node1, node2)
            elif user_input == "4":
                node = input("Enter the node: ")
                node = int(node)
                self.repo.remove_vertex(node)
            elif user_input == "5":
                node = input("Enter the node: ")
                node = int(node)
                self.repo.add_vertex(node)
            elif user_input == "6":
                node1 = input("Enter the first node: ")
                node1 = int(node1)
                node2 = input("Enter the second node: ")
                node2 = int(node2)
                if self.repo.edge_between_nodes(node1, node2):
                    print("There is an edge between the two nodes")
                else:
                    print("There is no edge between the two nodes")
            elif user_input == "7":
                node = input("Enter the node: ")
                node = int(node)
                print("The in degree of the node is: ", self.repo.get_in_degree(node))
            elif user_input == "8":
                node = input("Enter the node: ")
                node = int(node)
                print("The out degree of the node is: ", self.repo.get_out_degree(node))
            elif user_input == "9":
                node = input("Enter the node: ")
                node = int(node)
                print("The set of outbound edges of the node is: ", self.repo.get_set_of_outbound_edges(node))
            elif user_input == "10":
                node = input("Enter the node: ")
                node = int(node)
                print("The set of inbound edges of the node is: ", self.repo.get_set_of_inbound_edges(node))
            elif user_input == "11":
                node1 = input("Enter the first node: ")
                node1 = int(node1)
                node2 = input("Enter the second node: ")
                node2 = int(node2)
                new_data = input("Enter the new data: ")
                new_data = int(new_data)
                self.repo.modify_data_of_certain_edge(node1, node2, new_data)
            elif user_input == "12":
                for key in self.repo.get_domain():
                    for value in self.repo.get_domain()[key]:
                        print("Edge", key, "-", value, " with value:", self.repo.list_of_edges.data_map[key][value])
            elif user_input == "13":
                print("The connected components are: ")
                components = deque()
                components = self.repo.connected_components()
                count = 1
                for component in components:
                    print(f"Component {count}: ")
                    for char in component:
                        if (0 < char < 10) or char == ",":
                            print(char, end=" ")
                    print()
                    count += 1
            elif user_input == "14":
                break
            else:
                print("Invalid input")

