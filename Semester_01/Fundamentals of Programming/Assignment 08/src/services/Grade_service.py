from src.repository.Memory_Repository import MemoryRepository, RepositoryError
from src.domain.Grade_init import Grade


class GradeService:
    def __init__(self, repository: MemoryRepository):
        self.repository = repository

    def add_grade(self, student_id, discipline_id, value):
        response_data = {"success": True,
                         "message": "Grade added successfully!"}
        try:
            value = float(value)
        except ValueError:
            response_data["success"] = False
            response_data["message"] = "Grade is not a float!"
            return response_data

        try:
            grade_discipline = self.repository.find_discipline_by_id(
                discipline_id)
            grade_student = self.repository.find_student_by_id(student_id)
        except RepositoryError as re:
            response_data["success"] = False
            response_data["message"] = str(re)
            return response_data
        try:
            grade = Grade(grade_student, grade_discipline, value)
        except TypeError as te:
            response_data["success"] = False
            response_data["message"] = str(te)
            return response_data
        try:
            self.repository.add_grade(grade)
        except RepositoryError as re:
            response_data["success"] = False
            response_data["message"] = str(re)
            return response_data
        return response_data

    def remove_grades_by_student(self, student_id):
        response_data = {"success": True,
                         "message": f"Grades with student ID {student_id} removed successfully!"}
        try:
            self.repository.find_student_by_id(student_id)
            self.repository.remove_grades_by_student(student_id)
        except RepositoryError as re:
            response_data["success"] = False
            response_data["message"] = str(re)
            return response_data
        return response_data

    def remove_grades_by_discipline(self, discipline_id):
        response_data = {"success": True,
                         "message": f"Grades with discipline ID {discipline_id} removed successfully!"}
        try:
            self.repository.find_discipline_by_id(discipline_id)
            self.repository.remove_grades_by_discipline(discipline_id)
        except RepositoryError as re:
            response_data["success"] = False
            response_data["message"] = str(re)
            return response_data
        return response_data

    def list_grades(self):
        response_data = {"success": True,
                         "message": "Grades listed successfully!",
                         "data": self.repository.list_all_grades()}
        return response_data

    def list_grades_for_student(self, student_id):
        return self.repository.list_grades_for_student(student_id)

    def list_grades_for_discipline(self, discipline_id):
        return self.repository.list_grades_for_discipline(discipline_id)

    def list_grades_for_discipline_and_student(self, discipline_id, student_id):
        return self.repository.list_grades_for_discipline_and_student(discipline_id, student_id)

    def get_average_grade_for_discipline(self, discipline_id, student_id=None):
        return self.repository.get_average_grade_for_discipline(discipline_id, student_id)

    def get_student_aggregated_average(self, student_id):
        return self.repository.get_student_aggregated_average(student_id)

    def get_failing_students(self):
        response_data = {"success": True,
                         "message": "Failing students listed successfully!",
                         "data": []}
        all_disciplines = self.repository.list_disciplines()
        all_students = self.repository.list_students()
        failing_students = []
        for student in all_students:
            has_failing_discipline = False
            for discipline in all_disciplines:
                average_grade = self.repository.get_average_grade_for_discipline(
                    discipline.id, student.id)
                if average_grade is not None and average_grade < 5:
                    has_failing_discipline = True
                    break
            if has_failing_discipline:
                failing_students.append(student)
        response_data["data"] = failing_students
        return response_data

    def best_students(self):
        all_students = self.repository.list_students()
        student_averages = []
        response_data = {"success": True,
                         "message": "Best students listed successfully!",
                         "data": []}

        for student in all_students:
            average_grade = self.repository.get_student_aggregated_average(
                student.id)
            if average_grade is not None:
                student_averages.append((student, average_grade))

        student_averages.sort(key=lambda x: x[1], reverse=True)
        response_data["data"] = [student[0] for student in student_averages]
        return response_data

    def disciplines_with_grades_sorted_by_average(self):
        all_disciplines = self.repository.list_disciplines()
        discipline_averages = []
        respose_data = {"success": True,
                        "message": "Disciplines with grades listed successfully!",
                        "data": []}

        for discipline in all_disciplines:
            average_grade = self.repository.get_average_grade_for_discipline(
                discipline.id)
            if average_grade is not None:
                discipline_averages.append((discipline, average_grade))

        discipline_averages.sort(key=lambda x: x[1], reverse=True)
        respose_data["data"] = discipline_averages
        return respose_data
