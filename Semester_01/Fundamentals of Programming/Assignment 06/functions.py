#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions. 
#
import copy

first_word_in_the_command = 0
empty_value = 0
UNIT = 1
average_score_for_participant = 0
upper_limit_for_sorting = 1
number_of_words_to_establish_podium_by_number_of_places = 2
number_of_words_to_establish_podium_by_problem = 3
number_of_words_for_adding_score_at_the_end = 4
number_of_words_for_adding_score_at_a_certain_position = 6
new_score_for_problem_one = 1
new_score_for_problem_two = 2
new_score_for_problem_three = 3
position_to_insert_the_new_score = 5

def initialize_list_of_scores() -> list:
    # creates a list of scores with the default value of 0
    return []


def initialize_the_stack() -> list:
    return []


def handling_command_input(general_list_of_scores_for_participants: list, initial_user_input_as_string: str, the_stack_of_last_performed_operations: list):
    # handles the input from the user
    words_in_the_command = initial_user_input_as_string.split()
    if words_in_the_command[first_word_in_the_command] == "add" or words_in_the_command[first_word_in_the_command] == "insert":
        try:
            return add_new_score(general_list_of_scores_for_participants, words_in_the_command, the_stack_of_last_performed_operations)
        except ValueError as ve:
            print(ve)
    elif words_in_the_command[first_word_in_the_command] == "remove" and len(words_in_the_command) in [2, 4]:
        try:
            return remove_score(general_list_of_scores_for_participants, words_in_the_command, the_stack_of_last_performed_operations)
        except ValueError as ve:
            print(ve)
    elif words_in_the_command[first_word_in_the_command] == "replace":
        try:
            return replace_score(general_list_of_scores_for_participants, words_in_the_command, the_stack_of_last_performed_operations)
        except ValueError as ve:
            print(ve)
    elif words_in_the_command[first_word_in_the_command] == "list":
        try:
            return list_scores(general_list_of_scores_for_participants, words_in_the_command)
        except ValueError as ve:
            print(ve)
    elif words_in_the_command[first_word_in_the_command] == "top":
        try:
            return top_scores(general_list_of_scores_for_participants, words_in_the_command)
        except ValueError as ve:
            print(ve)
    elif words_in_the_command[first_word_in_the_command] == "remove" and len(words_in_the_command) == 3:
        try:
           general_list_of_scores_for_participants = remove_scores_by_certain_value(general_list_of_scores_for_participants, words_in_the_command, the_stack_of_last_performed_operations)
        except ValueError as ve:
            print(ve)
    elif words_in_the_command[first_word_in_the_command] == "undo" and len(words_in_the_command) == 1:
        try:
            general_list_of_scores_for_participants = undo_last_command(general_list_of_scores_for_participants, the_stack_of_last_performed_operations)
        except ValueError as ve:
            print(ve)
    elif words_in_the_command[first_word_in_the_command] == "exit":
        exit()
    else:
        raise ValueError("Invalid command!")


def create_dictionary_for_new_scores(P1: int, P2: int, P3: int) -> dict:
    # creates a dictionary for the new scores
    return {"P1": P1, "P2": P2, "P3": P3}


def add_new_score(list_of_scores: list, words_in_the_command: list, the_stack_of_last_performed_operations: list):
    if len(words_in_the_command) == number_of_words_for_adding_score_at_the_end:
        new_results_to_be_added = create_dictionary_for_new_scores(int(words_in_the_command[new_score_for_problem_one]),
                                                                   int(words_in_the_command[new_score_for_problem_two]),
                                                                   int(words_in_the_command[new_score_for_problem_three]))
        list_to_append = copy.deepcopy(list_of_scores)
        the_stack_of_last_performed_operations.append(list_to_append)
        list_of_scores.append(new_results_to_be_added)
    elif len(words_in_the_command) == number_of_words_for_adding_score_at_a_certain_position:
        new_results_to_be_added = create_dictionary_for_new_scores(int(words_in_the_command[new_score_for_problem_one]),
                                                                   int(words_in_the_command[new_score_for_problem_two]),
                                                                   int(words_in_the_command[new_score_for_problem_three]))
        list_to_append = copy.deepcopy(list_of_scores)
        the_stack_of_last_performed_operations.append(list_to_append)
        list_of_scores.insert(int(words_in_the_command[position_to_insert_the_new_score]), new_results_to_be_added)
    else:
        raise ValueError("Invalid command!")


