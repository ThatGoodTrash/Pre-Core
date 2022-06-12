from hashlib import md5
from ..exercises.main import main


def test_main():
    expected = b'`\x80>\xa7\x98\xa0\xc0\xdf\xb7\xf3c\x97\xd8\xd4\xd7r'
    result = main()
    assert md5(str(result).encode()).digest() == expected
