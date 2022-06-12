from ..exercises.main import next_palindrome


def test_main():
    assert next_palindrome(23545) == 23632
    assert next_palindrome(94187978322) == 94188088149
    assert next_palindrome(713322) == 714417
    assert next_palindrome(1234628) == 1235321
    assert next_palindrome(94187978322) == 94188088149