def remove_score(list_of_scores: list, words_in_the_command: list, the_stack_of_last_performed_operations:list):
    # removes a score from the list of scores
    if len(words_in_the_command) == 2:
        list_to_append = copy.deepcopy(list_of_scores)
        the_stack_of_last_performed_operations.append(list_to_append)
        list_of_scores[int(words_in_the_command[1])] = {"P1": empty_value, "P2": empty_value, "P3": empty_value}
    elif len(words_in_the_command) == 4:
        list_to_append = copy.deepcopy(list_of_scores)
        the_stack_of_last_performed_operations.append(list_to_append)
        for index in range(int(words_in_the_command[1]), int(words_in_the_command[3]) + 1):
            list_of_scores[index] = {"P1": empty_value, "P2": empty_value, "P3": empty_value}
    else:
        raise ValueError("Invalid command!")


def replace_score(list_of_scores: list, words_in_the_command: list, the_stack_of_last_performed_operations:list):
    # replaces a score from the list of scores
    if len(words_in_the_command) == 5:
        list_to_append = copy.deepcopy(list_of_scores)
        the_stack_of_last_performed_operations.append(list_to_append)
        list_of_scores[int(words_in_the_command[1])][words_in_the_command[2]] = int(words_in_the_command[4])
    else:
        raise ValueError("Invalid command!")


def print_scores_for_all_participants(list_of_scores: list):
    for index in range(len(list_of_scores)):
        print(f"Participant {index}: {list_of_scores[index]}")


def get_list_of_averages(list_of_scores: list):
    list_of_averages = []
    for index in range(len(list_of_scores)):
        list_of_averages.append((list_of_scores[index]["P1"] + list_of_scores[index]["P2"] + list_of_scores[index]["P3"]) / 3)
    return list_of_averages


def get_list_of_averages_with_initial_index(list_of_scores: list):
    list_of_averages = []
    for index in range(len(list_of_scores)):
        list_of_averages.append(((list_of_scores[index]["P1"] + list_of_scores[index]["P2"] + list_of_scores[index]["P3"]) / 3, index))
    return list_of_averages


def print_scores_for_participants_sorted_decreasing_by_average(list_of_scores: list):
    list_of_averages = get_list_of_averages_with_initial_index(list_of_scores)
    # sort list_of_averages by the first element in each tuple
    list_of_averages.sort(key=lambda x: x[average_score_for_participant], reverse=True)
    for index in range(len(list_of_averages)):
        print(f"Participant {list_of_averages[index][1]}: {list_of_scores[list_of_averages[index][1]]}")


def print_scores_for_participants_with_pivot_property(list_of_scores: list, words_in_the_command: list):
    list_of_averages = get_list_of_averages(list_of_scores)
    for index in range(len(list_of_averages)):
        if words_in_the_command[1] == "<" and list_of_averages[index] < int(words_in_the_command[2]):
            print(f"Participant {index}: {list_of_scores[index]}")
        elif words_in_the_command[1] == "=" and list_of_averages[index] == int(words_in_the_command[2]):
            print(f"Participant {index}: {list_of_scores[index]}")
        elif words_in_the_command[1] == ">" and list_of_averages[index] > int(words_in_the_command[2]):
            print(f"Participant {index}: {list_of_scores[index]}")


def list_scores(list_of_scores: list, words_in_the_command: list):
    # prints the list of scores

    if len(words_in_the_command) == 1:
        print_scores_for_all_participants(list_of_scores)
    elif len(words_in_the_command) == 2 and words_in_the_command[1] == "sorted":
        print_scores_for_participants_sorted_decreasing_by_average(list_of_scores)
    elif len(words_in_the_command) == 3 and words_in_the_command[2].isdigit():
        print_scores_for_participants_with_pivot_property(list_of_scores, words_in_the_command)
    else:
        raise ValueError("Invalid command!")


