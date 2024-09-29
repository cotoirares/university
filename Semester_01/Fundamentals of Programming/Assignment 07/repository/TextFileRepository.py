import os
from src.domain.DomainExpenses import Expense
from src.repository.MemoryRepository import MemoryRepository


class TextFileRepository(MemoryRepository):
    """
    This class stores the expenses in a text file.
    """
    def __init__(self, path_file):
        super().__init__()
        self.__path_file = path_file
        self._load_expense()

    def _load_expense(self):
        """
        This function loads the expenses from the text file.
        :return:
        """
        if not os.path.exists(self.__path_file):
            return []
        with open(self.__path_file, "r") as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line == "":
                    continue
                tokens = line.split(";")
                self.add(Expense(int(tokens[0]), int(tokens[1]), tokens[2]), False)
    def _save_expense(self):
        """
        This function saves the expenses in the text file.
        :return:
        """
        with open(self.__path_file, "w") as f:
            for expense in self.get_all():
                f.write(f"{expense.day};{expense.amount};{expense.type}\n")
    def add(self, new_expense: Expense, undo_state: bool = False):
        """
        This function adds an expense to the repository.
        :param new_expense:
        :param undo_state:
        :return:
        """
        super().add(new_expense, undo_state)
        self._save_expense()
    def filter(self, given_amount):
        """
        This function filters the expenses from the repository.
        :param given_amount:
        :return:
        """
        super().filter(given_amount)
        self._save_expense()
    def undo(self):
        """
        This function undoes the last operation that modified program data.
        :return:
        """
        super().undo()
        self._save_expense()