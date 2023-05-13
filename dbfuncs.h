#include <stdio.h>
#include <string.h>
#include "sqlite3.h"
#include "username_password_struct.h"
#include "account_info.h"
#include <stdbool.h>
int signIn(sqlite3* db, const char* dbPath) {
    char username[50];
    char password[50];
    char stmt[1000];
    char s_stmt[1000];
    sqlite3_stmt* selectStmt;
    sqlite3_stmt* displayDetails;
    bool signed_in;
    int rc = sqlite3_open(dbPath, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to open the database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    printf("\nUsername: ");
    scanf("%49s", username);
    printf("\nPassword: ");
    scanf("%49s", password);

    snprintf(stmt, sizeof(stmt), "SELECT * FROM AccountInfo WHERE username = '%s' AND password = '%s';", username, password);

    rc = sqlite3_prepare_v2(db, stmt, -1, &selectStmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare the SELECT statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    rc = sqlite3_step(selectStmt);
    if (rc == SQLITE_ROW) {
        printf("\nSign-in successful!\n");
        signed_in = true;
        printf("\nWelcome: %s ", sqlite3_column_text(selectStmt, 1));
        printf("Account ID: %s\n", sqlite3_column_text(selectStmt, 0));
        sqlite3_finalize(selectStmt);

        printf("Displaying Details\n");
        snprintf(s_stmt, sizeof(s_stmt), "SELECT * FROM personal_info AS pi JOIN AccountInfo AS ai ON pi.accID = ai.accID WHERE ai.username = '%s';", username);
        rc = sqlite3_prepare_v2(db, s_stmt, -1, &displayDetails, NULL);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "\nCannot find account: %s\n", sqlite3_errmsg(db));
            sqlite3_finalize(displayDetails);
            sqlite3_close(db);
            return -1;
        }

        rc = sqlite3_step(displayDetails);
        if (rc == SQLITE_ROW) {
            printf("\nAccount First Name: %s", sqlite3_column_text(displayDetails, 1));
            printf("\nAccount Last Name: %s", sqlite3_column_text(displayDetails, 2));
            printf("\nAccount Birthday: %s", sqlite3_column_text(displayDetails, 3));
            printf("\nAccount Phone Number: %s", sqlite3_column_text(displayDetails, 4));
            printf("\nAccount Balance: $%d", sqlite3_column_int(displayDetails, 5));
            sqlite3_finalize(displayDetails);
        } else {
            printf("\nInvalid account\n");
            sqlite3_finalize(displayDetails);
            sqlite3_close(db);
            return -1;
        }
    } else {
        printf("\nInvalid username or password!\n");
        sqlite3_finalize(selectStmt);
        sqlite3_close(db);
        return -1;
    }

    sqlite3_close(db);
    return 0;
}


