#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "heder.h"

int party_logged_in = 0;
char logged_party_name[100];
char logged_party_leader[100];
int logged_party_code = 0;

// Simple string compare (case insensitive)
int compare_strings(char *str1, char *str2) {
    int i;
    for (i = 0; str1[i] && str2[i]; i++) {
        char c1 = str1[i];
        char c2 = str2[i];
        
        // Convert to lowercase manually
        if (c1 >= 'A' && c1 <= 'Z') c1 = c1 + 32;
        if (c2 >= 'A' && c2 <= 'Z') c2 = c2 + 32;
        
        if (c1 != c2) return 0;
    }
    return (str1[i] == str2[i]);
}

// Function to verify party credentials
int verify_party(char *username, char *password, char *party_name, char *party_leader, int *party_code) {
    FILE *fp;
    char line[500];
    char file_name[100], file_leader[100];
    int file_code;
    char file_username[50], file_password[25];
    
    fp = fopen("party_login_data.txt", "r");
    
    if (fp == NULL) {
        return 0;
    }
    
    // Format: PartyName|PartyCode|Leader|Username|Password
    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%[^|]|%d|%[^|]|%[^|]|%s",
               file_name, &file_code, file_leader, file_username, file_password);
        
        if (strcmp(username, file_username) == 0 && 
            strcmp(password, file_password) == 0) {
            strcpy(party_name, file_name);
            strcpy(party_leader, file_leader);
            *party_code = file_code;
            fclose(fp);
            return 1;
        }
    }
    
    fclose(fp);
    return 0;
}

// View party registration status
void view_party_status() {
    system("cls");
    doubleline();
    printf("PARTY REGISTRATION STATUS\n");
    doubleline();
    
    printf("\nParty Name:        %s\n", logged_party_name);
    printf("Party Code:        %d\n", logged_party_code);
    printf("Party Leader:      %s\n", logged_party_leader);
    printf("Registration:      APPROVED\n");
    
    printf("\n");
    separator();
}

// View party candidates
void view_party_candidates() {
    FILE *fp;
    char line[500];
    char name[100], party[150], district[25];
    int election_number;
    char nic[50], username[55], password[25];
    int count = 0;
    
    system("cls");
    doubleline();
    printf("CANDIDATES FROM %s PARTY\n", logged_party_name);
    doubleline();
    
    fp = fopen("candidate registration data.txt", "r");
    
    if (fp == NULL) {
        printf("\nNo candidates registered yet!\n\n");
        separator();
        return;
    }
    
    printf("\n%-5s %-20s %-20s %-15s\n", 
           "No.", "Name", "District", "Election No.");
    separator();
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%s",
               name, party, district, &election_number, nic, username, password);
        
        if (compare_strings(party, logged_party_name)) {
            count++;
            printf("%-5d %-20s %-20s %-15d\n",
                   count, name, district, election_number);
        }
    }
    
    if (count == 0) {
        printf("\nNo candidates registered for your party yet!\n");
    } else {
        printf("\nTotal Candidates: %d\n", count);
    }
    
    printf("\n");
    separator();
    fclose(fp);
}

// View party performance
void view_party_performance() {
    FILE *fp, *fp_candidate;
    char line[500], cand_line[500];
    char candidate_name[100], voter_nic[50], district[25];
    char name[100], party[150], dist[25];
    int election_num, total_votes = 0;
    char nic[50], user[55], pass[25];
    
    system("cls");
    doubleline();
    printf("PERFORMANCE OF %s PARTY\n", logged_party_name);
    doubleline();
    
    fp = fopen("votes.txt", "r");
    
    if (fp == NULL) {
        printf("\nNo votes recorded yet!\n\n");
        separator();
        return;
    }
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%[^|]|%[^|]|%s", candidate_name, voter_nic, district);
        
        fp_candidate = fopen("candidate registration data.txt", "r");
        if (fp_candidate != NULL) {
            while (fgets(cand_line, sizeof(cand_line), fp_candidate) != NULL) {
                sscanf(cand_line, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%s",
                       name, party, dist, &election_num, nic, user, pass);
                
                if (strcmp(name, candidate_name) == 0 && 
                    compare_strings(party, logged_party_name)) {
                    total_votes++;
                    break;
                }
            }
            fclose(fp_candidate);
        }
    }
    
    fclose(fp);
    
    printf("\nTotal Votes Received: %d\n\n", total_votes);
    separator();
}

// Party dashboard
void party_dashboard() {
    char choice;
    
    do {
        printf("\n");
        doubleline();
        printf("PARTY DASHBOARD - %s\n", logged_party_name);
        doubleline();
        
        printf("\n1. View Party Registration Status\n");
        printf("2. View Party Candidates\n");
        printf("3. View Party Performance\n");
        printf("0. Logout\n\n");
        
        separator();
        
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        
        switch(choice) {
            case '1':
                view_party_status();
                break;
                
            case '2':
                view_party_candidates();
                break;
                
            case '3':
                view_party_performance();
                break;
                
            case '0':
                party_logged_in = 0;
                strcpy(logged_party_name, "");
                strcpy(logged_party_leader, "");
                logged_party_code = 0;
                
                system("cls");
                doubleline();
                printf("PARTY LOGOUT\n");
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

// Party login
void party_login() {
    char username[50];
    char password[25];
    int attempts = 0;
    
    system("cls");
    doubleline();
    printf("PARTY LOGIN\n");
    doubleline();
    
    while (attempts < 3) {
        printf("\nEnter party username: ");
        scanf("%s", username);
        
        printf("Enter party password: ");
        scanf("%s", password);
        
        if (verify_party(username, password, logged_party_name, 
                        logged_party_leader, &logged_party_code)) {
            party_logged_in = 1;
            
            system("cls");
            doubleline();
            printf("LOGIN SUCCESSFUL\n");
            doubleline();
            printf("\nWelcome, %s!\n", logged_party_name);
            printf("Party Code: %d\n", logged_party_code);
            printf("Leader: %s\n", logged_party_leader);
            separator();
            
            party_dashboard();
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

// Check if party is logged in
int is_party_logged_in() {
    return party_logged_in;
}

// Party logout
void party_logout() {
    party_logged_in = 0;
    strcpy(logged_party_name, "");
    strcpy(logged_party_leader, "");
    logged_party_code = 0;
    printf("\nParty logged out successfully.\n\n");
    separator();
}