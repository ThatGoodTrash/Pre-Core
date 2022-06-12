from Crypto.Cipher import ARC4
import struct


def create_new_header(config_type):
    """
    Create Headers "randomly"
    """

    magic_numbers = b"CAKE"
    pad = b"0000"
    encryption_type = b"RC4"
    pad2 = b"00000"
    key = b"supersecretkey24"
    length = 32
    funny = b"The cake is a lie"

    if config_type == 1:
        new_header = struct.pack(
            "4s4s3s5s16si", magic_numbers, pad, encryption_type, pad2, key, length
        )
    elif config_type == 2:
        new_header = struct.pack("4s3s16s", magic_numbers, encryption_type, key)
    elif config_type == 3:
        new_header = struct.pack("4s16s", magic_numbers, key)
    else:
        new_header = struct.pack(
            "4s3s16s17s", magic_numbers, encryption_type, key, funny
        )

    return new_header


def create_beginner():
    """
    Create CAKE file for Beginner Class
    """

    filename = "./tmp/beginner"
    new_filename = "../cakes/beginner_cake"
    header = b"CAKE"

    # Read the file and store all the contents
    with open(filename, "rb") as f:
        contents = f.read()

    # Open the file and write the header and then the contents
    with open(new_filename, "wb") as nf:
        nf.write(header)
        nf.write(contents)


def encrypt_file(filename, new_filename, header):

    key = b"supersecretkey24"
    cipher = ARC4.new(key)

    # Read the 'plaintext' ELF Files
    with open(filename, "rb") as f:
        contents = f.read()

    # Encrypt it's contents
    encrypted_contents = cipher.encrypt(contents)

    # Write the random header and the encrypted contents
    with open(new_filename, "wb") as nf:
        nf.write(header)
        nf.write(encrypted_contents)


def create_intermediate():
    """
    Create a CAKE file for Intermediate challenge
    """

    filename = "./tmp/cookie"
    new_filename = "../cakes/intermediate_cake"
    header = create_new_header(3)

    encrypt_file(filename, new_filename, header)


def create_expert():
    """
    Encrypt files for Expert Levels
    """

    tmp_path = "./tmp/"
    dst_path = "../cakes/"
    # ELF binaries compiled from C recipes
    recipes = ["box", "chocolate", "cheese", "crab", "pineapple"]

    for i, recipe in enumerate(recipes):
        filename = tmp_path + recipe
        new_filename = dst_path + "expert_" + recipe
        header = create_new_header(i+1)
        encrypt_file(filename, new_filename, header)


if __name__ == "__main__":

    # Create files for Beginner Level
    create_beginner()

    # Create files for Intermediate
    create_intermediate()

    # Create files for Expert Level
    create_expert()
