#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "heder.h"

int voter_logged_in = 0;
char logged_voter_name[100];
char logged_voter_nic[50];
char logged_voter_district[50];
int logged_voter_age = 0;

// Function to verify voter credentials
int verify_voter_login(char *username, char *password, char *voter_name, 
                       char *voter_nic, char *voter_district, int *voter_age) {
    FILE *fp;
    char line[500];
    char file_name[100], file_username[50], file_nic[50], file_password[25], file_district[50];
    int file_age;
    
    fp = fopen("voter registration data.txt", "r");
    
    if (fp == NULL) {
        return 0;
    }
    
    // Format: name|age|district|username|nic|password
    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%[^|]|%d|%[^|]|%[^|]|%[^|]|%s",
               file_name, &file_age, file_district, file_username, file_nic, file_password);
        
        if (strcmp(username, file_username) == 0 && 
            strcmp(password, file_password) == 0) {
            strcpy(voter_name, file_name);
            strcpy(voter_nic, file_nic);
            strcpy(voter_district, file_district);
            *voter_age = file_age;
            fclose(fp);
            return 1;
        }
    }
    
    fclose(fp);
    return 0;
}

// Check if voter has voted
int check_if_voted(char *nic) {
    FILE *fp;
    char line[100];
    char file_nic[50];
    
    fp = fopen("voted_voters.txt", "r");
    
    if (fp == NULL) {
        return 0;
    }
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%s", file_nic);
        
        if (strcmp(file_nic, nic) == 0) {
            fclose(fp);
            return 1;
        }
    }
    
    fclose(fp);
    return 0;
}

// View voter profile
void view_voter_profile() {
    system("cls");
    doubleline();
    printf("VOTER PROFILE\n");
    doubleline();
    
    printf("\nName:              %s\n", logged_voter_name);
    printf("Age:               %d\n", logged_voter_age);
    printf("District:          %s\n", logged_voter_district);
    printf("NIC:               %s\n", logged_voter_nic);
    
    if (check_if_voted(logged_voter_nic)) {
        printf("Voting Status:     VOTED\n");
    } else {
        printf("Voting Status:     NOT VOTED\n");
    }
    
    printf("\n");
    separator();
}

// View candidates in voter's district
void view_my_candidates() {
    FILE *fp;
    char line[500];
    char name[100], party[150], district[25];
    int election_number;
    char nic[50], username[55], password[25];
    int count = 0;
    
    system("cls");
    doubleline();
    printf("CANDIDATES IN YOUR DISTRICT (%s)\n", logged_voter_district);
    doubleline();
    
    fp = fopen("candidate registration data.txt", "r");
    
    if (fp == NULL) {
        printf("\nNo candidates registered yet!\n\n");
        separator();
        return;
    }
    
    printf("\n%-5s %-20s %-20s %-15s\n", 
           "No.", "Name", "Party", "Election No.");
    separator();
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%s",
               name, party, district, &election_number, nic, username, password);
        
        // Simple case insensitive compare
        char dist_lower[50], voter_dist_lower[50];
        int i;
        
        for (i = 0; district[i]; i++) {
            if (district[i] >= 'A' && district[i] <= 'Z')
                dist_lower[i] = district[i] + 32;
            else
                dist_lower[i] = district[i];
        }
        dist_lower[i] = '\0';
        
        for (i = 0; logged_voter_district[i]; i++) {
            if (logged_voter_district[i] >= 'A' && logged_voter_district[i] <= 'Z')
                voter_dist_lower[i] = logged_voter_district[i] + 32;
            else
                voter_dist_lower[i] = logged_voter_district[i];
        }
        voter_dist_lower[i] = '\0';
        
        if (strcmp(dist_lower, voter_dist_lower) == 0) {
            count++;
            printf("%-5d %-20s %-20s %-15d\n",
                   count, name, party, election_number);
        }
    }
    
    if (count == 0) {
        printf("\nNo candidates registered for your district yet!\n");
    } else {
        printf("\nTotal Candidates: %d\n", count);
    }
    
    printf("\n");
    separator();
    fclose(fp);
}

// View voting instructions
void view_voting_instructions() {
    system("cls");
    doubleline();
    printf("VOTING INSTRUCTIONS\n");
    doubleline();
    
    printf("\nHow to Vote:\n");
    printf("1. Go to Main Menu and select 'Polling (Cast Vote)'\n");
    printf("2. Enter your username and password\n");
    printf("3. View candidates from your district\n");
    printf("4. Enter the name of your chosen candidate\n");
    printf("5. Confirm your vote\n");
    
    printf("\nImportant Notes:\n");
    printf("- You can only vote ONCE\n");
    printf("- You can only vote for candidates in YOUR district (%s)\n", logged_voter_district);
    printf("- Your vote is confidential\n");
    printf("- Polling must be active to cast your vote\n");
    
    printf("\n");
    separator();
}

