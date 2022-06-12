Finding the right file can be incredibly difficult. Filename, full text search, metadata, unknown location… What are you looking for? For this exercise, we’re going to develop an increasingly capable tool capable of searching through the operating system for a file that we’re looking for.

Why don’t we just use “grep”, “find”, “findstr”, “Get-ChildItem”, or “Select-String”? Each of those utilities will spawn a new shell, process, or fork. Sometimes, we just need to build the capability ourselves.

Beginner: Develop an application (CLI) that is capable of finding a specified file or files that match the criteria specified. In particular, the application should be able to find by one or more of the following criteria:
Find a file by name, extension, or filename that matches the regular expression
Find a file if the content contains a string or by regular expression
Find a file by date, owner, or file permissions (read, write, execute)
Find a file by MD5 hash

In addition, the results should print to stdout or to a file in either CSV or JSON format.

Intermediate: The filesystem doesn’t change that much… does it?  Depending on the search criteria, your program should run faster on subsequent searches. Running through the entire file system shouldn’t happen on your second query if you’re just looking for a particular filename.

Additionally, profile your code to determine whether it is IO or CPU bound. Consider including multithreading / multiprocessing to allow your program to search faster.

Expert: Make your program persistent and use system notifications to keep track of when files change. You only need to do this for one system (. Information about the file should be updated in your cache when it occurs.  Can you make metadata queries instantaneous?
Hint:
Windows: SHChangeNotifyRegister
Linux: inotify
