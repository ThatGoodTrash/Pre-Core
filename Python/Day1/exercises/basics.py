# Return an int
def exercise_one():
    return 1


# Return a float
def exercise_two():
    return 1.3


# return an empty list
def exercise_three():
    empty_list = []
    return empty_list


# return an empty tuple
def exercise_four():
    empty_tup = ()
    return tuple(empty_tup)


# reverse the order of a list
def exercise_five(input_arr):
    input_arr.reverse()

    return input_arr


# sort a list
def exercise_six(input_arr):
    input_arr.sort()

    return input_arr


# return a list that contains a int, another list, a tuple,a string, and bytes
def exercise_seven():
    result_list = []
    result_list.append(5)
    result_list.append([1, 2, 3])
    result_list.append((4, 5))
    result_list.append("random string")
    result_list.append(b"this is bytes")

    return result_list


# return the sum of two numbers
def exercise_eight(one, two):
    sum = one + two

    return sum


# return true if a number is prime
def is_prime(number):
    for i in range(2, int(number / 2) + 1):
        if number % i == 0:
            return False
        else:
            return True
