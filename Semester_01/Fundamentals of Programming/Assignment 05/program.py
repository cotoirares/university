# 1. Read a list of complex numbers (in z = a + bi form) from the console.
# 2. Display the entire list of numbers on the console.
# 3. Display the length and elements of a longest increasing subsequence, when considering each number's modulus
# 4. Length and elements of a longest subarray of numbers having the same modulus.
# 5. Exit the application.

# Store the complex number both using list and dictionary

# Write the implementation for A5 in this file

# Author: Rares Cotoi, @ 912

def separation_function_of_the_real_part_and_imaginary_part_for_a_complex_number_entered_by_user(number_input) -> (
        int, int):
    NULL = 0
    MINIMUM_ASCII_FOR_DIGIT = '0'
    MAXIMUM_ASCII_FOR_DIGIT = '9'
    BASE = 10
    UNIT = 1
    real_part = NULL
    imaginary_part = NULL
    presence_of_operation = NULL
    for x in number_input:
        if MINIMUM_ASCII_FOR_DIGIT <= x <= MAXIMUM_ASCII_FOR_DIGIT:
            if presence_of_operation == NULL:
                real_part = real_part * BASE + int(x)
            else:
                imaginary_part = imaginary_part * BASE + int(x)
        elif x == '+' or x == '-':
            presence_of_operation = UNIT
        else:
            continue
    return real_part, imaginary_part


#
# Write below this comment 
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def initialize_a_list_for_representing_complex_numbers() -> list:
    list_of_complex_numbers = [(2, 3), (3, 5), (4, 1), (2, 7), (-1, 2), (2, -3), (5, 3), (12, 10), (10, -11), (0, 1)]
    return list_of_complex_numbers


def add_a_complex_number_to_the_list_of_complex_numbers(list_of_complex_numbers: list, real_part: int,
                                                        imaginary_part: int) -> list:
    list_of_complex_numbers.append((real_part, imaginary_part))
    return list_of_complex_numbers


#
# Write below this comment 
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

""""
def initialize_a_dictionary_to_memorize_complex_numbers() -> dict:
    dictionary_of_complex_numbers = {1: (2, 3), 2: (3, 5), 3: (4, 1), 4: (2, 7), 5: (-1, 2), 6: (2, -3), 7: (5, 3),
                                     8: (12, 10), 9: (10, -11), 10: (0, 1)}
    return dictionary_of_complex_numbers

def add_a_complex_number_to_the_dictionary_of_complex_numbers(dictionary_of_complex_numbers: dict, real_part: int,
                                                                imaginary_part: int):
    dictionary_of_complex_numbers[len(dictionary_of_complex_numbers) + 1] = (real_part, imaginary_part)
    return dictionary_of_complex_numbers
"""


#
# Write below this comment 
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

# 3. Display the length and elements of a longest increasing subsequence, when considering each complex number's modulus

def get_modulus_of_the_complex_numbers_using_the_list_representation(list_of_complex_numbers: list) -> list:
    list_of_modulus = []
    for i in range(len(list_of_complex_numbers)):
        modulus = (list_of_complex_numbers[i][0] ** 2 + list_of_complex_numbers[i][1] ** 2)
        list_of_modulus.append(modulus)
    return list_of_modulus


"""
def get_modulus_of_the_complex_numbers_using_the_dictionary_representation(list_of_complex_numbers: dict) -> dict:
    list_of_modulus = {}
    for i in range(len(list_of_complex_numbers)):
        modulus = (list_of_complex_numbers[i][0] ** 2 + list_of_complex_numbers[i][1] ** 2)
        list_of_modulus[i] = modulus
    return list_of_modulus
"""


