"""
------------ READ THIS BEFORE YOU BEGIN -----------------------

Your lab analyzes encrypted binary files.
The beginner cake file is not encrypted.

Binary files should not be put in code repositories like git.
Do not add or commit any binary files to your branch.

Please read the README.md for setup instructions.

The binaries you need will be under /Python/Day3/cakes/

"""

from elftools.elf.elffile import ELFFile
from Crypto.Cipher import ARC4
import struct
import os

# Beginner Challenge
def decode_cake_format():

    # CAKE headers are right before ELF headers.
    # ELF files start with the same exact bytes ALWAYS.
    # Find those bytes using hexeditor.

    beginner_cake_file = "cakes/cake_beginner"
    header = ""

    # TODO: Correct the header length
    # How many bytes (1 byte looks like: 0xHH) are in the CAKE header?
    header_length = 0

    # TODO: Read the file's bytes

    # TODO: Read only the header's bytes from the file

    # TODO: Unpack the bytes into a string

    # TODO: Decode the string to ascii

    print("Beginner Header: ", header)

    return header


# Intermediate Challenge
def decrypt_cake_file(filename):

    # Hint, the header may have some helpful information...
    # If you are strapped for time, you can use libraries instead of implementing it

    # Extra mini task, decrypt and remove the CAKE header. Run the file and see what happens.

    pass


# Expert: It turns out every version of malware uses a new CAKE format.
# The R&D team has provided documentation for the various types of cake files.
# Build a tool that can read the CAKE configs and decode the list of CAKE files.
def decode_cake_file(cake_list):
    pass


def main():

    cake_files = os.listdir("cakes/")

    # Beginner Challenge
    decode_cake_file()

    # Intermediate Challenge
    # decrypt_cake_file(f)

    # Expert Challenge
    # decode_cake_file(cake_files)


if __name__ == "__main__":
    main()
