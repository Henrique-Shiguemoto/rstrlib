# rstrlib

This is just a simple string library for casual use. This is not recommended for low level development. 

The <code>main.c</code> is just a test code showing how to use the library and testing the functions.

## Features

- String creation
- String deletion
- String length calculation
- String copying
- String concatenation
- Character search in String
- Substring extraction
- String trimming
- String convertion to upper and lower case
- String convertion (string to int, string to float) (maybe I'll get rid of this...I don't enjoy the stdio.h dependency)
- Convenience function such as counting letters function, counting digits function, verifying if character is letter or digit
- String reversing
- String splitting by delimiter
  
## How to Use

Copy the <code>rstrlib.c</code> and <code>rstrlib.h</code> files to your project. Then you can just include the <code>rstrlib.h</code> in a source file.

Depending on your build system, you'll need to update it (like a Makefile for example), since this isn't a header-only library.

## Technologies Used

- C11
- Makefile
