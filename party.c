#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heder.h"


int Party_Registration();

int loging_party() {
    doubleline();
    printf("               Party Login Portal\n");
    doubleline();

    char username[10];
    char pwd[10];
    char choice;

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", pwd);

    if (strcmp(username, "party") == 0 && strcmp(pwd, "passparty") == 0) {
        
            Party_Registration();
           
           
   
    } else {
        printf("Invalid login credentials!\n");
    }

    return 0;
}

int Party_Registration() {
    system("cls");
    char name[20];
    int code;
    char leader[25];
    FILE *fp;

    doubleline();
    printf("\t\tWELCOME TO THE PARLIAMENT ELECTION SYSTEM\n");
    doubleline();
    printf("\n\t\t----------- Party Registration ------------\n");

    printf("Enter Party Name: ");
    scanf("%s", name);
    printf("Enter Party Code: ");
    scanf("%d", &code);
    printf("Enter Party Leader: ");
    scanf("%s", leader);

    fp = fopen("Party_Registration.txt", "a"); 

    if (fp == NULL) {
        printf("File does not exist, please check!\n");
        return 1;
    }

    fprintf(fp, "%s %d %s\n", name, code, leader);
    fclose(fp);
    printf("Party Registered Successfully!\n");

    return 0;
}













