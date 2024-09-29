import pickle
import os
from src.repository.MemoryRepository import MemoryRepository


class BinaryRepository(MemoryRepository):
    # this class stores the expenses in a binary file

    def __init__(self, path_file):
        super().__init__()
        self.__path_file = path_file
        self.load_expense()

    def filename(self):
        return self.__path_file
    def load_expense(self):
        # this function loads the expenses from the binary file

        if not os.path.exists(self.__path_file):
            return
        with open(self.__path_file, "rb") as f:
            try:
                while True:
                    expenses_new = pickle.load(f)
                    if isinstance(expenses_new, list):
                        self._expenses.extend(expenses_new)
                    else:
                        self._expenses.append(expenses_new)
            except EOFError:
                pass

    def _save_expense(self):
        # This function saves the expenses in the binary file
        with open(self.__path_file, "wb") as f:
            pickle.dump(self._expenses, f)

    def add(self, new_expense, undo_state: bool = False):
        # this function adds an expense to the repository

        super().add(new_expense, undo_state)
        self._save_expense()

    def filter(self, given_amount):
        # this function filters the expenses from the repository

        super().filter(given_amount)
        self._save_expense()

    def undo(self):
        # this function undoes the last operation that modified program data

        super().undo()
        self._save_expense()
