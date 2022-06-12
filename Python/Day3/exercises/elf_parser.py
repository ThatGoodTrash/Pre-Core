from elftools.elf.elffile import ELFFile

"""
    Because a CAKE file isn't really an ELF file, you won't be able to use the
    pyelftools library for the CAKE lab.
    However, it's good to know about it and have a nice example to use it.
"""


def print_sections(elf_filename):

    with open(elf_filename, "rb") as f:

        # Create an ELF object with our file
        elf = ELFFile(f)

        # Print out all the sections and their "Address" which is just an offset
        # of where each section is in the file -> remember that's in HEX not int
        print("Section Address | Section Name")
        for section in elf.iter_sections():
            print(hex(section["sh_addr"]), section.name)

    f.close()


def get_section(elf_filename):

    with open(elf_filename, "rb") as f:

        # TODO: You'll need to calculate the following two variables:
        section_offset = 0
        section_size = 0

        section_end = section_offset + section_size

        print("")
        print("Section Offset: ", section_offset)
        print("Section Size: ", section_size)
        print("Section End: ", section_end)
        print("")

        # Grab the file's contents as a byte string
        elf_contents = f.read()

        # Uncomment if you'd like to see all the bytes in the file
        # print(elf_contents)

        # Let's just zone in on the section we care about
        elf_section = elf_contents[section_offset:section_end]
        print(elf_section)

        # Congrats! You got the strings.
        # Hopefully this helps you understand how the ELF file works
        # and how to get the information you may need.

        # Parsing that section is the real challenge for the CAKE data

    f.close()


if __name__ == "__main__":

    print_sections("hello")
    get_section("hello")
