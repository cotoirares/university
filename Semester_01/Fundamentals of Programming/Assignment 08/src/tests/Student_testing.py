from unittest import TestCase
from src.domain.Student_init import Student
from src.repository.Memory_Repository import MemoryRepository
from src.services.Student_service import StudentService


class TestingStudentInputValidity(TestCase):
    def setUp(self):
        self.__s = Student("1","Ana")
    def tearDown(self):
        pass
    def testing_student_name_more_than_3_charachters_long(self):
        assert self.__s.name == "Ana"
        self.assertEqual(self.__s.name,"Ana","Test failed!")
    def testing_student_ID_more_than_100(self):
        assert self.__s.id == "1"
        self.assertEqual(self.__s.id,"1","Test failed!")


class TestingStudentAddition(TestCase):
    def setUp(self):
        self.__s = StudentService(MemoryRepository())
    def tearDown(self):
        pass
    def testing_student_addition_name_more_than_3_characters(self):
        self.__s.add_student(Student("1","Ana"))
        self.assertEqual(len(self.__s.list_students()),11,"Test failed!")
    def testing_student_addition_id_more_than_100(self):
        self.__s.add_student(Student("2","Maria"))
        self.assertEqual(len(self.__s.list_students()),11,"Test failed!")


class TestingStudentUpdate(TestCase):
    def setUp(self):
        self.__s = StudentService(MemoryRepository())
    def tearDown(self):
        pass
    def testing_student_update_name_more_than_3_characters(self):
        self.__s.add_student(Student("1","Ana"))
        self.__s.update_student("1","Maria")
        self.assertEqual(len(self.__s.list_students()),11,"Test failed!")
    def testing_student_update_id_more_than_100(self):
        self.__s.add_student(Student("2","Maria"))
        self.__s.update_student("2","Ana")
        self.assertEqual(len(self.__s.list_students()),11,"Test failed!")
