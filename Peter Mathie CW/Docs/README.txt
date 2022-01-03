HOW TO COMPILE/USE THE STARTER CODE FOR: F29LP CW2.1 Part I |
____________________________________________________________|

This is starter code in C for F29LP CW2.1: parser for the FUNC language. Files (initially) in this folder:

- CW2.1.pdf: the coursework specification
- func.lex: a VERY parțial specification of the lexical rules for FUNC
- tokens.h: this is where you need to define all the constants corresponding to all the tokens/terminals in FUNC
- parser.c: starter code including some helper functions for the FUNC parser (no AST - Task 2 of the) CW)
- ast-parser.c: starter code including some helper functions for the FUNC AST parser (Task 3 of the CW)
- Makefile: the make file for compiling parser.c or ast-parser.c. You shouldn't need to edit this file.
- tree.h: header file containing an definitions for multiple branching trees
- tree.c: implementation of tree manipulation operations declared in tree.h
- this readme.txt file
- ex1.func & ex2.func: two example FUNC programmes from the Coursework specification.


NOTE: The code already compiles, but of course does not do anything until you implement parser.c & ast-parser.c!

----------------------------------------


For CW2.1, Task 1: 

You need to complete the lexical specification file, func.flex; then generate the lexical analyser using FLEX. You can do this by running flex on the lexical specification file, func.flex (which is initially very partially specified for you):

$ flex func.lex

This will generate your FUNC lexical analyser as lex.yy.c

----------------------------------------

For Task 2:

To compile the parser (CW2.1 Task 2) type the following commands into your terminal (assumes you have gcc installed):

$ make clean (remove old .o & executables)
$ make parser (compile parser.c)

You can then run the parser executable on a text file that contains a FUNC program (e.g. ex1.func) as follows:

$ ./parser ex1.func

----------------------------------------

For Task 3:

To compile the AST parser type the following commands into your terminal (assumes you have gcc installed):

$ make clean (remove old .o & executables)
$ make ast-parser (compile ast-parser.c)

You can then run the parser executable on a text file that contains a FUNC program (e.g. ex1.func) as follows:

$ ./parser ex1.func

----------------------------------------
