#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "heder.h"

// Global variables for logged-in voter
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

// Function to check if voter has already voted
int has_voter_voted(char *nic) {
    FILE *fp = fopen("voted_records.txt", "r");
    if (fp == NULL) {
        return 0; // No records exist, so voter hasn't voted
    }
    
    char line[200];
    while (fgets(line, sizeof(line), fp) != NULL) {
        char recorded_nic[20];
        sscanf(line, "%[^|]|", recorded_nic);
        
        if (strcmp(recorded_nic, nic) == 0) {
            fclose(fp);
            return 1; // Voter has already voted
        }
    }
    
    fclose(fp);
    return 0; // Voter hasn't voted yet
}

// Function to check if polling is currently active
int is_polling_active() {
    FILE *fp = fopen("polling_time.txt", "r");
    if (fp == NULL) {
        return 0; // Polling not configured
    }
    
    int start_day, start_month, start_year, start_hour, start_minute;
    int end_day, end_month, end_year, end_hour, end_minute;
    
    fscanf(fp, "%d/%d/%d %d:%d %d/%d/%d %d:%d", 
           &start_day, &start_month, &start_year, &start_hour, &start_minute,
           &end_day, &end_month, &end_year, &end_hour, &end_minute);
    fclose(fp);
    
    // Get current time
    time_t now = time(NULL);
    struct tm *current = localtime(&now);
    
    // Create time structures for start and end times
    struct tm start_time = {0};
    start_time.tm_year = start_year - 1900;
    start_time.tm_mon = start_month - 1;
    start_time.tm_mday = start_day;
    start_time.tm_hour = start_hour;
    start_time.tm_min = start_minute;
    
    struct tm end_time = {0};
    end_time.tm_year = end_year - 1900;
    end_time.tm_mon = end_month - 1;
    end_time.tm_mday = end_day;
    end_time.tm_hour = end_hour;
    end_time.tm_min = end_minute;
    
    time_t start_timestamp = mktime(&start_time);
    time_t end_timestamp = mktime(&end_time);
    
    // Check if current time is between start and end
    if (now >= start_timestamp && now <= end_timestamp) {
        return 1; // Polling is active
    }
    
    return 0; // Polling is not active
}

// Function to display candidates for voting
void display_candidates_for_voting(char *voter_district) {
    FILE *fp = fopen("candidate registration data.txt", "r");
    if (fp == NULL) {
        printf("\nNo candidates registered!\n");
        return;
    }
    
    char line[500];
    int count = 0;
    
    printf("\n");
    doubleline();
    printf("     CANDIDATES IN YOUR DISTRICT: %s     \n", voter_district);
    doubleline();
    printf("\n");
    
    printf("%-5s %-25s %-20s %-15s\n", "No.", "Candidate Name", "Party", "Election #");
    separator();
    
    // File format: name|party|district|election_number|nic|username|password
    while (fgets(line, sizeof(line), fp) != NULL) {
        char name[100], party[150], district[25];
        int election_number;
        char nic[50], username[55], password[25];
        
        sscanf(line, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%s",
               name, party, district, &election_number, 
               nic, username, password);
        
        // Only show candidates from voter's district
        if (strcasecmp(district, voter_district) == 0) {
            count++;
            printf("%-5d %-25s %-20s %-15d\n", 
                   count, name, party, election_number);
        }
    }
    
    fclose(fp);
    
    if (count == 0) {
        printf("\nNo candidates registered in your district yet.\n");
    }
    
    separator();
}

// Function to record a vote
int record_vote(int election_number, char *voter_nic) {
    // First verify the candidate exists and is from the voter's district
    FILE *fp_candidates = fopen("candidate registration data.txt", "r");
    if (fp_candidates == NULL) {
        return 0;
    }
    
    char line[500];
    int candidate_found = 0;
    char candidate_district[25];
    
    while (fgets(line, sizeof(line), fp_candidates) != NULL) {
        char name[100], party[150], district[25];
        int file_election_number;
        char nic[50], username[55], password[25];
        
        sscanf(line, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%s",
               name, party, district, &file_election_number, 
               nic, username, password);
        
        if (file_election_number == election_number) {
            candidate_found = 1;
            strcpy(candidate_district, district);
            break;
        }
    }
    fclose(fp_candidates);
    
    if (!candidate_found) {
        return 0; // Invalid election number
    }
    
    // Check if candidate is from voter's district
    if (strcasecmp(candidate_district, logged_voter_district) != 0) {
        printf("\n✗ ERROR: You can only vote for candidates in your district (%s)!\n", 
               logged_voter_district);
        return 0;
    }
    
    // Record the vote
    FILE *fp_votes = fopen("votes.txt", "a");
    if (fp_votes == NULL) {
        return 0;
    }
    
    // Get current timestamp
    time_t now = time(NULL);
    char *timestamp = ctime(&now);
    timestamp[strlen(timestamp) - 1] = '\0'; // Remove newline
    
    // Format: election_number|voter_nic|timestamp
    fprintf(fp_votes, "%d|%s|%s\n", election_number, voter_nic, timestamp);
    fclose(fp_votes);
    
    // Record that this voter has voted
    FILE *fp_voted = fopen("voted_records.txt", "a");
    if (fp_voted != NULL) {
        fprintf(fp_voted, "%s|%s\n", voter_nic, timestamp);
        fclose(fp_voted);
    }
    
    return 1; // Success
}

