"""
Visualisation of Bubble Sort & Strand Sort

Author: Cotoi Rares, @912
"""

from random import randint


def display_menu():
    print("1. Generate a list of numbers")
    print("2. Sort the list using bubble sort")
    print("3. Sort the list using strand sort")
    print("0. Exit the program")


def numbers_generator() -> list:
    print("Enter the number of numbers you want to generate")
    number_of_numbers = input()
    try:
        number_of_numbers = int(number_of_numbers)
    except ValueError:
        print("Invalid input!")
    list_of_numbers = []
    for index in range(0, number_of_numbers):
        current_number = randint(0, 100)
        list_of_numbers.append(current_number)
    return list_of_numbers


def bubble_sort(list_of_numbers: list[int], given_step: int) -> list:
    sorted = False
    length_of_list = len(list_of_numbers)
    steps_made = 0
    while not sorted:
        sorted = True
        for index in range(0, length_of_list - 1):
            if list_of_numbers[index] > list_of_numbers[index + 1]:
                sorted = False
                auxiliary_for_interchange = list_of_numbers[index]
                list_of_numbers[index] = list_of_numbers[index + 1]
                list_of_numbers[index + 1] = auxiliary_for_interchange
                steps_made += 1
                if steps_made % given_step == 0:
                    print(f"The array at step {steps_made}: {list_of_numbers}")
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


def strand_sort(list_of_numbers: list[int], given_step: int, steps_made: int) -> list[int]:
    if not list_of_numbers:
        return []
    steps_made += 1
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
    if steps_made % given_step == 0:
        print(f"At step {steps_made}, Sublist: {sublist}, Remaining array: {list_of_numbers}")
    return merge(strand_sort(list_of_numbers, given_step, steps_made), sublist)


def main():
    while True:
        display_menu()
        option = input(">")
        if option == "1":
            list_of_numbers = numbers_generator()
            print(list_of_numbers)
        elif option == "2":  # sorting using bubble sort
            step = int(input("Enter the step: "))
            list_of_numbers_copy = list_of_numbers.copy()
            list_of_numbers_copy = bubble_sort(list_of_numbers_copy, step)
            print(f"The sorted array is: {list_of_numbers_copy}")
        elif option == "3":  # sorting using strand sort
            step = int(input("Enter the step: "))
            output = strand_sort(list_of_numbers, step, 1)
            print(f"The sorted array is: {output}")
        else:
            break


if __name__ == "__main__":
    main()
