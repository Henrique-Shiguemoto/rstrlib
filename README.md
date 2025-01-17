# rstrlib

This is just a simple string library for casual use. This is not recommended for low level/performance dependent development. 

The <code>main.c</code> is just a test code showing how to use the library and testing the functions.

## Features

- String creation / setting / deletion
- String length calculation
- String copying
- String concatenation
- String searching
- Substring extraction
- String comparison
- String trimming
- String convertions
- Convenience functions (see <code>main.c</code>)
- String splitting by delimiter and substring
- Delimiter and Substring replacement
  
## How to Use

Copy the <code>rstrlib.c</code> and <code>rstrlib.h</code> files to your project. Then you can just include the <code>rstrlib.h</code> in a source file.

Depending on your build system, you'll need to update it (like a Makefile for example), since this isn't a header-only library.

## Technologies Used

- C11
- Makefile
