from random import choice, randint
from src.domain.Discipline_init import Discipline, discipline_generator
from src.domain.Student_init import Student, students_generator

LOWEST_GRADE_OPTION = 1
HIGHEST_GRADE_OPTION = 10

class Grade():
    def __init__(self, student: Student, discipline: Discipline, grade: float):
        if not isinstance(discipline, Discipline):
            raise TypeError("The argument is not a Discipline type object!")
        if not isinstance(student, Student):
            raise TypeError("The argument is not a Student type object!")
        if not isinstance(grade, float) and not isinstance(grade, int):
            raise TypeError("Grade must be a number!")
        if grade < 1 or grade > 10:
            raise TypeError("Grade must be between 1 and 10!")

        self._discipline = discipline
        self._student = student
        self._grade = grade

    def __str__(self):
        return "Discipline: " + str(self.discipline) + " Student: " + str(
            self.student) + "Grade obtained: " + str(self.grade)

    @property
    def discipline(self):
        return self._discipline

    @property
    def student(self):
        return self._student

    @property
    def grade(self):
        return self._grade


def grades_generator(n):
    list_of_grades = []
    list_of_students = students_generator(n)
    list_of_disciplines = discipline_generator(n)
    for i in range(n):
        list_of_grades.append(
            Grade(choice(list_of_students), choice(list_of_disciplines), randint(LOWEST_GRADE_OPTION, HIGHEST_GRADE_OPTION)))
    return list_of_students, list_of_disciplines, list_of_grades
