#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "heder.h"

int voter_logged_in = 0;
char logged_voter_nic[20];
char logged_voter_name[100];
char logged_voter_district[20];

// Function to verify voter credentials and login
void voter_login() {
    char username[50];
    char password[25];
    char line[500];
    int login_success = 0;
    
    FILE *fp;
    
    system("cls");
    doubleline();
    printf("           VOTER LOGIN PAGE              \n");
    doubleline();
    
    printf("\nEnter username: ");
    scanf("%s", username);
    
    printf("Enter password: ");
    scanf("%s", password);
    
    separator();
    
    fp = fopen("voter registration data.txt", "r");
    
    if (fp == NULL) {
        printf("\n✗ No registered voters found!\n");
        printf("Please register first (Option 2).\n\n");
        separator();
        return;
    }
    
    // File format: name|age|district|username|nic|password
    while (fgets(line, sizeof(line), fp) != NULL) {
        char file_name[100], file_district[20], file_username[50];
        char file_nic[20], file_password[25];
        int file_age;
        
        int fields = sscanf(line, "%[^|]|%d|%[^|]|%[^|]|%[^|]|%s",
                           file_name, &file_age, file_district, 
                           file_username, file_nic, file_password);
        
        if (fields == 6) {
            if (strcmp(username, file_username) == 0 && 
                strcmp(password, file_password) == 0) {
                login_success = 1;
                strcpy(logged_voter_name, file_name);
                strcpy(logged_voter_nic, file_nic);
                strcpy(logged_voter_district, file_district);
                break;
            }
        }
    }
    
    fclose(fp);
    
    if (login_success) {
        voter_logged_in = 1;
        system("cls");
        doubleline();
        printf("✓ LOGIN SUCCESSFUL!\n");
        doubleline();
        printf("\n   Welcome, %s!\n", logged_voter_name);
        printf("   NIC: %s\n", logged_voter_nic);
        printf("   District: %s\n\n", logged_voter_district);
        separator();
    } else {
        system("cls");
        doubleline();
        printf("✗ LOGIN FAILED!\n");
        doubleline();
        printf("\n   Invalid username or password.\n");
        printf("   Please try again or register first.\n\n");
        separator();
    }
}


