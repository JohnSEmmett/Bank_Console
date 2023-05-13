#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define character_limit 25


struct username {
    char username[25];
    char password[25];
};

//Return Functions : BOOLS -

bool int_check_grt(int a, int b) {
    bool validity;
    if(a <= b) {
        return true;
    } else {
        return false;
    }
}

bool int_check_lsr(int a, int b) {
    bool validity;
    if(a <= b) {
        return false;
    } else {
        return true;
    }
}
bool string_check(char* ss, int count) {
    if(strlen(ss) <= count) {
        return true;
    } else return false;
}

//struc funcs :

void createUser(struct username* p_dummy) {
    char storage[500];
    do {
        scanf("%s", storage);
        if (string_check(storage, character_limit) == false) {
            printf("ERROR: EXCEEDED CHAR LIMIT");
        } else {
            strcpy(p_dummy->username, storage);
        } 
    } while (!string_check(storage, character_limit));
}
void createPass(struct username* p_dummy) {
    char local[500];
        do{
        scanf("%s", &local); 
        if (string_check(local, character_limit) == false) {
            printf("ERROR: EXCEEDED CHAR LIMIT");
        } else {
            strcpy(p_dummy->password, local);
           
        }
    } while (!string_check(local, character_limit));
}

