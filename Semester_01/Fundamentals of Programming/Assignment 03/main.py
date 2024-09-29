"""
Complexity visualisation for Bubble Sort & Strand Sort

Author: Cotoi Rares, @912

"""


from tabulate import tabulate
from random import randint
import time


def display_menu():
    print("1. Generate a list of numbers")
    print("2. Sort the list using bubble sort")
    print("3. Sort the list using strand sort")
    print("4. Test the sorting algorithms for best case")
    print("5. Test the sorting algorithms for worst case")
    print("6. Test the sorting algorithms for average case")
    print("0. Exit the program")


def list_generator_with_random_numbers(numbers_to_generate: int) -> [int]:
    list_of_numbers = []
    for index in range(numbers_to_generate):
        list_of_numbers.append(randint(0, 100))
    return list_of_numbers


def list_generator_sorted_in_ascending_order(numbers_to_generate: int) -> [int]:
    list_of_generated_numbers = []
    random_number_generated = randint(0, 100)
    list_of_generated_numbers.append(random_number_generated)
    for index in range(1, numbers_to_generate):
        random_number_generated = random_number_generated + randint(0, 100)
        list_of_generated_numbers.append(random_number_generated)
    return list_of_generated_numbers


def list_generator_sorted_in_descending_order(numbers_to_generate: int) -> [int]:
    list_of_generated_numbers = []
    for index in range(numbers_to_generate, 0, -1):
        list_of_generated_numbers.append(index)
    return list_of_generated_numbers


def numbers_generator(numbers_to_generate: int, case: int) -> list:
    try:
        numbers_to_generate = int(numbers_to_generate)
    except ValueError:
        print("Invalid input!")
    if case == 0:  # worst case
        list_of_numbers = list_generator_sorted_in_descending_order(numbers_to_generate)
    elif case == 1:  # average case
        list_of_numbers = list_generator_with_random_numbers(numbers_to_generate)
    elif case == 2:  # best case
        list_of_numbers = list_generator_sorted_in_ascending_order(numbers_to_generate)
    return list_of_numbers


def bubble_sort(list_of_numbers: list[int]) -> list:
    sorted = False
    length_of_list = len(list_of_numbers)
    while not sorted:
        sorted = True
        for index in range(0, length_of_list - 1):
            if list_of_numbers[index] > list_of_numbers[index + 1]:
                sorted = False
                auxiliary_for_interchange = list_of_numbers[index]
                list_of_numbers[index] = list_of_numbers[index + 1]
                list_of_numbers[index + 1] = auxiliary_for_interchange
    return list_of_numbers


def merge(list_of_numbers1: list[int], list_of_numbers2: list[int]) -> list[int]:
    list_of_numbers = []
    list1_index = 0
    list2_index = 0
    while list1_index < len(list_of_numbers1) and list2_index < len(list_of_numbers2):
        if list_of_numbers1[list1_index] <= list_of_numbers2[list2_index]:
            list_of_numbers.append(list_of_numbers1[list1_index])
            list1_index += 1
        else:
            list_of_numbers.append(list_of_numbers2[list2_index])
            list2_index += 1
    while list1_index < len(list_of_numbers1):
        list_of_numbers.append(list_of_numbers1[list1_index])
        list1_index += 1
    while list2_index < len(list_of_numbers2):
        list_of_numbers.append(list_of_numbers2[list2_index])
        list2_index += 1
    return list_of_numbers


def strand_sort(list_of_numbers: list[int]) -> list[int]:
    if not list_of_numbers:
        return []
    sublist = [list_of_numbers[0]]
    to_be_removed = list_of_numbers[0]
    list_of_numbers = [number for number in list_of_numbers if number != to_be_removed]
    index = 0
    while index < len(list_of_numbers):
        if list_of_numbers[index] >= sublist[-1]:
            sublist.append(list_of_numbers[index])
            to_be_removed = list_of_numbers[index]
            list_of_numbers = [number for number in list_of_numbers if number != to_be_removed]
        else:
            index += 1
    return merge(strand_sort(list_of_numbers), sublist)


def get_time_for_executing_bubble_sort(list_of_numbers: list) -> float:
    start_time = time.time()
    bubble_sort(list_of_numbers)
    end_time = time.time()
    return end_time - start_time


def get_time_for_executing_strand_sort(list_of_numbers: list) -> float:
    start_time = time.time()
    strand_sort(list_of_numbers)
    end_time = time.time()
    return end_time - start_time


def create_table_rows_with_execution_time_for_bubble_sort(array_length: int, case:int) -> list:
    table_rows = []
    for index in range(0, 5):
        list_of_numbers = numbers_generator(array_length * (2 ** index), case)
        time = get_time_for_executing_bubble_sort(list_of_numbers)
        table_rows = table_rows + ([[array_length * (2 ** index), time]])
    return table_rows


def create_table_rows_with_execution_time_for_strand_sort(array_length: int, case:int) -> list:
    table_rows = []
    for index in range(0, 5):
        list_of_numbers = numbers_generator(array_length * (2 ** index), case)
        time = get_time_for_executing_strand_sort(list_of_numbers)
        table_rows = table_rows + [[array_length * (2 ** index), time]]
    return table_rows


def create_table_rows_with_execution_time_for_both_algorithms(array_length: int, case:int) -> list:
    table_rows = []
    for index in range(0, 5):
        list_of_numbers = numbers_generator(array_length * (2 ** index), case)
        bubble_sort_execution_time = get_time_for_executing_bubble_sort(list_of_numbers)
        strand_sort_execution_time = get_time_for_executing_strand_sort(list_of_numbers)
        table_rows = table_rows + [[array_length * (2 ** index),
                                    bubble_sort_execution_time, strand_sort_execution_time]]
    return table_rows