void sendMoney(sqlite3* db, const char* dbPath) {
    char senderUsername[50];
    char recipientUsername[50];
    double amount;
    char stmt[1000];
    sqlite3_stmt* selectStmtSender;
    sqlite3_stmt* selectStmtRecipient;

    int rc = sqlite3_open(dbPath, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to open the database: %s\n", sqlite3_errmsg(db));
        return;
    }

    printf("\nSender's First Name: ");
    scanf("%49s", senderUsername);
    printf("\nRecipient's First Name: ");
    scanf("%49s", recipientUsername);
    printf("\nAmount to Send: ");
    scanf("%lf", &amount);

    // Fetch sender's balance
    snprintf(stmt, sizeof(stmt), "SELECT balance FROM personal_info WHERE first_name = '%s';", senderUsername);
    rc = sqlite3_prepare_v2(db, stmt, -1, &selectStmtSender, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare the SELECT statement for sender: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_step(selectStmtSender);
    if (rc == SQLITE_ROW) {
        double senderBalance = sqlite3_column_double(selectStmtSender, 0);
        sqlite3_finalize(selectStmtSender);

        // Fetch recipient's balance
        snprintf(stmt, sizeof(stmt), "SELECT balance FROM personal_info WHERE first_name = '%s';", recipientUsername);
        rc = sqlite3_prepare_v2(db, stmt, -1, &selectStmtRecipient, NULL);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Failed to prepare the SELECT statement for recipient: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return;
        }

        rc = sqlite3_step(selectStmtRecipient);
        if(rc == SQLITE_ROW) {
            double senderBalance = sqlite3_column_double(selectStmtSender, 0);
            double recipientBalance = sqlite3_column_double(selectStmtRecipient, 0);
            sqlite3_finalize(selectStmtRecipient);

            if (senderBalance >= amount) {
                senderBalance -= amount;
                recipientBalance += amount;

                // Update the sender's balance
                snprintf(stmt, sizeof(stmt), "UPDATE personal_info SET balance = %.2f WHERE first_name = '%s';", senderBalance, senderUsername);
                rc = sqlite3_exec(db, stmt, 0, 0, NULL);
                if (rc != SQLITE_OK) {
                    fprintf(stderr, "Failed to update the sender's balance: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return;
                }

                // Update the recipient's balance
                snprintf(stmt, sizeof(stmt), "UPDATE personal_info SET balance = %.2f WHERE first_name = '%s';", recipientBalance, recipientUsername);
                rc = sqlite3_exec(db, stmt, 0, 0, NULL);
                if (rc != SQLITE_OK) {
                    fprintf(stderr, "Failed to update the recipient's balance: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return;
                }

                printf("\nMoney sent successfully!\n");
            } else {
                printf("\nInsufficient balance!\n");
            }
        } else {
            printf("\nRecipient account not found!\n");
            sqlite3_finalize(selectStmtRecipient);
        }
    } else {
        printf("\nSender account not found!\n");
        sqlite3_finalize(selectStmtSender);
    }

    sqlite3_close(db);
}



void insert_into_db(sqlite3* db, const char* dbPath, struct username* atp_one) {
    int rc = sqlite3_open(dbPath, &db);
    char sqlstmt[1000];
    snprintf(sqlstmt, sizeof(sqlstmt), "INSERT INTO AccountInfo(username, password) VALUES ('%s', '%s');", atp_one->username, atp_one->password);
    rc = sqlite3_exec(db, sqlstmt, 0, 0, NULL);
    sqlite3_close(db);
    printf("\nAccount Has Been Created\n");
}


void acc_insert_into(sqlite3* db, const char* dbPath, struct account_info* p_dummy) {
    int rc = sqlite3_open(dbPath, &db);
    char stmt[1000];

    // Insert personal information into the 'personal_info' table
    snprintf(stmt, sizeof(stmt), "INSERT INTO personal_info(accID, first_name, last_name, age_of_birth, phone_number, balance) VALUES ((SELECT accID FROM AccountInfo ORDER BY accID DESC LIMIT 1), '%s', '%s', '%s', '%s','%d');",
        p_dummy->first_name, p_dummy->last_name, p_dummy->date_of_birth, p_dummy->phone_number, p_dummy->account_balance);
    rc = sqlite3_exec(db, stmt, 0, 0, NULL);
    sqlite3_close(db);
    printf("\nPersonal information has been added to the corresponding account.\n");
}

void display_current_names(sqlite3* db, const char* dbPath) {
    char stmt[1000];
    sqlite3_stmt *selectNames;
    
    int rc = sqlite3_open(dbPath, &db);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "ERROR: Opening File: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }
    
    snprintf(stmt, sizeof(stmt), "SELECT first_name FROM personal_info");
    
    rc = sqlite3_prepare_v2(db, stmt, -1, &selectNames, NULL);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "ERROR: Failed to prepare the SELECT statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }
    
    printf("Current Names:\n");
    
    while(sqlite3_step(selectNames) == SQLITE_ROW) {
        const unsigned char *name = sqlite3_column_text(selectNames, 0);
        printf("%s\n", name);
    }
    
    sqlite3_finalize(selectNames);
    sqlite3_close(db);
}
