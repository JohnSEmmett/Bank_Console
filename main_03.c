/*
    WELCOME: J & J Banking is a application built by John Emmett and compiled using MinGW v6.3.0-1.
    Goal: Build a banking application using a RDBMS and a simple Schema to store accounts created in a db file local to the program.
    Thus, it is suggested that the program is left as is and is compiled using CMD if a rebuild is neccesary.
    General Outline of the Program and it's functionality...
    First, I'd like to be able to have the user create or login to a account. In doing so, I expect the following structure to be followed...
    Prompt User (Login or Create) --> CREATE (Check Input --> Update to Database) LOGIN (Check Input via DBMS ---> Output Account details)
    Enable client to:
        1. Send money.
        2. Receive Money.
        3. Deposit.
        4. Withdraw.
*/




#include <stdio.h>
#include "sqlite3.h"
#include <string.h>
#include "C:\Users\jsemm\OneDrive\Desktop\Connections\sqlite\sqlite-amalgamation-3410200\module.h"

int callback(void *data, int argc, char **argv, char **colNames) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", colNames[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main() {
    // Begin Program : Will probably use a switch here to navigate through various options
    /*do {

    } while ();
    */

    printf("\n \t Starting program...");
    struct username acc_one;
    //
    //Setting up the Database Engine and Error handler
    printf("\t*******************Program Analysis******************");
    printf("\nCreating Instance of SQLite object with a container for DB...");
    sqlite3 *db;
    char *errMsg = NULL;


    // Create string for DB's path
    printf("\nAttempting to connect to the Database...");
    const char *dbPath = "C:\\Users\\jsemm\\OneDrive\\Desktop\\Connections\\database\\connectionsdata.db";
    printf("\t File: %s", dbPath);
    int rc = sqlite3_open(dbPath, &db);
    
    //Handle the error if the database cannot be opened due to the path being incorrect
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    } printf("\nConnection to Database Succesfull: \t File: %s \tOPENED\n\n", dbPath);
    createAccount(&acc_one);
    insert_into_db(db, dbPath, &acc_one);

    // SQL STATEMENTS:
    const char *selectALL = "SELECT * FROM client;";
    

    //Executing statements
    /*
        Program should execute in order similar to this:
        - After program is ran, it will prompt two choices, create account and sign on.
        - You can open two DB's from the same file...
        - Therefore, if client selects create then we need to take the information from the struct header file and update it to the table.
        - Predefined statements that are updated to the struct may be useful...
    */
    // EXECUTION OF STATEMENTS:
    // rc = sqlite3_exec(db, selectALL, callback, 0, &errMsg);
    rc = sqlite3_exec(db, selectALL, callback, 0, &errMsg);
    //Check to see if statements were executed properly
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot select data: %s\n", errMsg);
        sqlite3_free(errMsg);
        return 1;
    }
    
    // Close database
    sqlite3_close(db);
    
    return 0;
}
