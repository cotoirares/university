from src.domain.DomainExpenses import Expense

class RepositoryException(Exception):
    # this class implements the exceptions for the repository

    def __init__(self,message):
        super().__init__(message)

class MemoryRepository:
    # this class stores expenses in memory

    def __init__(self):
        self._expenses = []
        self.__history = []
    def _save_history(self):
        """
        This function saves the current state of the repository.
        :return:
        """
        self.__history.append(self._expenses.copy())
    def add(self,new_expense: Expense,undo_state: bool = False):
        # this function adds an expense to the repository

        if new_expense.day < 1 or new_expense.day > 30:
            raise RepositoryException("Invalid day!")
        elif new_expense.amount < 0:
            raise RepositoryException("Invalid amount!")
        elif new_expense.type == "":
            raise RepositoryException("Invalid type!")
        elif new_expense in self._expenses:
            raise RepositoryException("Expense already exists!")
        elif undo_state:
            self._save_history()
        self._expenses.append(new_expense)
    def get_all(self):
        """
        This function returns all the expenses from the repository.
        :return:
        """
        return self._expenses.copy()
    def filter(self,given_amount:int):
        """
        This function filters the expenses from the repository.
        :param given_amount:
        :return:
        """
        if given_amount < 0:
            raise RepositoryException("Invalid amount!")
        self._save_history()
        self._expenses = [expense for expense in self._expenses if expense.amount > given_amount]
    def undo(self):
        """
        This function undoes the last operation that modified program data.
        :return:
        """
        if len(self.__history) == 0:
            raise RepositoryException("No more undo!")
        self._expenses = self.__history.pop()