def best_case_algorithms_interpreter(algorith_entered_by_user: int): # remember that best case = 2 in number generator
    if algorith_entered_by_user == 1:  # bubble
        print("Enter the array length:")
        array_length = int(input(">"))
        table_headers = ["Array length", "Execution time"]
        table_rows = create_table_rows_with_execution_time_for_bubble_sort(array_length, 2)
        print(tabulate(table_rows, table_headers, tablefmt="grid"))
    elif algorith_entered_by_user == 2:  # strand
        print("Enter the array length:")
        array_length = int(input(">"))
        table_headers = ["Array length", "Execution time"]
        table_rows = create_table_rows_with_execution_time_for_strand_sort(array_length, 2)
        print(tabulate(table_rows, table_headers, tablefmt="grid"))
    elif algorith_entered_by_user == 3:
        print("Enter the array length:")
        array_length = int(input(">"))
        table_headers = ["Array length", "Bubble Sort", "Strand Sort"]
        table_rows = create_table_rows_with_execution_time_for_both_algorithms(array_length, 2)
        print(tabulate(table_rows, table_headers, tablefmt="grid"))


def worst_case_algorithms_interpreter(algorith_entered_by_user: int): # remember that worst case = 0 in number generator
    if algorith_entered_by_user == 1:
        print("Enter the array length:")
        array_length = int(input(">"))
        table_headers = ["Array length", "Execution time"]
        table_rows = create_table_rows_with_execution_time_for_bubble_sort(array_length, 0)
        print(tabulate(table_rows, table_headers, tablefmt="grid"))
    elif algorith_entered_by_user == 2:
        print("Enter the array length:")
        array_length = int(input(">"))
        table_headers = ["Array length", "Execution time"]
        table_rows = create_table_rows_with_execution_time_for_strand_sort(array_length, 0)
        print(tabulate(table_rows, table_headers, tablefmt="grid"))
    elif algorith_entered_by_user == 3:
        print("Enter the array length:")
        array_length = int(input(">"))
        table_headers = ["Array length", "Bubble Sort", "Strand Sort"]
        table_rows =  create_table_rows_with_execution_time_for_both_algorithms(array_length, 0)
        print(tabulate(table_rows, table_headers, tablefmt="grid"))


def average_case_algorithms_interpreter(algorith_entered_by_user: int): # remember that average case = 1 in number generator
    if algorith_entered_by_user == 1:  # in the menu option 1 is reserved for bubble sort
        print("Enter the array length:")
        array_length = int(input(">"))
        table_headers = ["Array length", "Execution time"]
        table_rows = create_table_rows_with_execution_time_for_bubble_sort(array_length, 1)
        print(tabulate(table_rows, table_headers, tablefmt="grid"))
    elif algorith_entered_by_user == 2:  # in the menu option 2 is reserved for strand sort
        print("Enter the array length:")
        array_length = int(input(">"))
        table_headers = ["Array length", "Execution time"]
        table_rows = create_table_rows_with_execution_time_for_strand_sort(array_length, 1)
        print(tabulate(table_rows, table_headers, tablefmt="grid"))
    elif algorith_entered_by_user == 3:  # in the menu option 3 is reserved for comparing both algorithms
        print("Enter the array length:")
        array_length = int(input(">"))
        table_headers = ["Array length", "Bubble Sort", "Strand Sort"]
        table_rows = create_table_rows_with_execution_time_for_both_algorithms(array_length, 1)
        print(tabulate(table_rows, table_headers, tablefmt="grid"))


def main():
    while True:
        display_menu()
        option = input(">")
        if option == "1":  # generating a list of numbers
            number_of_numbers_to_generate = int(input("Enter the number of numbers you want to generate: "))
            list_of_numbers = numbers_generator(number_of_numbers_to_generate, 1)
            print(list_of_numbers)
        elif option == "2":  # sorting using bubble sort
            list_of_numbers = bubble_sort(list_of_numbers)
            print(f"The sorted array is: {list_of_numbers}")
        elif option == "3":  # sorting using strand sort
            the_sorted_list = strand_sort(list_of_numbers)
            print(f"The sorted array is: {the_sorted_list}")
        elif option == "4":  # testing the sorting algorithms for best case
            print("Select the algorithm you want to test with the best case numbers:")
            print("1. Bubble Sort")
            print("2. Strand Sort")
            print("3. Compare both algorithms")
            algorith_entered_by_user = int(input(">"))
            best_case_algorithms_interpreter(algorith_entered_by_user)
        elif option == "5":  # testing the sorting algorithms for worst case
            print("Select the algorithm you want to test with the worst case numbers:")
            print("1. Bubble Sort")
            print("2. Strand Sort")
            print("3. Compare both algorithms")
            algorith_entered_by_user = int(input(">"))
            worst_case_algorithms_interpreter(algorith_entered_by_user)
        elif option == "6":  # testing the sorting algorithms for average case
            print("Select the algorithm you want to test with the average case numbers:")
            print("1. Bubble Sort")
            print("2. Strand Sort")
            print("3. Compare both algorithms")
            algorith_entered_by_user = int(input(">"))
            average_case_algorithms_interpreter(algorith_entered_by_user)
        elif option == "0":
            break


if __name__ == "__main__":
    main()
