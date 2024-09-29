from unittest import TestCase
from src.domain.Discipline_init import Discipline
from src.repository.Memory_Repository import MemoryRepository
from src.services.Discipline_service import DisciplineService


class TestingDiscipline(TestCase):
    def setUp(self):
        self.__d = Discipline("1", "Mate")

    def tearDown(self):
        pass

    def testing_existing_discipline_more_than_4_characters(self):
        assert self.__d.name == "Mate"
        self.assertEqual(self.__d.name, "Mate", "Test failed!")

    def testing_existing_discipline_ID_more_than_1000(self):
        assert self.__d.id == "1"
        self.assertEqual(self.__d.id, "1", "Test failed!")


class TestingDiscipline_Addition(TestCase):
    def setUp(self):
        self.__d = DisciplineService(MemoryRepository())

    def tearDown(self):
        pass

    def testing_adding_new_discipline_name_more_than_4_characters(self):
        self.__d.add_discipline(Discipline("1", "Mate"))
        self.assertEqual(len(self.__d.list_disciplines()), 11, "Test failed!")

    def testing_adding_new_discipline_ID_more_than_1000(self):
        self.__d.add_discipline(Discipline("2", "Romana"))
        self.assertEqual(len(self.__d.list_disciplines()), 11, "Test failed!")


class TestingDiscipline_Update(TestCase):
    def setUp(self):
        self.__d = DisciplineService(MemoryRepository())

    def tearDown(self):
        pass

    def testing_discipline_update_name_more_than_4_characters(self):
        self.__d.add_discipline(Discipline("1", "Mate"))
        self.__d.update_discipline("1", "Romana")
        self.assertEqual(len(self.__d.list_disciplines()), 11, "Test failed!")

    def testing_discipline_update_ID_more_than_1000(self):
        self.__d.add_discipline(Discipline("2", "Romana"))
        self.__d.update_discipline("2", "Mate")
        self.assertEqual(len(self.__d.list_disciplines()), 11, "Test failed!")

