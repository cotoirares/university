from src.repository.Memory_Repository import MemoryRepository
from src.services.Student_service import StudentService
from src.services.Discipline_service import DisciplineService
from src.services.Grade_service import GradeService


class Services:
    def __init__(self) -> None:
        self.__stud_repo = MemoryRepository()
        self.student_service = StudentService(self.__stud_repo)
        self.discipline_service = DisciplineService(self.__stud_repo)
        self.grade_service = GradeService(self.__stud_repo)
