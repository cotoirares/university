"""
During a programming contest, each contestant had to solve 3 problems (named P1, P2 and P3). Afterwards, an evaluation committee graded the solutions to each of the problems using integers between 0 and 10. The committee needs a program that will allow managing the list of scores and establishing the winners. Write a program that implements the functionalities exemplified below:

(A) Add the result of a new participant
add <P1 score> <P2 score> <P3 score>
insert <P1 score> <P2 score> <P3 score> at <position>

(B) Modify scores
remove <position>
remove <start position> to <end position>
replace <old score> <P1 | P2 | P3> with <new score>

(C) Display participants whose score has different properties.
list
list sorted
list [ < | = | > ] <score>

(D) Establish the podium
top <number>
top <number> <P1 | P2 | P3>
remove [ < | = | > ] <score>

(E) Undo
undo – the last operation that modified program data is reversed. The user can undo all operations performed since program start by repeatedly calling this function.

Modules: UI - User Interface | functions - Functionalities

Author: Rares Cotoi, @ 912
"""
import src.ui as ui
import src.functions as functions


def main():
    list_of_scores = functions.initialize_list_of_scores()
    the_stack = functions.initialize_the_stack()
    while True:
        ui.menu_implementation()
        user_input = ui.get_command()
        try:
            functions.handling_command_input(list_of_scores, user_input, the_stack)
        except ValueError as ve:
            print(ve)


main()

