from hashlib import md5
from ..exercises.main import part1, part2


def test_part1():
    expected = b"(~\x03\xdb\x1d\x99\xe0\xec.\xdb\x90\xd0y\xe1B\xf3"
    result = part1()
    assert md5(str(result).encode()).digest() == expected


def test_part2():
    expected = b'lXt\x9e\x11~0j!\xc6\x81\xeeK;N\x86'
    result = part2()
    assert md5(str(result).encode()).digest() == expected
