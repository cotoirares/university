class IdObject:
    def __init__(self, _id: int):
        self.__id = str(_id)
    @property
    def id(self):
        return self.__id