def top_scores_by_number_of_places(list_of_scores:list, words_in_the_command:list):
    index_to_stop = int(words_in_the_command[1])
    list_of_averages = get_list_of_averages_with_initial_index(list_of_scores)
    list_of_averages.sort(key=lambda x: x[average_score_for_participant], reverse=True)
    place = 1
    for index in range(index_to_stop):
        print(f"Place {place}: Participant {list_of_averages[index][1]} with an average of {list_of_averages[index][average_score_for_participant]}")
        place += 1


def top_scores_by_problem(list_of_scores:list, words_in_the_command:list):
    index_to_stop = int(words_in_the_command[upper_limit_for_sorting])
    problem = words_in_the_command[2]
    copy_list_of_scores = list_of_scores.copy()
    copy_list_of_scores.sort(key=lambda x: x[problem], reverse=True)
    place = 1
    for index in range(index_to_stop):
        for index2 in range(len(list_of_scores)):
            if list_of_scores[index2][problem] == copy_list_of_scores[index][problem]:
                print(f"Place {place}: Participant {index2} - {copy_list_of_scores[index][problem]}")
        place += 1


def remove_scores_by_certain_value(list_of_scores:list, words_in_the_command:list, the_stack_of_last_performed_operations:list) -> list:
    if words_in_the_command[1] == "<":
        list_to_append = copy.deepcopy(list_of_scores)
        the_stack_of_last_performed_operations.append(list_to_append)
        for index in range(len(list_of_scores)):
            if (list_of_scores[index]["P1"] + list_of_scores[index]["P2"] + list_of_scores[index]["P3"]) / 3 < int(words_in_the_command[2]):
                list_of_scores[index]["P1"] = empty_value
                list_of_scores[index]["P2"] = empty_value
                list_of_scores[index]["P3"] = empty_value
    elif words_in_the_command[1] == "=":
        list_to_append = copy.deepcopy(list_of_scores)
        the_stack_of_last_performed_operations.append(list_to_append)
        for index in range(len(list_of_scores)):
            if (list_of_scores[index]["P1"] + list_of_scores[index]["P2"] + list_of_scores[index]["P3"]) / 3 == int(words_in_the_command[2]):
                list_of_scores[index]["P1"] = empty_value
                list_of_scores[index]["P2"] = empty_value
                list_of_scores[index]["P3"] = empty_value
    elif words_in_the_command[1] == ">":
        list_to_append = copy.deepcopy(list_of_scores)
        the_stack_of_last_performed_operations.append(list_to_append)
        for index in range(len(list_of_scores)):
            if (list_of_scores[index]["P1"] + list_of_scores[index]["P2"] + list_of_scores[index]["P3"]) / 3 > int(words_in_the_command[2]):
                list_of_scores[index]["P1"] = empty_value
                list_of_scores[index]["P2"] = empty_value
                list_of_scores[index]["P3"] = empty_value
    else:
        raise ValueError("Invalid command!")
    return list_of_scores


def top_scores(list_of_scores:list, words_in_the_command:list):
    if len(words_in_the_command) == number_of_words_to_establish_podium_by_number_of_places:
        top_scores_by_number_of_places(list_of_scores, words_in_the_command)
    elif len(words_in_the_command) == number_of_words_to_establish_podium_by_problem:
        top_scores_by_problem(list_of_scores, words_in_the_command)
    else:
        raise ValueError("Invalid command!")


def undo_last_command(list_of_scores:list, the_stack_of_last_performed_operations:list):
    if len(the_stack_of_last_performed_operations) == empty_value:
        raise ValueError("No more undos!")
    else:
        list_of_scores.clear()
        copy_list = the_stack_of_last_performed_operations.pop()
        for index in range(len(copy_list)):
            list_of_scores.append(copy_list[index])
        return list_of_scores