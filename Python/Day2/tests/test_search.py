from ..exercises.search import (
    get_items,
    has_extension,
    file_contains,
    file_perms_matches,
    has_name,
    matches_hash,
)
import re
import pytest
from pathlib import Path

test_folder = (Path(__file__).parent / "test_folder").resolve()


def test_files_and_folders():
    # Note: My get_items returns a list of pathlib.Path objects. We use the
    # list comprehensions below to just get the names

    # Test that the files we know are in the folder are coming back
    files_set = set(["notme.run", "findme.txt", "md5.hash", "other.py", ".gitkeep"])
    files = set([x.name for x in get_items(test_folder, files=True, dirs=False)])
    assert len(files_set) == len(files)
    assert len(files & files_set) == len(files_set)

    # Test that the folders we know are in the folder are coming back
    folders_set = set(["folder_1", "folder_2", "dont_look"])
    folders = set([x.name for x in get_items(test_folder, files=False, dirs=True)])

    assert len(folders_set) == len(folders)
    assert len(folders & folders_set) == len(folders_set)

    # Test that we can get both files and folders
    files_and_folders = set(
        [x.name for x in get_items(test_folder, files=True, dirs=True)]
    )
    combined_set = files_set.union(folders_set)
    assert len(files_and_folders) == len(combined_set)
    assert len(combined_set & files_and_folders) == len(combined_set)


def test_find_file_extension():
    expected = set(["findme.txt"])
    results = set([])
    for path in get_items(test_folder, files=True, dirs=False):
        if has_extension(path, "txt"):
            results.add(path.name)

    assert len(expected) == len(results)
    assert len(expected & results) == len(expected)


def test_find_name():
    expected = set(["other.py"])
    results = set([])
    for path in get_items(test_folder, files=True, dirs=False):
        if has_name(path, "other.py"):
            results.add(path.name)

    assert len(expected) == len(results)
    assert len(expected & results) == len(expected)


# 5f2c96c687d353970f8ecff84ed3979f


def test_find_hash():
    expected = set([".gitkeep"])
    results = set([])
    for path in get_items(test_folder, files=True, dirs=False):
        if matches_hash(path, "5f2c96c687d353970f8ecff84ed3979f"):
            results.add(path.name)

    assert len(expected) == len(results)
    assert len(expected & results) == len(expected)


def test_find_file_contents():
    expected = set([".gitkeep", "md5.hash"])
    results = set([])
    for path in get_items(test_folder, files=True, dirs=False):
        if file_contains(path, "why am I"):
            results.add(path.name)
        if file_contains(path, re.compile("^AAA+$")):
            results.add(path.name)

    assert len(expected) == len(results)
    assert len(expected & results) == len(expected)


@pytest.mark.skip(reason="Implement based on system")
def test_find_by_date():
    assert 1 == 2


@pytest.mark.skip(reason="Implement based on system")
def test_find_by_owner():
    assert 1 == 2


@pytest.mark.skip(reason="Implement based on system")
def test_find_by_permissions():
    expected = set([".gitkeep"])
    results = set([])
    for path in get_items(test_folder, files=True, dirs=False):
        if file_perms_matches(path, read=True, write=True, execute=True):
            results.add(path.name)

    assert len(expected) == len(results)
    assert len(expected & results) == len(expected)
