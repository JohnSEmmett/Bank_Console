#include <stdio.h>
#include <string.h>

#define start_balance 0
#define char_constant 50
#define birth_constant 8
#define number_constant 10


struct account_info {
    char first_name[50];
    char last_name[50];
    char date_of_birth[8];
    char phone_number[13];
    int account_balance;
};
//For future coding: 
//We will take the set functions and use them in combinaton with get functions written in another H file. but for now we will keep it as such.
void set_first(struct account_info* p_dummy) {
    char input[500];
    bool control = true;
    do{
        scanf("%s", input);
        if(strlen(input) <= char_constant) {
            strcpy(p_dummy->first_name, input);
            control = false;
        } else {
            printf("ERROR: Too many Characters"); 
        }
    } while (control);
}
void set_last(struct account_info* p_dummy) {
    char input[500];
    do {
        scanf("%s", input);
        if(strlen(input) <= char_constant) {
            strcpy(p_dummy->last_name, input);
        } else {
            printf("ERROR: Too many Characters");
        }
    } while(strlen(input) > char_constant);
}
void set_birth(struct account_info* p_dummy) {
    char input[500];
    do {
        scanf("%s", input);
        if(strlen(input) == 10 && input[2] == '/' && input[5] == '/') {
            strcpy(p_dummy->date_of_birth, input);
        } else {
            printf("Invalid input. Please enter a valid date in the format MM/DD/YYYY.\n");
        } 
    } while(strlen(input) != 10 || input[2] != '/' || input[5] != '/');
}
void set_number(struct account_info* p_dummy) {
    char input[500];
    do {
        scanf("%s", input);
        if(strlen(input) == 12 && input[3] == '-' && input[7] == '-') {
            strcpy(p_dummy->phone_number, input);
        } else {
            printf("Invalid input. Please enter a valid phone number in the format 222-222-2222.\n");
        }
    } while(strlen(input) != 12 || input[3] != '-' || input[7] != '-');
}

void getBalance(struct account_info* p_dummy) {
    printf("\nAccount Balance: \t$%d", p_dummy->account_balance);
}

void set_balance(struct account_info* p_dummy, int amnt) {
    p_dummy -> account_balance = amnt;
}
