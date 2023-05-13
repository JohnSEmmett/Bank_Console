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
#include <windows.h>
#include <string.h>
#include "headers/sqlite3.h"
#include "headers/dbfuncs.h"


int callback(void *data, int argc, char **argv, char **colNames) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", colNames[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main() {
    sqlite3 *db;
    const char *dbPath = "C:\\Users\\jsemm\\OneDrive\\Desktop\\Connections\\database\\connectionsdata.db";
    int choice;
    int deposit = 0;

    do {
        printf("\nWelcome to J & J Banking!");
        printf("\nPlease select an option:");
        printf("\n1. Sign In");
        printf("\n2. Create Account");
        printf("\n3. Exit");
        printf("\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                signIn(db, dbPath);
                sendMoney(db, dbPath);
                printf("\n\t List of Available Accounts");
                break;
            case 2: {
                struct username acc_handle;
                struct account_info acc_one;

                printf("\nCreate User: ");
                createUser(&acc_handle);
                printf("\nCreate Pass: ");
                createPass(&acc_handle);
                insert_into_db(db, dbPath, &acc_handle);

                printf("\nCreate First: ");
                set_first(&acc_one);
                printf("\nCreate Last: ");
                set_last(&acc_one);
                printf("\nCreate birth: ");
                set_birth(&acc_one);
                printf("\nCreate number: ");
                set_number(&acc_one);
                printf("\nDeposit Amount: \n");
                scanf("%d", &deposit);
                set_balance(&acc_one, deposit);

                acc_insert_into(db, dbPath, &acc_one);
                printf("\nAccount created successfully!");

                // Redirect back to sign in
                signIn(db, dbPath);
                sendMoney(db, dbPath);
                break;
            }
            case 3:
                printf("\nExiting...");
                break;
            default:
                printf("\nInvalid choice. Please try again.");
                break;
        }

    } while (choice != 3);

    return 0;
}
