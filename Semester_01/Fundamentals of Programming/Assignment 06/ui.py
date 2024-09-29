#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements) are found here
#
def menu_implementation():
    """
    Prints the menu
    """
    print("\nThis is a system for managing the scores of participants in a programming contest. Enter your command as stated below:\n")
    print("add or insert - Add the result of a new participant")
    print("remove or replace - Modify scores")
    print("list or list sorted - Display participants whose score has different properties")
    print("top - Establish the podium")
    print("undo - Undo the last operation that modified program data")
    print("exit - Exit\n")


def get_command() -> str:
    """
    Reads a command from the keyboard and returns it as a string
    """
    return input("Enter your command: ")
