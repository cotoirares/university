from src.services.Services import Functions
from src.repository.MemoryRepository import MemoryRepository


class Test:
    # this class tests the functions from the service module.

    def __init__(self, repository) -> None:
        self.expense_service = Functions(repository)

    def test_add_expense(self):
        # tests the add method from the service module.

        expense_data = self.expense_service.get_all()
        count = len(expense_data)
        self.expense_service.add(1, 100, "gas")
        assert len(self.expense_service.get_all()) == count + 1

        self.expense_service.add(3, 300, "heating")
        assert len(self.expense_service.get_all()) == count + 2

        try:
            self.expense_service.add(3, 300, "heating")
        except Exception:
            assert True
        assert len(self.expense_service.get_all()) == count + 2

    def test_filter_expenses_by_amount(self):
        # tests the filter method from the service module.

        self.expense_service.filter(1000)
        assert len(self.expense_service.get_all()) == 0

        self.expense_service.add(9, 150, "water")
        self.expense_service.add(22, 500, "electricity")
        self.expense_service.add(27, 270, "other")

        assert len(self.expense_service.get_all()) == 3

        self.expense_service.filter(100)
        assert len(self.expense_service.get_all()) == 3

        self.expense_service.filter(400)
        assert len(self.expense_service.get_all()) == 1

    def test_undo_last_operation(self):
        # tests the undo method from the service module.
        initial_expense_data = self.expense_service.get_all()
        self.expense_service.add(5, 180, "heating")
        self.expense_service.add(22, 200, "water")

        assert (
            len(self.expense_service.get_all())
            == len(initial_expense_data) + 2
        )

        self.expense_service.undo()
        assert (
            len(self.expense_service.get_all())
            == len(initial_expense_data) + 1
        )

        self.expense_service.undo()
        assert len(self.expense_service.get_all()) == len(initial_expense_data)

    def run(self):
        self.test_add_expense()
        self.test_filter_expenses_by_amount()
        self.test_undo_last_operation()

test1 = Test(MemoryRepository())
test1.run()