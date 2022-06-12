import datetime
import re
from pathlib import Path
from typing import Iterable, Optional, Union


def get_items(root_dir: str, files: bool, dirs: bool) -> Iterable[Path]:
    pass

def name_contains(item: Path, pattern: str, is_file: bool) -> bool:
    pass


def has_extension(item: Path, pattern: str) -> bool:
    pass


def has_name(item: Path, pattern: str) -> bool:
    pass


def file_contains(item: Path, pattern: Union[str, re.Pattern]) -> bool:
    pass


def file_date_matches(
    item: Path,
    start: Optional[datetime.datetime] = None,
    stop: Optional[datetime.datetime] = None,
) -> bool:
    pass


def file_owner_matches(item: Path, owner: str) -> bool:
    pass


def file_perms_matches(item: Path, read: bool, write: bool, execute: bool) -> bool:
    pass


def matches_hash(item: Path, hash: str) -> bool:
    pass
