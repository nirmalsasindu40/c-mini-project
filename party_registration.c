#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heder.h"

// Party registration function
int Party_Registration() {
    system("cls");
    char name[100];
    int code;
    char leader[100];
    char password[25];
    char username[50];
    FILE *fp;

    doubleline();
    printf("PARTY REGISTRATION\n");
    doubleline();
    
    printf("\nEnter Party name: ");
    scanf("%s", name);

    printf("Enter Party username: ");
    scanf("%s", username);
    
    printf("Enter Party password: ");
    scanf("%s", password);

    printf("Enter Party Code: ");
    while(scanf("%d", &code) != 1) {
        printf("Invalid input! Please enter a number: ");
        while(getchar() != '\n');
    }

    printf("Enter Party Leader name: ");
    scanf("%s", leader);

    fp = fopen("party_Registration.txt", "a"); 

    if (fp == NULL) {
        printf("\nError: Could not open file for registration!\n");
        separator();
        return 1;
    }

    // Format MUST match party_login.c: PartyName|PartyCode|Leader|Username|Password
    fprintf(fp, "%s|%d|%s|%s|%s\n", name, code, leader, username, password);
    fclose(fp);
    
    system("cls");
    doubleline();
    printf("REGISTRATION SUCCESSFUL\n");
    doubleline();
    printf("\nParty '%s' has been registered successfully!\n", name);
    printf("Party Code: %d\n", code);
    printf("Leader: %s\n\n", leader);
    separator();

    return 0;
}

// Admin login for party registration
int loging_party() {
    system("cls");
    doubleline();
    printf("PARTY REGISTRATION PORTAL\n");
    doubleline();

    char username[50];
    char pwd[50];

    printf("\nAdmin Authentication Required\n");
    separator();
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", pwd);

    // Simple admin verification for party registration
    if (strcmp(username, "party") == 0 && strcmp(pwd, "passparty") == 0) {
        system("cls");
        doubleline();
        printf("AUTHENTICATION SUCCESSFUL\n");
        doubleline();
        printf("\nAccess granted for party registration.\n");
        separator();
        
        Party_Registration();
    } else {
        system("cls");
        doubleline();
        printf("AUTHENTICATION FAILED\n");
        doubleline();
        printf("\nInvalid admin credentials!\n");
        printf("Access denied for party registration.\n\n");
        separator();
    }

    return 0;
}