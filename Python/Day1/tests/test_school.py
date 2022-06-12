from ..exercises.school import School, ElementarySchool, MiddleSchool, HighSchool
from ..exercises.student import (
    Student,
    ElementarySchoolStudent,
    MiddleSchoolStudent,
    HighSchoolStudent,
)


def test_schools():
    assert issubclass(ElementarySchool, School)
    assert issubclass(MiddleSchool, School)
    assert issubclass(HighSchool, School)


def test_students():
    assert issubclass(ElementarySchoolStudent, Student)
    assert issubclass(MiddleSchoolStudent, Student)
    assert issubclass(HighSchoolStudent, Student)


def test_new_student():
    student_one = Student("rachel")
    assert student_one is not None
    assert student_one.name == "rachel"


def test_middle_school():
    student = MiddleSchoolStudent("johny")
    school = MiddleSchool()
    school.add_student(student)
    assert len(school.students()) == 1


def test_high_school():
    student = HighSchoolStudent("jake")
    school = HighSchool()
    school.add_student(student)
    assert len(school.students()) == 1


def test_little_school():
    student = ElementarySchoolStudent("jimmy")
    school = ElementarySchool()
    school.add_student(student)
    assert len(school.students()) == 1


def test_student_cant_go_to_wrong_school():
    small_student = ElementarySchoolStudent("jimmy")
    medium_student = MiddleSchoolStudent("johny")
    big_student = HighSchoolStudent("jake")
    small_school = ElementarySchool()
    medium_school = MiddleSchool()
    big_school = HighSchool()

    # We shouldn't be able to send a middle schooler to elementary school
    assert not small_school.add_student(medium_student)
    assert not medium_school.add_student(big_student)
    assert not big_school.add_student(small_student)
