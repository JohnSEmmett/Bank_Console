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
    printf("\nRunning program...");
    printf("Generating Accounts");
    //Use structure from module.h header file
    //
    struct username first_account;
    createAccount(&first_account);
    output(&first_account);
    //
    //Setting up the Database Engine and Error handler
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
    }
    // Select data
    printf("\nConnection to Database Succesfull: \t File: %s \tOPENED\n\n", dbPath);
    const char *selectSQL = "SELECT * FROM client;";
    const char *insertSQL = "UPDATE client SET First = 'John' WHERE First = 'Jack';";
    rc = sqlite3_exec(db, selectSQL, callback, 0, &errMsg);
    rc = sqlite3_exec(db, insertSQL, callback, 0, &errMsg);
     rc = sqlite3_exec(db, selectSQL, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot select data: %s\n", errMsg);
        sqlite3_free(errMsg);
        return 1;
    }
    
    // Close database
    sqlite3_close(db);
    
    return 0;
}