// Check polling status
void check_polling_status() {
    system("cls");
    doubleline();
    printf("POLLING STATUS\n");
    doubleline();
    
    if (is_polling_active()) {
        printf("\nPolling Status:    ACTIVE\n");
        printf("You can cast your vote now!\n");
        
        if (check_if_voted(logged_voter_nic)) {
            printf("\nNote: You have already voted.\n");
        } else {
            printf("\nYou have not voted yet. Please go to 'Polling (Cast Vote)' to vote.\n");
        }
    } else {
        printf("\nPolling Status:    INACTIVE\n");
        printf("Polling is not active at the moment.\n");
        printf("Please wait for the admin to start polling.\n");
    }
    
    printf("\n");
    separator();
}

// Voter dashboard
void voter_dashboard() {
    char choice;
    
    do {
        printf("\n");
        doubleline();
        printf("VOTER DASHBOARD - %s\n", logged_voter_name);
        doubleline();
        
        printf("\n1. View My Profile\n");
        printf("2. View Candidates in My District\n");
        printf("3. Check Polling Status\n");
        printf("4. Voting Instructions\n");
        printf("5. Go to Polling (Cast Vote)\n");
        printf("0. Logout\n\n");
        
        separator();
        
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        
        switch(choice) {
            case '1':
                view_voter_profile();
                break;
                
            case '2':
                view_my_candidates();
                break;
                
            case '3':
                check_polling_status();
                break;
                
            case '4':
                view_voting_instructions();
                break;
                
            case '5':
                if (check_if_voted(logged_voter_nic)) {
                    system("cls");
                    doubleline();
                    printf("ALREADY VOTED\n");
                    doubleline();
                    printf("\nYou have already cast your vote!\n");
                    printf("Each voter can only vote once.\n\n");
                    separator();
                } else {
                    system("cls");
                    doubleline();
                    printf("POLLING (CAST VOTE)\n");
                    doubleline();
                    polling();
                }
                break;
                
            case '0':
                voter_logged_in = 0;
                strcpy(logged_voter_name, "");
                strcpy(logged_voter_nic, "");
                strcpy(logged_voter_district, "");
                logged_voter_age = 0;
                
                system("cls");
                doubleline();
                printf("VOTER LOGOUT\n");
                doubleline();
                printf("\nYou have been logged out successfully.\n\n");
                separator();
                return;
                
            default:
                printf("\nInvalid choice! Please try again.\n\n");
                separator();
        }
        
    } while(choice != '0');
}

// Voter login
void voter_login() {
    char username[50];
    char password[25];
    int attempts = 0;
    
    system("cls");
    doubleline();
    printf("VOTER LOGIN\n");
    doubleline();
    
    while (attempts < 3) {
        printf("\nEnter voter username: ");
        scanf("%s", username);
        
        printf("Enter voter password: ");
        scanf("%s", password);
        
        if (verify_voter_login(username, password, logged_voter_name, 
                              logged_voter_nic, logged_voter_district, &logged_voter_age)) {
            voter_logged_in = 1;
            
            system("cls");
            doubleline();
            printf("LOGIN SUCCESSFUL\n");
            doubleline();
            printf("\nWelcome, %s!\n", logged_voter_name);
            printf("District: %s\n", logged_voter_district);
            
            if (check_if_voted(logged_voter_nic)) {
                printf("Voting Status: VOTED\n");
            } else {
                printf("Voting Status: NOT VOTED\n");
            }
            
            separator();
            
            voter_dashboard();
            return;
        } else {
            attempts++;
            system("cls");
            doubleline();
            printf("LOGIN FAILED\n");
            doubleline();
            printf("\nInvalid credentials! Attempt %d of 3\n", attempts);
            
            if (attempts >= 3) {
                printf("\nToo many failed attempts. Access denied.\n\n");
                separator();
                return;
            }
        }
    }
}

// Check if voter is logged in
int is_voter_logged_in() {
    return voter_logged_in;
}

// Voter logout
void voter_logout() {
    voter_logged_in = 0;
    strcpy(logged_voter_name, "");
    strcpy(logged_voter_nic, "");
    strcpy(logged_voter_district, "");
    logged_voter_age = 0;
    printf("\nVoter logged out successfully.\n\n");
    separator();
}