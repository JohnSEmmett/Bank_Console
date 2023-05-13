# Bank_Console

NOTES FROM PUBLISHER:
 This is my first project using an external library such as SQLite3. I initially struggled to compile the SQlite3 Amagalation package but managed to get it set up properly.
 The program has a lot left to be desired, it needs to be modified to fix security issues with the inputs regarding the header files. It also needs to implement/call functions in a seperate file in order to prevent SQL Injections.
 Overall, I am very pleased with how the initial project came out and as a result of how it is programmed, should be able to be updated routinely and made better.
 I really wanted to practice using external libraries in order to build a scalable and robust but lightweight windows console application. 
 This project enabled me to deepen my understanding of the various concepts in C such as but not limited to, exception handling, file management, functions, external libraries, external libraries functionality.
 More concepts were used and implemented but would be tiring listing.. therefore I leave you with a few more notes.
 
 HOW THE PROGRAM WORKS:
 
  In order for this program to work, you will need to use SQLite3's various files...
  SQLite3.c and your program_main_code.c need to be in the same directory / folder.
  You will also need Sqlite3.h and SQLite3.lib. These files are absolutely required in order to access the neccesary header files needed at compilation.
  ** Remember to include the DDL Paths to the compiler, esepcially when using a windows or mac operating system. **
  
  The program will prompt you with three options, more options will be implemented at a later point.
  The three options are as follows, 
  first, create an account.
  second, sign into an account.
  third, quit.
  Eventually, there will be a search filter to search for contacts and an option to directly go in and either send money or deposit money.
  Lets say you create an account... The program utilizes the various header files to create structs pertaining to a username and a password, once completed we will call a function from the dbfunc.h file in order to update the stored values into the database.
  The same processs occurs for inputting first, last, birthdate, and phone numbers. 
  After the information is updated to the database the user will be prompted to sign in, use the account you just created.
  Then you will be prompted to send money, this is by default and again, will be changed.
  
I will also be adding additional error handling that will be rolled out someime in the coming week.

ADDTIONAL COMMENTS FROM PUBLISHER:

I did not create the SQL files needed for the program to work, as I stated earlier, I used SQLite3's Amagalation Package and followed the steps to set up and compile shell cmd and DLL library.
I used MinGW version 6.0.3.1 and VS Code as my IDE... Compiled in CMD using the cmd, gcc main.c sqlite3.c -o program_name -L{Directory where library is stored} - lsqlite3

