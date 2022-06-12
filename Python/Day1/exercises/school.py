class School:
    pass


class ElementarySchool(School):
    students = 0

    def __init__(self) -> None:
        super().__init__()

    def add_student(self, student):
        MiddleSchool.students += 1


class MiddleSchool(School):
    students = 0

    def __init__(self) -> None:
        super().__init__()

    def add_student(self, student):
        MiddleSchool.students += 1



class HighSchool(School):
    student_num = 0

    def __init__(self) -> None:
        super().__init__()

    def add_student(self, student):
        MiddleSchool.students += 1
    
    def students(self):
        student_num = 0
        student_num += 1
