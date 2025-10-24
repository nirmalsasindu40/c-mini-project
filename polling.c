#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
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

// Verify voter credentials and get voter's district
int verify_voter(char *username, char *password, char *voter_nic, char *voter_district) {
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
            strcpy(voter_district, district);
            fclose(fp);
            return 1; // Valid voter
        }
    }
    
    fclose(fp);
    return 0; // Invalid credentials
}

// Convert string to lowercase
void to_lowercase(char *str, char *result) {
    int i;
    for(i = 0; str[i]; i++) {
        result[i] = tolower(str[i]);
    }
    result[i] = '\0';
}

// Display candidates from voter's district only
void display_candidates(char *voter_district) {
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
    int found = 0;
    
    fp = fopen("candidate registration data.txt", "r");
    
    if (fp == NULL) {
        printf("\nNo candidates registered yet!\n");
        return;
    }
    
    printf("\n");
    separator();
    printf("REGISTERED CANDIDATES FOR %s DISTRICT:\n", voter_district);
    separator();
    printf("\n%-5s %-20s %-20s %-15s\n", "No.", "Name", "Party", "Election No.");
    separator();
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%s", 
               name, party, district, &election_number, nic, username, password);
        
        // Convert both districts to lowercase for case-insensitive comparison
        char voter_dist_lower[25];
        char candidate_dist_lower[25];
        
        to_lowercase(voter_district, voter_dist_lower);
        to_lowercase(district, candidate_dist_lower);
        
        // Only display candidates from the voter's district
        if (strcmp(voter_dist_lower, candidate_dist_lower) == 0) {
            printf("%-5d %-20s %-20s %-15d\n", 
                   count, name, party, election_number);
            count++;
            found = 1;
        }
    }
    
    if (!found) {
        printf("\nNo candidates registered for your district yet!\n");
    }
    
    separator();
    fclose(fp);
}

// Verify if candidate exists in voter's district
int verify_candidate_in_district(char *candidate_name, char *voter_district) {
    FILE *fp;
    char name[100];
    char party[150];
    char district[25];
    int election_number;
    char nic[50];
    char username[55];
    char password[25];
    char line[500];
    
    fp = fopen("candidate registration data.txt", "r");
    
    if (fp == NULL) {
        return 0;
    }
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%s", 
               name, party, district, &election_number, nic, username, password);
        
        // Convert to lowercase for case-insensitive comparison
        char voter_dist_lower[25];
        char candidate_dist_lower[25];
        char candidate_name_lower[100];
        char name_lower[100];
        
        to_lowercase(voter_district, voter_dist_lower);
        to_lowercase(district, candidate_dist_lower);
        to_lowercase(candidate_name, candidate_name_lower);
        to_lowercase(name, name_lower);
        
        if (strcmp(name_lower, candidate_name_lower) == 0 && 
            strcmp(voter_dist_lower, candidate_dist_lower) == 0) {
            fclose(fp);
            return 1; // Candidate exists in voter's district
        }
    }
    
    fclose(fp);
    return 0; // Candidate not found in voter's district
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
    char voter_district[20];
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
    
    // Verify voter credentials and get district
    if (!verify_voter(username, password, voter_nic, voter_district)) {
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
    printf("Your District: %s\n", voter_district);
    
    // Display candidates from voter's district only
    display_candidates(voter_district);
    
    printf("\nEnter the name of the candidate you want to vote for: ");
    scanf("%s", candidate_choice);
    
    // Verify candidate exists in voter's district
    if (!verify_candidate_in_district(candidate_choice, voter_district)) {
        printf("\n✗ Invalid candidate! Please choose a candidate from your district (%s).\n\n", voter_district);
        separator();
        return;
    }
    
    // Confirmation
    printf("\nYou are voting for: %s (District: %s)\n", candidate_choice, voter_district);
    printf("Are you sure? (Y/N): ");
    scanf(" %c", &choice);
    
    if (choice == 'Y' || choice == 'y') {
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