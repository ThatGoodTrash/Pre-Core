from ..exercises.main import next_palindrome


def test_palindrome():
    assert next_palindrome(808) == 818
    assert next_palindrome(999) == 1001
    assert next_palindrome(2133) == 2222
    assert next_palindrome(4052555153018976267) == 4052555153515552504
