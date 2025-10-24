#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include "heder.h"

int candidate_logged_in = 0;
char logged_candidate[100];



void candidate_login(){
    char username[55];
    char password[25];
    char line[500];
    int login_success = 0;
    
    FILE *fp;
    
    system("cls");  
    
    doubleline();
    printf("=================CANDIDATE LOGIN PAGE=================\n");
    doubleline();
    
    printf("Enter username: ");
    scanf("%s", username);
    
    printf("Enter password: ");
    scanf("%s", password);
    
    separator();
    
    
    fp = fopen("candidate registration data.txt", "r");
    
    if (fp == NULL){
        printf("\n No registered candidates found!\n");
        printf("Please register first .\n\n");
        separator();
        return;
    }
    
    
    while(fgets(line, sizeof(line), fp) != NULL){
        char file_name[100], file_party[150], file_district[25];
        int file_election_number;
        char file_nic[50], file_username[55], file_password[25];
        
        
        int fields = sscanf(line, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%s",
                           file_name, file_party, file_district, 
                           &file_election_number, file_nic, 
                           file_username, file_password);
        
        
        if(fields == 7){
            
            if(strcmp(username, file_username) == 0 && 
               strcmp(password, file_password) == 0){
                login_success = 1;
                strcpy(logged_candidate, file_name);
                break;
            }
        }
    }
    
    fclose(fp);
    
    if(login_success){
        candidate_logged_in = 1;
        doubleline();
        printf("\033[1;32mLOGIN SUCCESSFUL!\033[0m\n");
       
        doubleline();
        printf("\n   Welcome, %s!\n", logged_candidate);
        printf("   You are now logged in as a candidate.\n\n");
        
        //add polling
        
    } else {
        doubleline();
        printf("LOGIN FAILED!\n");
        doubleline();
        printf("\n   Invalid username or password.\n");
        printf("   Please try again or register first.\n\n");
        
    }
}


int is_candidate_logged_in(){
    return candidate_logged_in;
}


void candidate_logout(){
    candidate_logged_in = 0;
    strcpy(logged_candidate, "");
    printf("\033[1;32mYou have been logged out successfully.\033[0m\n");
 
}
