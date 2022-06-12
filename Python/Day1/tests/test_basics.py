from ..exercises.basics import (
    exercise_one,
    exercise_two,
    exercise_three,
    exercise_four,
    exercise_five,
    exercise_six,
    exercise_seven,
    exercise_eight,
    is_prime,
)


def test_one():
    assert exercise_one() == 1


def test_two():
    assert exercise_two() == 1.3


def test_three():
    empty_array = exercise_three()
    assert len(empty_array) == 0
    assert type(empty_array) == list


def test_four():
    empty_tuple = exercise_four()
    assert len(empty_tuple) == 0
    assert type(empty_tuple) == tuple


def test_five():
    orig_array = [1, 2, 3, 4]
    return_array = exercise_five(orig_array)
    expected_array = [4, 3, 2, 1]
    assert len(return_array) == 4
    assert type(return_array) == list
    assert expected_array == return_array


def test_six():
    orig_array = [5, 1, 6, 4]
    sorted_array = exercise_six(orig_array)
    expected_array = [1, 4, 5, 6]
    assert len(sorted_array) == 4
    assert type(sorted_array) == list
    assert expected_array == sorted_array


def test_seven():
    result = exercise_seven()
    assert len(result) == 5
    assert type(result) == list
    assert type(result[0]) == int
    assert type(result[1]) == list
    assert type(result[2]) == tuple
    assert type(result[3]) == str
    assert type(result[4]) == bytes


def test_eight():
    for i in range(0, 50):
        assert exercise_eight(i, i) == i + i


def test_is_prime():
    assert is_prime(7)
    assert is_prime(13)
    assert not is_prime(4)
    assert not is_prime(16)
    assert is_prime(1321)
    assert not is_prime(1024)
