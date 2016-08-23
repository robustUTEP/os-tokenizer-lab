# os-tokenizer-lab

The printDemo subdir includes source code to a program that 
prints text files line-by-line with line numbers.  It does lots of malloc and 
pointer futzing.

Your lab should be added to the "tokenizer" subdir and pushed back to
the repository for grading.

A summary of the lab assignment follows. The full assignment is on the
course web site.

Objective

In this lab, you will demonstrate a competency in the "C" programming language. Competency in C will be required for future success in this course.
Skills that you must acquire before attempting this lab

Familiarity with the C programming language
How to run a text editor (such as emacs)
You will demonstrate mastery of

Arrays and pointers
memory allocation
Separate compilations and linking
Writing a simple Makefile
Assignment

Write a tokenizer function mytoc() in a file called mytoc.c. Mytoc()'s
signature must also be provided in a "header" file named mytoc.h.
Write file named test.c containing a test program that includes the
header file mytoc.h. The behavior of this program is described below.
Write a Makefile that compiles the two source files and links them to
build a functional test program named "test".  A description of mytoc:

In general, tokenizers partition a character string into individual
tokens (words) separated by reserved "delimiter characters".? In this
case, the delimiter character is the space character and tokens
contain any characters other than space characters.

Your function "mytoc" should have the following signature:

char ** mytoc(char *str, char delim) A call to mytoc() should return a
freshly allocated null-terminated array of pointers to freshly
allocated strings containing each "token" from the input string. The
input string can be of any length, and should not be modified. The
vector returned by mytoc() and the strings referenced by it, should
all be allocated using malloc or calloc (so that it would be
appropriate to free() them). Finally, these dynamically allocated
blocks of memory should not be larger (or smaller) than required.

For example, a call to mytoc("hello world", ' ') should return the
address of an array containing:

 {"hello", "world", (char*)0} Other than malloc/calloc/free, your
implementation of mytoc should only call functions written by you. In
particular, calls to functions whose prototypes are in "string.h" such
as "strtok()" are prohibited.



