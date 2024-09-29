from src.repository.Memory_Repository import MemoryRepository, RepositoryError
from src.domain.Student_init import Student


class StudentService:
    def __init__(self, stud_repo: MemoryRepository) -> None:
        self.__stud_repo = stud_repo

    def add_student(self, student_id, name):
        response_data = {"success": True,
                         "message": "Student added successfully!"}
        try:
            student = Student(student_id, name)
        except TypeError as te:
            response_data["success"] = False
            response_data["message"] = str(te)
            return response_data
        self.__stud_repo.add_student(student)
        return response_data

    def remove_student(self, student_id):
        response_data = {"success": True,
                         "message": f"Student with ID {student_id} removed successfully!"}
        try:
            self.__stud_repo.find_student_by_id(student_id)
        except RepositoryError as e:
            response_data["success"] = False
            response_data["message"] = str(e)
            return response_data

        self.__stud_repo.remove_student(student_id)

        return response_data

    def update_student(self, student_id, new_name):
        response_data = {"success": True,
                         "message": f"Student with ID {student_id} updated successfully!"}
        try:
            self.__stud_repo.update_student(student_id, new_name)
        except RepositoryError as e:
            response_data["success"] = False
            response_data["message"] = str(e)
            return response_data
        return response_data

    def list_students(self):
        response_data = {"success": True,
                         "message": "Students listed successfully!",
                         "data": self.__stud_repo.list_students()}
        return response_data

    def find_students(self, query):
        response_data = {"success": True,
                         "message": "Students listed successfully!",
                         "data": self.__stud_repo.find_students(query)}
        return response_data
