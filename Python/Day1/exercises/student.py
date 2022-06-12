class Student:
    def __init__(self, name:str) -> None:
        self.name = name


class ElementarySchoolStudent(Student):
    pass


class MiddleSchoolStudent(Student):
    def __init__(self, name: str) -> None:
        super().__init__(name)


class HighSchoolStudent(Student):
    pass
