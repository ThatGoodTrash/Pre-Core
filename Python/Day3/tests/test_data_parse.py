from ..exercises.data_parse import (
    decode_cake_format,
    decrypt_cake_file,
    decode_cake_file,
)
from pathlib import Path
from hashlib import md5

cake_path = Path(__file__).parent / "../cakes/"
src_path = Path(__file__).parent / "../setup/tmp/"


def md5_file(file: Path) -> bytes:
    with open(file, "rb") as f:
        return md5(f.read()).digest()


def test_beginner_cake():
    expected = b"\xf7\x91\xe2\x15\x08\x1dm\xfc\x15\xb9\xa6\xebR_[)"
    result = decode_cake_format()
    result_hash = md5(result).digest()
    assert result_hash == expected
    assert md5_file(cake_path / "beginner_cake_decoded") == md5_file(
        src_path / "beginner"
    )


def test_intermediate_cake():
    decrypt_cake_file(cake_path / "intermediate_cake")
    assert md5_file(cake_path / "intermediate_cake_decrypted") == md5_file(
        src_path / "cookie"
    )


def test_expert_cake1():
    decode_cake_file(cake_path / "expert_box", 1)
    assert md5_file(cake_path / "expert_box_decrypted") == md5_file(src_path / "box")


def test_expert_cake2():
    decode_cake_file(cake_path / "expert_chocolate", 2)
    assert md5_file(cake_path / "expert_chocolate_decrypted") == md5_file(
        src_path / "chocolate"
    )


def test_expert_cake3():
    decode_cake_file(cake_path / "expert_cheese", 3)
    assert md5_file(cake_path / "expert_cheese_decrypted") == md5_file(
        src_path / "cheese"
    )


def test_expert_cake4():
    decode_cake_file(cake_path / "expert_crab", 4)
    assert md5_file(cake_path / "expert_crab_decrypted") == md5_file(src_path / "crab")


def test_expert_cake5():
    decode_cake_file(cake_path / "expert_pineapple", 5)
    assert md5_file(cake_path / "expert_pineapple_decrypted") == md5_file(
        src_path / "pineapple"
    )