// Main polling function
void polling() {
    // Check if voter is logged in
    if (!voter_logged_in) {
        system("cls");
        doubleline();
        printf("POLLING - VOTER LOGIN REQUIRED\n");
        doubleline();
        printf("\nYou must be logged in to vote.\n");
        printf("Please login first (Option 3).\n\n");
        separator();
        return;
    }
    
    // Check if polling is active
    if (!is_polling_active()) {
        system("cls");
        doubleline();
        printf("POLLING NOT ACTIVE\n");
        doubleline();
        printf("\nVoting is not currently open.\n");
        printf("Please check the polling schedule with the administrator.\n\n");
        separator();
        return;
    }
    
    // Check if voter has already voted
    if (has_voter_voted(logged_voter_nic)) {
        system("cls");
        doubleline();
        printf("ALREADY VOTED\n");
        doubleline();
        printf("\nYou have already cast your vote.\n");
        printf("Each voter can only vote once.\n\n");
        separator();
        return;
    }
    
    // Display voting interface
    system("cls");
    doubleline();
    printf("           CAST YOUR VOTE           \n");
    doubleline();
    
    printf("\nVoter: %s\n", logged_voter_name);
    printf("NIC: %s\n", logged_voter_nic);
    printf("District: %s\n", logged_voter_district);
    
    // Display candidates
    display_candidates_for_voting(logged_voter_district);
    
    // Get vote
    int election_number;
    char confirm;
    
    printf("\nEnter the election number of your chosen candidate: ");
    while (scanf("%d", &election_number) != 1) {
        printf("Invalid input! Please enter a number: ");
        while (getchar() != '\n');
    }
    
    // Confirm vote
    printf("\nYou are voting for candidate with election number: %d\n", election_number);
    printf("Are you sure? (Y/N): ");
    scanf(" %c", &confirm);
    
    if (confirm == 'Y' || confirm == 'y') {
        if (record_vote(election_number, logged_voter_nic)) {
            system("cls");
            doubleline();
            printf("✓ VOTE RECORDED SUCCESSFULLY!\n");
            doubleline();
            printf("\nThank you for voting, %s!\n", logged_voter_name);
            printf("Your vote has been securely recorded.\n");
            printf("Election Number: %d\n\n", election_number);
            separator();
        } else {
            system("cls");
            doubleline();
            printf("✗ VOTE FAILED!\n");
            doubleline();
            printf("\nInvalid election number.\n");
            printf("Please try again with a valid candidate number.\n\n");
            separator();
        }
    } else {
        printf("\nVote cancelled. You can vote again.\n\n");
        separator();
    }
}

// Function for voter logout
void voter_logout() {
    voter_logged_in = 0;
    strcpy(logged_voter_nic, "");
    strcpy(logged_voter_name, "");
    strcpy(logged_voter_district, "");
    
    system("cls");
    doubleline();
    printf("VOTER LOGOUT\n");
    doubleline();
    printf("\nYou have been logged out successfully.\n\n");
    separator();
}

// Check if voter is logged in
int is_voter_logged_in() {
    return voter_logged_in;
}

// Admin function to set polling time
void admin_set_polling_time() {
    int start_day, start_month, start_year, start_hour, start_minute;
    int end_day, end_month, end_year, end_hour, end_minute;
    
    printf("\n=== POLLING START TIME ===\n");
    printf("Enter start date (DD MM YYYY): ");
    scanf("%d %d %d", &start_day, &start_month, &start_year);
    
    printf("Enter start time (HH MM in 24-hour format): ");
    scanf("%d %d", &start_hour, &start_minute);
    
    printf("\n=== POLLING END TIME ===\n");
    printf("Enter end date (DD MM YYYY): ");
    scanf("%d %d %d", &end_day, &end_month, &end_year);
    
    printf("Enter end time (HH MM in 24-hour format): ");
    scanf("%d %d", &end_hour, &end_minute);
    
    // Save to file
    FILE *fp = fopen("polling_time.txt", "w");
    if (fp == NULL) {
        printf("\nError setting polling time!\n");
        return;
    }
    
    fprintf(fp, "%d/%d/%d %d:%d %d/%d/%d %d:%d", 
            start_day, start_month, start_year, start_hour, start_minute,
            end_day, end_month, end_year, end_hour, end_minute);
    fclose(fp);
    
    system("cls");
    doubleline();
    printf("POLLING TIME SET SUCCESSFULLY\n");
    doubleline();
    
    printf("\nPolling Start: %02d/%02d/%d at %02d:%02d\n", 
           start_day, start_month, start_year, start_hour, start_minute);
    printf("Polling End:   %02d/%02d/%d at %02d:%02d\n\n", 
           end_day, end_month, end_year, end_hour, end_minute);
    
    separator();
}