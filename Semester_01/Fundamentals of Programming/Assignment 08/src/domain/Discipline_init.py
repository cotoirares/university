from random import choice, random
from src.domain.ID_init import IdObject
STARTING_ID_FOR_DISCIPLINES = 1000

class Discipline(IdObject):
    def __init__(self, id, name: str):
        super().__init__(id)
        if len(name) < 4:
            raise TypeError("The name must be at least 4 characters long!")
        else:
            self.__name = name

    def __str__(self):
        return "ID: " + str(self.id) + " Discipline: " + self.name

    def __eq__(self, other):
        return isinstance(other, Discipline) and self.id == other.id

    def __copy__(self):
        return Discipline(self.id, self.name)

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, new_name):
        self.__name = new_name


def discipline_generator(n):
    disciplines_list_with_IDs = []
    index_to_start_in_generating_disciplines = STARTING_ID_FOR_DISCIPLINES
    list_of_names_for_disciplines = ["English", "Mathematics", "Computer Science", "History", "Geography", "Physics", "Chemistry", "Biology", "Arts", "Economy"]
    disciplines_already_generated = set()

    for i in range(n):
        discipline_name = choice(list_of_names_for_disciplines)
        while discipline_name in disciplines_already_generated:
            discipline_name = choice(list_of_names_for_disciplines)

        disciplines_already_generated.add(discipline_name)
        disciplines_list_with_IDs.append(Discipline(str(i + index_to_start_in_generating_disciplines), discipline_name))

    return disciplines_list_with_IDs
