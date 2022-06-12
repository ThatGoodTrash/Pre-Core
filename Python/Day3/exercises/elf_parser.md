# ELF Tutorial

# Side Note:
C files are out of the scope of this course.
However, we are using this one in order to create an ELF file, 
which is just a linux binary file.

To find out more information on how an ELF file is structured:
https://linux.die.net/man/5/el

# Make the Tutorial Binary
In order to compile the binary for this tutorial, follow this quick tutorial.

` $ gcc -g -o hello hello.c`
` $ chmod +x ./hello`

This will have created a file in your directory with no extension: hello

Run that binary with:

` > ./hello ` 

You should see: 

` Hello World! ` 

If you do not, contact a TA.

The "hello" file is an ELF file, which will allow you to familiarize yourself with ELF files before the beginning of this lab.

For the Data Parsing lab, we know that CAKE files are the same as ELF except that the headers have changed. Linux uses the file header to help give it information on how to run. 

Important: You will not be able to run the CAKE files like the hello file above.

Look at the contents of the hello.c file:

` cat hello.c `

You'll notice that the "Hello World!" is a string. We know that CAKE files hold are supposed to hold recipes that are printed out to us in a similiar fashion.

Hmmm... So if we can find the "Hello World!" string in the hello binary, we should be able to find the recipe strings in the CAKE binaries.

# Using Hex Editor

Let's do some analysis. We can't just open a binary and read it, it's a binary! BUT, we can look at 
it's bytes in hex with a hex editor. 

` > hex hello `

You'll notice that the first bytes are:

` 7F 45 4C 46 `

You'll also see that (on the far right side) that those bytes translate to:

` .ELF `

HINT: If ELF files start with .ELF (4 bytes), what do you think that CAKE files start with?

# Finding Strings

Use the down arrow in the hex editor to scroll through the hex file. There'll be a lot of 0s, so just keep scrolling. Look through the entire hello binary and see if you can find anything interesting. The righthand side will show you ASCII strings from the hex. 

Find anything interesting?

Yes?

Great! Make note of the offset on the lefthand side and continue.

No, you're stuck?

Okay, here's a hint. Remember we're looking for an ASCII string. What's the ASCII string in the hello.c file?

# Using readelf

CAKE files don't have the same ELF headers, but they do have good nuggets of information

If you wanted to look at hello's ELF header, do the following command:

` > readelf hello --file-header `

Elf files are comprised of "sections", do you know which section strings are stored?

No? (Might I suggest ye ol' google?)

` > readelf hello --sections `

Note that it's formatted oddly where each "row" is actually two lines each. Remember that section that contains strings that you googled? What size and offset is that section we care about?

# Python Parser

Go look at the elf_parser.py file and read through it to see how you can grab strings from the ELF file.
