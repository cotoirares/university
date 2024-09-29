from src.domain.Discipline_init import Discipline, discipline_generator
from src.domain.Grade_init import Grade, grades_generator
from src.domain.Student_init import Student, students_generator

LOWEST_GRADE = 1
HIGHEST_GRADE = 10

class RepositoryError(Exception):
    def __init__(self, message: str) -> None:
        self.__message = message

    @property
    def message(self) -> str:
        return self.__message

    def __str__(self) -> str:
        return self.__message


class MemoryRepository:
    def __init__(self):
        students, disciplines, grades = grades_generator(10)
        self.students = students
        self.disciplines = disciplines
        self.grades = grades

    def find_student_by_id(self, student_id):
        for student in self.students:
            if student.id == student_id:
                return student
        raise RepositoryError(f"Student with ID {student_id} was not found.")

    def find_discipline_by_id(self, discipline_id):
        for discipline in self.disciplines:
            if discipline.id == discipline_id:
                return discipline
        raise RepositoryError(f"Discipline with ID {discipline_id} not found.")

    def add_student(self, student):
        if student in self.students:
            raise RepositoryError(
                f"Student with ID {student.id} already exists in the list.")
        if not isinstance(student, Student):
            raise RepositoryError("The input is not valid for a student.")
        self.students.append(student)

    def remove_student(self, student_id):
        for student in self.students:
            if student.id == student_id:
                self.students.remove(student)
                self.remove_grades_by_student(student_id)
                return
        raise RepositoryError(f"Student with ID {student_id} was not found in the list.")

    def update_student(self, student_id, new_name):
        for student in self.students:
            if student.id == student_id:
                student.name = new_name
                return
        raise RepositoryError(f"Student with ID {student_id} not found.")

    def list_students(self):
        return self.students.copy()

    def add_discipline(self, discipline):
        if discipline in self.disciplines:
            raise RepositoryError(
                f"Discipline with ID {discipline.id} already exists in the list.")
        if not isinstance(discipline, Discipline):
            raise RepositoryError("The input is not valid for a discipline.")
        self.disciplines.append(discipline)

    def remove_discipline(self, discipline_id):
        for discipline in self.disciplines:
            if discipline.id == discipline_id:
                self.disciplines.remove(discipline)
                self.remove_grades_by_discipline(discipline_id)
                return
        raise RepositoryError(f"Discipline with ID {discipline_id} was not found in the list.")

    def update_discipline(self, discipline_id, new_name):
        for discipline in self.disciplines:
            if discipline.id == discipline_id:
                discipline.name = new_name
                return
        raise RepositoryError(f"Discipline with ID {discipline_id} was not found in the list.")

    def list_disciplines(self):
        return self.disciplines.copy()

    def add_grade(self, grade):
        if not isinstance(grade, Grade):
            raise RepositoryError("The input is not valid for a grade.")
        if grade.grade < LOWEST_GRADE or grade.grade > HIGHEST_GRADE:
            raise RepositoryError("The grade must be between 1 and 10.")
        self.find_discipline_by_id(grade.discipline.id)
        self.find_student_by_id(grade.student.id)
        self.grades.append(grade)

    def remove_grades_by_student(self, student_id):
        self.grades = [grade for grade in self.grades if grade.student.id != student_id]

    def remove_grades_by_discipline(self, discipline_id):
        self.grades = [grade for grade in self.grades if grade.discipline.id != discipline_id]

    def get_grades_by_student(self, student_id):
        if student_id not in [grade.student.id for grade in self.grades]:
            raise RepositoryError(f"Student with ID {student_id} was not found.")
        return [grade for grade in self.grades if grade.student.id == student_id]

    def get_grades_by_discipline(self, discipline_id):
        if discipline_id not in [grade.discipline.id for grade in self.grades]:
            raise RepositoryError(f"Discipline with ID {discipline_id} was not found in the list.")
        return [grade for grade in self.grades if grade.discipline_id == discipline_id]

    def get_average_grade_for_discipline(self, discipline_id, student_id=None):
        if student_id is not None:
            #calculatint average grade for a specific discipline and student
            discipline_grades = [grade.grade for grade in self.grades if
                                 grade.discipline.id == discipline_id and grade.student.id == student_id]
        else:
            #calculatint average grade for a specific discipline (all students)
            discipline_grades = [grade.grade for grade in self.grades if grade.discipline.id == discipline_id]

        if not discipline_grades:
            return None  #this means that there are no grades for the discipline yet

        return sum(discipline_grades) / len(discipline_grades)

    def get_student_aggregated_average(self, student_id):
        student_grades = [grade.grade for grade in self.grades if grade.student.id == student_id]
        if not student_grades:
            return None  #this means that there are no grades for the student yet

        return sum(student_grades) / len(student_grades)

    def get_all_disciplines_with_grades(self):
        return list(set(grade.discipline.id for grade in self.grades))

    def find_students(self, query):
        query_lower = query.lower()
        return [student for student in self.students if query_lower in student.name.lower()]

    def find_disciplines(self, query):
        query_lower = query.lower()
        return [discipline for discipline in self.disciplines if query_lower in discipline.name.lower()]

    def list_all_grades(self):
        return self.grades.copy()
