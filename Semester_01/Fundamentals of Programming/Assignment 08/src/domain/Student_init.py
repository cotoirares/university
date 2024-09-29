from random import choice
from src.domain.ID_init import IdObject

MINIMUM_NAME_LENGTH = 3
MINIMUM_INDEX_FOR_IDs = 100

class Student(IdObject):
    def __init__(self, id, name: str):
        super().__init__(id)
        if len(name) < MINIMUM_NAME_LENGTH:
            raise TypeError("The name must be at least 3 characters long!")
        else:
            self.__name = name

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, new_name):
        self.__name = new_name

    def __str__(self):
        return "ID: " + str(self.id) + " Student name: " + self.name

    def __eq__(self, other):
        return isinstance(other, Student) and self.id == other.id

    def __copy__(self):
        return Student(self.id, self.name)

    def __hash__(self):
        return hash(self.id)


def students_generator(n):
    list_of_generated_students = []
    starting_index_for_IDs = MINIMUM_INDEX_FOR_IDs
    list_of_names_for_students = ["Alex", "David", "George", "Mihai", "Marius", "Andrei", "Cristi", "Cristina", "Maria", "Ioana", "Ana", "Andreea", "Andra", "Alexia", "Alexandra", "Alina"]
    students_already_generated = set()

    for i in range(n):
        student_name = choice(list_of_names_for_students)
        while student_name in students_already_generated:
            student_name = choice(list_of_names_for_students)

        students_already_generated.add(student_name)
        list_of_generated_students.append(Student(str(i + starting_index_for_IDs), student_name))

    return list_of_generated_students
