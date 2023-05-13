#include <stdio.h>
#include <string.h>
#include "sqlite3.h"

struct username {
    char first[25];
    char last[25];
    char username[50];
    char password[50];
};
void insert_into_db(sqlite3* db, const char* dbPath, struct username* atp_one) {
    int rc = sqlite3_open(dbPath, &db);
    char sqlstmt[50];
    snprintf(sqlstmt, sizeof(sqlstmt), "INSERT INTO client(first) VALUES ('%s');", atp_one->first);
    rc = sqlite3_exec(db, sqlstmt, 0, 0, NULL);
    sqlite3_close(db);
    printf("Changed");
}



void createAccount(struct username* p_dummy) {
    char input[250];

    printf("\nWelcome to J & J Banking: \nPlease answer the following...");
    //We will add checks to ensure that usernames are valid, etc.//
    printf("\nPlease Enter a Username \n");
    scanf("%s", &input);
    strcpy(p_dummy -> username, input);
    printf("\nPlease Enter a Password \n");
    scanf("%s", &input);
    strcpy(p_dummy-> password, input);
    printf("\nLets go ahead and get some more information...");
    printf("\nWhat is a good First Name? \n");
    scanf("%s", &input);
    strcpy(p_dummy-> first, input);
    printf("\nWhat is a good Last Name? \n");
    scanf("%s", &input);
    strcpy(p_dummy-> last, input);
}

void output(struct username* p_dummy) {
   

    printf("\n|||||||||||||||||||||  Welcome %s. ||||||||||||||||||||||", p_dummy->username);
    printf("\n*********************************************************\n");
    printf("* Username: %s                                       \n", p_dummy->username);
    printf("* Password: %s                                     \n", p_dummy->password);
    printf("* First Name: %s                                         \n", p_dummy->first);
    printf("* Last Name: %s                                     \n", p_dummy->password);
    printf("*                                                        \n");
    printf("*********************************************************\n");
}
