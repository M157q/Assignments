## Homework Assignment 3 
### An AST builder for the C-- Language
### (Posted on 04/16, Due 04/28 11:59PM)

---

### Homework#3: A syntax recognizer and AST (Abstract Syntax Tree) generation for C— programs
    
#### Part 1.
In the template file, parser.y,  
we have provided an incomplete set of C— production rules.  
Your job is to fill the missing productions  
(they are marked by C comments, e.g. /**/)  
so that the parser you created through Yacc/Bison can parse correct C— programs.

---

#### Part 2.
In a multi-pass compiler,  
we usually generate an AST during the syntax checking pass.  
A few follow-up passes such as semantic checking and code generation can be performed based on the AST.  
You are required to build the AST using the node structure we provided in the header.h.  
In the parser.y template file,  
you need to add action routines to build the AST.  
There are some AST building action routines already added.  
However, the majority of such actions are missing from the parser.y file.  
They are marked by C comments, e.g. /**/,  
and you need to fill in such actions.  
The generated AST will be printed out to an AST.gv file via the printGV() call  
(This has been coded in the parser.y main function).  
TAs will check the correctness of the AST generated from your parser.  
AST.gv can be viewed graphically by the GVedit tool,  
(you can download from http://www.graphviz.org/ ).  
That graphic layout could help you see the AST structures better and debug your action routines more effectively.  

Additional Notes:  
+ You may assume the identifier names will not exceed 256 characters. However, the number of distinct identifiers should not be limited.
+ In the Homework3  directory you may find the following files:
    + src/lexer.l      the sample lex program that you may start with
    + src/header.h     contains AST data structures
    + src/Makefile
    + src/parser.y         template YACC file with incomplete production rules
    + src/functions.c  functions that can be used to generate the AST.gv
    + pattern/*.c      test data files
    + tar.sh       packaging script file
       
---

### Submission requirements:

1) DO NOT change the executable name (parser).  
2) Use the script file “tar.sh” to wrap up your assignment works into a single file. Then upload your packaged file to e3 (or send to TA)  

```
Usage: ./tar.sh source_directory studentID1_studentID2 (all student IDs in your team) version_number
Example: ./tar.sh hw 12345_12346 ver1
Output: 12345_12346_ver1.tar.bz2 (submit this file)
```

3) We grade the assignments on the linux1 workstation. Before summiting your assignment, you should make sure your version works correctly on linux1.


See sample directory in hw3 zipped files for examples of AST.
