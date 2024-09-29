from src.domain.DomainExpenses import Expense
from random import randint,choice

class Functions:
    # this class implements the functions of the program

    def __init__(self,chosen_repo):
        self.__repo = chosen_repo
        if len(self.__repo.get_all())<10:
            self.add_starting()

    def add_starting(self):

        for i in range(10):
            day = randint(1,30)
            amount = randint(100,500)
            type = choice(("gas","water","electricity","heating","other"))
            if Expense(day,amount,type) not in self.__repo.get_all():
                self.add(day,amount,type,False)
            else:
                i -= 1


    def get_all(self):
        # this function returns all the expenses from the repository
        return self.__repo.get_all()

    def add(self,expense_day,expense_amount,expense_type,undo_state: bool = True,):
        # this function adds an expense to the repository

        expense = Expense(expense_day, expense_amount, expense_type)
        self.__repo.add(expense, undo_state)

    def filter(self,given_amount):
        # this function filters the expenses from the repository
        return self.__repo.filter(given_amount)

    def undo(self):
        # this function undoes the last operation that modified program data

        return self.__repo.undo()
