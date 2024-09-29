from src.repository.MemoryRepository import RepositoryException
from src.services.Services import Functions

exit_input = 5

class UI:
    def __init__(self, chosen_repo):
        self._expense_service = Functions(chosen_repo)

    def __print_menu(self):
        print("1. Add expense")
        print("2. Display expenses")
        print("3. Filter expenses")
        print("4. Undo")
        print("5. Exit")

    def __add(self):
        day = int(input("Day: "))
        amount = int(input("Amount: "))
        type = input("Type: ")
        if not isinstance(day, int) or not isinstance(amount, int):
            print("Invalid input!")
        else:
            try:
                self._expense_service.add(day, amount, type)
            except RepositoryException as ValueError:
                print(ValueError)

    def __display(self):
        if not self._expense_service.get_all():
            print("No expenses!")
            return
        for expense in self._expense_service.get_all():
            print(expense)

    def __filter(self):
        given_amount = int(input("Amount: "))
        try:
            self._expense_service.filter(given_amount)
        except RepositoryException as ValueError:
            print(ValueError)

    def __undo(self):
        self._expense_service.undo()

    def run(self):
        commands = {
            "1": self.__add,
            "2": self.__display,
            "3": self.__filter,
            "4": self.__undo
        }
        while True:
            self.__print_menu()
            command = input("Enter command: ")
            if command == str(exit_input):
                return
            if command in commands:
                try:
                    commands[command]()
                except RepositoryException as ValueError:
                    print(ValueError)
            else:
                print("Invalid command!")