def longest_increasing_subsequence_using_list_as_an_input(list_of_modulus: int) -> list:
    if len(list_of_modulus) == 0:
        print("The list is empty!")
        return

    index_of_the_previous_element_in_the_subsequence = [-1] * len(list_of_modulus)
    dynamic_programming_array_for_calculating_the_subsequence = [1] * len(list_of_modulus)
    for i in range(1, len(list_of_modulus)):
        for j in range(i):
            if list_of_modulus[i] > list_of_modulus[j]:
                dynamic_programming_array_for_calculating_the_subsequence[i] = max(
                    dynamic_programming_array_for_calculating_the_subsequence[i],
                    dynamic_programming_array_for_calculating_the_subsequence[
                        j] + 1)  # the length of the longest increasing subsequence ending in position i is the maximum between the length of the longest increasing subsequence ending in position i and the length of the longest increasing subsequence ending in position j + 1
                if dynamic_programming_array_for_calculating_the_subsequence[i] == \
                        dynamic_programming_array_for_calculating_the_subsequence[
                            j] + 1:  # if the length of the longest increasing subsequence ending in position i is equal to the length of the longest increasing subsequence ending in position j + 1
                    index_of_the_previous_element_in_the_subsequence[i] = j

    maximum_length_of_the_longest_increasing_subsequence = max(
        dynamic_programming_array_for_calculating_the_subsequence)  # the maxim length of the longest increasing subsequence

    subsequence = []
    for i in range(len(dynamic_programming_array_for_calculating_the_subsequence)):
        if dynamic_programming_array_for_calculating_the_subsequence[
            i] == maximum_length_of_the_longest_increasing_subsequence:  # if the length of the longest increasing subsequence ending in position i is equal to the maximum length of the longest increasing subsequence
            index = i
            break
    while index != -1:
        subsequence.append(list_of_modulus[index])  # add the number in position index to the subsequence
        index = index_of_the_previous_element_in_the_subsequence[
            index]  # go to the previous number in the longest increasing subsequence
    subsequence.reverse()  # reverse the subsequence because we added the numbers in the reverse order

    return maximum_length_of_the_longest_increasing_subsequence, subsequence


"""
def longest_increasing_subsequence_using_dictionary_as_an_input(list_of_modulus: dict) -> dict:
    if len(list_of_modulus) == 0:
        print("The list is empty!")
        return

    index_of_the_previous_element_in_the_subsequence = [-1]*len(list_of_modulus)
    dynamic_programming_array_for_calculating_the_subsequence = [1] * len(list_of_modulus)
    for i in range(1, len(list_of_modulus)):
        for j in range(i):
            if list_of_modulus[i] > list_of_modulus[j]:
                dynamic_programming_array_for_calculating_the_subsequence[i] = max(dynamic_programming_array_for_calculating_the_subsequence[i], dynamic_programming_array_for_calculating_the_subsequence[j] + 1) # the length of the longest increasing subsequence ending in position i is the maximum between the length of the longest increasing subsequence ending in position i and the length of the longest increasing subsequence ending in position j + 1
                if dynamic_programming_array_for_calculating_the_subsequence[i] == dynamic_programming_array_for_calculating_the_subsequence[j] + 1: # if the length of the longest increasing subsequence ending in position i is equal to the length of the longest increasing subsequence ending in position j + 1
                    index_of_the_previous_element_in_the_subsequence[i] = j

    maximum_length_of_the_longest_increasing_subsequence = max(dynamic_programming_array_for_calculating_the_subsequence) # the maxim length of the longest increasing subsequence
    subsequence = []
    for i in range(len(dynamic_programming_array_for_calculating_the_subsequence)):
        if dynamic_programming_array_for_calculating_the_subsequence[i] == maximum_length_of_the_longest_increasing_subsequence:
            index = i
            break
    while index != -1:
        subsequence.append(list_of_modulus[index])
        index = index_of_the_previous_element_in_the_subsequence[index]
    subsequence.reverse()

    return maximum_length_of_the_longest_increasing_subsequence, subsequence
"""


def longest_subarray_of_numbers_having_the_same_modulus_using_a_list_representation(list_of_modulus: list):
    if len(list_of_modulus) == 0:
        print("The list is empty!")
        return
    maximum_in_the_list = max(list_of_modulus)
    frequency_array = [0] * (maximum_in_the_list + 1)
    for i in range(len(list_of_modulus)):
        frequency_array[list_of_modulus[i]] += 1
    maximum_frequency = max(frequency_array)
    subarray_same_modulus = []
    for i in range(maximum_frequency):
        subarray_same_modulus.append(frequency_array.index(maximum_frequency))
    return maximum_frequency, subarray_same_modulus


"""
def longest_subarray_of_numbers_having_the_same_modulus_using_a_dictionary_representation(list_of_modulus: dict):
    if (len(list_of_modulus) == 0):
        print("The list is empty!")
        return
    maximum_in_the_list = max(list_of_modulus)
    frequency_array = [0] * (maximum_in_the_list + 1)
    for i in range(len(list_of_modulus)):
        frequency_array[list_of_modulus[i]] += 1
    maximum_frequency = max(frequency_array)
    subarray_same_modulus = []
    for i in range(maximum_frequency):
        subarray_same_modulus.append(frequency_array.index(maximum_frequency))
    return maximum_frequency, subarray_same_modulus
"""


