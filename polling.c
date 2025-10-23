#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "heder.h"

// Check if voter has already voted
int has_voter_voted(char *nic) {
    FILE *fp;
    char file_nic[50];
    char line[200];
    
    fp = fopen("voted_voters.txt", "r");
    
    if (fp == NULL) {
        return 0; // File doesn't exist, so voter hasn't voted
    }
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%s", file_nic);
        
        if (strcmp(file_nic, nic) == 0) {
            fclose(fp);
            return 1; // Voter has already voted
        }
    }
    
    fclose(fp);
    return 0; // Voter hasn't voted yet
}

// Mark voter as voted
void mark_voter_as_voted(char *nic) {
    FILE *fp;
    
    fp = fopen("voted_voters.txt", "a");
    
    if (fp == NULL) {
        printf("Error: Could not record vote!\n");
        return;
    }
    
    fprintf(fp, "%s\n", nic);
    fclose(fp);
}

// Verify voter credentials
int verify_voter(char *username, char *password, char *voter_nic) {
    FILE *fp;
    char name[100];
    int age;
    char district[20];
    char file_username[50];
    char nic[20];
    char file_password[25];
    char line[300];
    
    fp = fopen("voter registration data.txt", "r");
    
    if (fp == NULL) {
        printf("Error: Voter database not found!\n");
        return 0;
    }
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%[^|]|%d|%[^|]|%[^|]|%[^|]|%s", 
               name, &age, district, file_username, nic, file_password);
        
        if (strcmp(file_username, username) == 0 && strcmp(file_password, password) == 0) {
            strcpy(voter_nic, nic);
            fclose(fp);
            return 1; // Valid voter
        }
    }
    
    fclose(fp);
    return 0; // Invalid credentials
}

// Display all candidates
void display_candidates() {
    FILE *fp;
    char name[100];
    char party[150];
    char district[25];
    int election_number;
    char nic[50];
    char username[55];
    char password[25];
    char line[500];
    int count = 1;
    
    fp = fopen("candidate registration data.txt", "r");
    
    if (fp == NULL) {
        printf("No candidates registered yet!\n");
        return;
    }
    
    printf("\n");
    separator();
    printf("REGISTERED CANDIDATES:\n");
    separator();
    printf("\n%-5s %-20s %-20s %-15s %-15s\n", "No.", "Name", "Party", "District", "Election No.");
    separator();
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%s", 
               name, party, district, &election_number, nic, username, password);
        
        printf("%-5d %-20s %-20s %-15s %-15d\n", 
               count, name, party, district, election_number);
        count++;
    }
    
    separator();
    fclose(fp);
}

// Record vote
void record_vote(char *candidate_name, char *voter_nic, char *voter_district) {
    FILE *fp;
    
    fp = fopen("votes.txt", "a");
    
    if (fp == NULL) {
        printf("Error: Could not record vote!\n");
        return;
    }
    
    fprintf(fp, "%s|%s|%s\n", candidate_name, voter_nic, voter_district);
    fclose(fp);
}

// Main polling function
void polling() {
    char username[50];
    char password[25];
    char voter_nic[20];
    char candidate_choice[100];
    char choice;
    
    // Check if polling is active
    if (!is_polling_active()) {
        printf("\nPolling is not active at the moment!\n");
        printf("Please contact the admin to start polling.\n\n");
        separator();
        return;
    }
    
    printf("\n");
    separator();
    printf("VOTER AUTHENTICATION\n");
    separator();
    
    printf("\nEnter your username: ");
    scanf("%s", username);
    
    printf("Enter your password: ");
    scanf("%s", password);
    
    // Verify voter credentials
    if (!verify_voter(username, password, voter_nic)) {
        printf("\n✗ Invalid credentials! Please register first or check your username/password.\n\n");
        separator();
        return;
    }
    
    // Check if voter has already voted
    if (has_voter_voted(voter_nic)) {
        printf("\n✗ You have already cast your vote!\n");
        printf("Each voter can only vote once.\n\n");
        separator();
        return;
    }
    
    printf("\n✓ Authentication successful!\n");
    
    // Display candidates
    display_candidates();
    
    printf("\nEnter the name of the candidate you want to vote for: ");
    scanf("%s", candidate_choice);
    
    // Confirmation
    printf("\nYou are voting for: %s\n", candidate_choice);
    printf("Are you sure? (Y/N): ");
    scanf(" %c", &choice);
    
    if (choice == 'Y' || choice == 'y') {
        char voter_district[20];
        
        // Get voter's district from registration data
        FILE *fp = fopen("voter registration data.txt", "r");
        char name[100];
        int age;
        char district[20];
        char file_username[50];
        char nic[20];
        char file_password[25];
        char line[300];
        
        while (fgets(line, sizeof(line), fp) != NULL) {
            sscanf(line, "%[^|]|%d|%[^|]|%[^|]|%[^|]|%s", 
                   name, &age, district, file_username, nic, file_password);
            
            if (strcmp(nic, voter_nic) == 0) {
                strcpy(voter_district, district);
                break;
            }
        }
        fclose(fp);
        
        // Record the vote
        record_vote(candidate_choice, voter_nic, voter_district);
        
        // Mark voter as voted
        mark_voter_as_voted(voter_nic);
        
        printf("\n✓ Your vote has been successfully recorded!\n");
        printf("Thank you for participating in the election.\n\n");
    } else {
        printf("\n✗ Vote cancelled.\n\n");
    }
    
    separator();
}

// Check if polling is active
int is_polling_active() {
    FILE *fp;
    int status;
    
    fp = fopen("polling_status.txt", "r");
    
    if (fp == NULL) {
        return 0; // Polling not active if file doesn't exist
    }
    
    fscanf(fp, "%d", &status);
    fclose(fp);
    
    return status; // Returns 1 if active, 0 if not
}


