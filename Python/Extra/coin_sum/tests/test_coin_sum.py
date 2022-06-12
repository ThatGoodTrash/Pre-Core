from hashlib import md5
from ..exercises.main import main


def test_main():
    expected = b"\x14-\xfeJ3\xd6$\xd2\xb80\xa9%~\x96rm"
    result = main()
    assert md5(str(result).encode()).digest() == expected