#
# Write below this comment 
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities
#

def console_menu():
    READ_LIST_OF_COMPLEX_NUMBERS = '1'
    DISPLAY_THE_LIST_OF_COMPLEX_NUMBERS = '2'
    DISPLAY_THE_LENGTH_AND_ELEMENTS_OF_A_LONGEST_INCREASING_SUBSEQUENCE = '3'
    DISPLAY_THE_LENGTH_AND_ELEMENTS_OF_A_LONGEST_SUBARRAY_OF_NUMBERS_HAVING_THE_SAME_MODULUS = '4'
    EXIT_THE_APPLICATION = '5'
    print(f"{READ_LIST_OF_COMPLEX_NUMBERS}. Read a list of complex numbers (in z = a + bi form) from the console.")
    print(f"{DISPLAY_THE_LIST_OF_COMPLEX_NUMBERS}. Display the entire list of numbers on the console.")
    print(
        f"{DISPLAY_THE_LENGTH_AND_ELEMENTS_OF_A_LONGEST_INCREASING_SUBSEQUENCE}. Display the length and elements of a longest increasing subsequence, when considering each number's modulus")
    print(f"{DISPLAY_THE_LENGTH_AND_ELEMENTS_OF_A_LONGEST_SUBARRAY_OF_NUMBERS_HAVING_THE_SAME_MODULUS}. Length and elements of a longest subarray of numbers having the same modulus.")
    print(f"{EXIT_THE_APPLICATION}. Exit the application.")


def main():
    list_of_complex_numbers = initialize_a_list_for_representing_complex_numbers()
    READ_LIST_OF_COMPLEX_NUMBERS = '1'
    DISPLAY_THE_LIST_OF_COMPLEX_NUMBERS = '2'
    DISPLAY_THE_LENGTH_AND_ELEMENTS_OF_A_LONGEST_INCREASING_SUBSEQUENCE = '3'
    DISPLAY_THE_LENGTH_AND_ELEMENTS_OF_A_LONGEST_SUBARRAY_OF_NUMBERS_HAVING_THE_SAME_MODULUS = '4'
    EXIT_THE_APPLICATION = '5'

    while True:
        console_menu()
        command = input(">")

        if command == READ_LIST_OF_COMPLEX_NUMBERS:
            print("Enter the number of numbers you want to add")
            number_of_numbers = int(input(">"))
            for i in range(number_of_numbers):
                number_input = input("Enter a complex number: ")
                real_part, imaginary_part = separation_function_of_the_real_part_and_imaginary_part_for_a_complex_number_entered_by_user(
                    number_input)
                list_of_complex_numbers = add_a_complex_number_to_the_list_of_complex_numbers(list_of_complex_numbers,
                                                                                              real_part, imaginary_part)

        elif command == DISPLAY_THE_LIST_OF_COMPLEX_NUMBERS:
            print("The list of complex numbers is:")
            print(list_of_complex_numbers)

        elif command == DISPLAY_THE_LENGTH_AND_ELEMENTS_OF_A_LONGEST_INCREASING_SUBSEQUENCE:
            list_of_modulus = get_modulus_of_the_complex_numbers_using_the_list_representation(list_of_complex_numbers)
            length_of_the_longest_increasing_subsequence, list_of_longest_increasing_subsequence_of_modulus = longest_increasing_subsequence_using_list_as_an_input(
                list_of_modulus)
            print("The length of the longest increasing subsequence of modulus is:")
            print(length_of_the_longest_increasing_subsequence)
            print("The elements of the longest increasing subsequence of modulus are:")
            print(list_of_longest_increasing_subsequence_of_modulus)

        elif command == DISPLAY_THE_LENGTH_AND_ELEMENTS_OF_A_LONGEST_SUBARRAY_OF_NUMBERS_HAVING_THE_SAME_MODULUS:
            list_of_modulus = get_modulus_of_the_complex_numbers_using_the_list_representation(list_of_complex_numbers)
            length_of_the_longest_subarray, longest_subarray = longest_subarray_of_numbers_having_the_same_modulus_using_a_list_representation(
                list_of_modulus)
            print("The length of the longest subarray of numbers having the same modulus is:")
            print(length_of_the_longest_subarray)
            print("The elements of the longest subarray of numbers having the same modulus are:")
            print(longest_subarray)

        elif command == EXIT_THE_APPLICATION:
            break
        else:
            print("Invalid command")


if __name__ == "__main__":
    main()
