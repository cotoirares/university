"""
The sequence a1, ..., an of distinct integer numbers is given. Display all subsets with a mountain aspect. A set has a mountain aspect if the elements increase up to a point and then they decrease. E.g. 10, 16, 27, 18, 14, 7

Author: Rares Cotoi, @ 912
"""

def backtracking_generator_for_candidate_solutions_as_increasing_then_decreasing_sequences\
                (array_input_passed_by_user: list, backtracking_candidate_solution: list,
                 current_subset_is_decreasing: bool) -> None:

    if len(backtracking_candidate_solution) == len(array_input_passed_by_user):
        if current_subset_is_decreasing:
            print(backtracking_candidate_solution)
        return

    for number in array_input_passed_by_user:
        # check if the number is already in the current subset
        if number in backtracking_candidate_solution:
            continue
        # checking if the sequence always starts with an increasing sequence
        if len(backtracking_candidate_solution) == 0:
            backtracking_candidate_solution.append(number)
            backtracking_generator_for_candidate_solutions_as_increasing_then_decreasing_sequences(
                array_input_passed_by_user, backtracking_candidate_solution, False)
            backtracking_candidate_solution.pop()
        else:

            if current_subset_is_decreasing:
                if number < backtracking_candidate_solution[-1]: # check if the number is smaller than the last element in the current subset
                    backtracking_candidate_solution.append(number)
                    backtracking_generator_for_candidate_solutions_as_increasing_then_decreasing_sequences(
                        array_input_passed_by_user, backtracking_candidate_solution, True)
                    backtracking_candidate_solution.pop()

            else: # current subset is increasing
                if number > backtracking_candidate_solution[-1]:
                    backtracking_candidate_solution.append(number)
                    backtracking_generator_for_candidate_solutions_as_increasing_then_decreasing_sequences(
                        array_input_passed_by_user, backtracking_candidate_solution, False)
                    if number == max(array_input_passed_by_user) and len(backtracking_candidate_solution) < len(array_input_passed_by_user):    backtracking_generator_for_candidate_solutions_as_increasing_then_decreasing_sequences(
                            array_input_passed_by_user, backtracking_candidate_solution, True)
                    backtracking_candidate_solution.pop()

def main():
    array_input_passed_by_user = input("Enter the initial array: ").split()
    array_input_passed_by_user = [int(x) for x in array_input_passed_by_user]
    backtracking_candidate_solution = []
    print("The mountain sequences are: ")
    backtracking_generator_for_candidate_solutions_as_increasing_then_decreasing_sequences(
        array_input_passed_by_user, backtracking_candidate_solution, False)


if __name__ == "__main__":
    main()