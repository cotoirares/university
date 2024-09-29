"""
Manage a list of expenses. Each expense has a day (integer between 1 and 30), amount of money (positive integer) and expense type (string). Provide the following features:

Add an expense. Expense data is read from the console.
Display the list of expenses.
Filter the list so that it contains only expenses above a certain value read from the console.
Undo the last operation that modified program data. This step can be repeated. The user can undo only those operations made during the current run of the program.

Author: Rares Cotoi, @ 912
"""

from src.repository.BinaryRepository import BinaryRepository
from src.repository.MemoryRepository import MemoryRepository
from src.repository.TextFileRepository import TextFileRepository
from src.ui.UserInterface import UI

def get_repo():
    # this function reads the repository type from the settings file and returns the repository.
    with open("Settings.properties", "r") as settings_file:
        for input_line in settings_file:
            input_line = input_line.strip()
            if input_line.startswith("REPOSITORY="):
                repository_type = input_line[len("REPOSITORY="):]
                if repository_type == "memory":
                    return MemoryRepository()
                elif repository_type == "text":
                    return TextFileRepository("ExpensesList.txt")
                elif repository_type == "binary":
                    return BinaryRepository("expenses.data")
                else:
                    raise ValueError("Invalid repository type!")
            else:
                raise ValueError("Invalid settings file!")


if __name__ == "__main__":
    repository = get_repo()
    ui = UI(repository)
    ui.run()
