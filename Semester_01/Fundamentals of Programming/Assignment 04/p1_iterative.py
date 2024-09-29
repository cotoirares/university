"""
The sequence a1, ..., an of distinct integer numbers is given. Display all subsets with a mountain aspect. A set has a mountain aspect if the elements increase up to a point and then they decrease. E.g. 10, 16, 27, 18, 14, 7

Author: Rares Cotoi, @ 912
"""

def backtracking_iterative_generator_for_candidate_solutions_as_increasing_then_decreasing_sequences(
        array_input_passed_by_user: list) -> None:
    the_stack = [([], False)]
    while len(the_stack) > 0:
        backtracking_candidate_solution, current_subset_is_decreasing = the_stack.pop()
        if len(backtracking_candidate_solution) == len(array_input_passed_by_user):
            if current_subset_is_decreasing:
                print(backtracking_candidate_solution)
        else:
            for number in array_input_passed_by_user:
                if number in backtracking_candidate_solution:
                    continue
                if len(backtracking_candidate_solution) == 0:
                    backtracking_candidate_solution.append(number)
                    the_stack.append((backtracking_candidate_solution.copy(), False))
                    backtracking_candidate_solution.pop()
                else:
                    if current_subset_is_decreasing:
                        if number < backtracking_candidate_solution[-1]:
                            backtracking_candidate_solution.append(number)
                            the_stack.append((backtracking_candidate_solution.copy(), True))
                            backtracking_candidate_solution.pop()
                    else:
                        if number > backtracking_candidate_solution[-1]:
                            backtracking_candidate_solution.append(number)
                            the_stack.append((backtracking_candidate_solution.copy(), False))
                            if number == max(array_input_passed_by_user) and len(backtracking_candidate_solution) < len(array_input_passed_by_user):
                                the_stack.append((backtracking_candidate_solution.copy(), True))
                            backtracking_candidate_solution.pop()


def main():
    array_input_passed_by_user = input("Enter the initial array: ").split()
    array_input_passed_by_user = [int(x) for x in array_input_passed_by_user]
    backtracking_iterative_generator_for_candidate_solutions_as_increasing_then_decreasing_sequences(
        array_input_passed_by_user)


if __name__ == "__main__":
    main()
