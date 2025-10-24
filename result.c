#include<stdio.h>
#include<string.h>
#include "heder.h"

// Struct to hold vote data
struct Vote {
    char voter_nic[50];
    char candidate_name[100];
    char party[150];
    char district[25];
};

// Function to display overall results
void display_overall_results() {
    FILE *fp;
    struct Vote vote;
    char line[500];
    int total_votes = 0;
    
    printf("\n========== OVERALL ELECTION RESULTS ==========\n\n");
    
    fp = fopen("votes.txt", "r");
    
    if (fp == NULL) {
        printf("No votes found or file doesn't exist!\n");
        separator();
        return;
    }
    
    // Count total votes
    while (fgets(line, sizeof(line), fp) != NULL) {
        total_votes++;
    }
    
    printf("Total Votes Cast: %d\n\n", total_votes);
    
    fclose(fp);
    separator();
}

// Function to display results by district
void display_results_by_district() {
    FILE *fp;
    char line[500];
    char district_name[25];
    char voter_nic[50], candidate[100], party[150], district[25];
    int count = 0;
    
    printf("\n========== RESULTS BY DISTRICT ==========\n\n");
    printf("Enter district name: ");
    scanf("%s", district_name);
    
    fp = fopen("votes.txt", "r");
    
    if (fp == NULL) {
        printf("No votes found!\n");
        separator();
        return;
    }
    
    printf("\nVotes in %s district:\n\n", district_name);
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%s", voter_nic, candidate, party, district);
        
        if (strcmp(district, district_name) == 0) {
            count++;
            printf("%d. Candidate: %s | Party: %s\n", count, candidate, party);
        }
    }
    
    if (count == 0) {
        printf("No votes found for this district!\n");
    } else {
        printf("\nTotal votes in %s: %d\n", district_name, count);
    }
    
    fclose(fp);
    separator();
}

// Function to display results by party
void display_results_by_party() {
    FILE *fp;
    char line[500];
    char party_name[150];
    char voter_nic[50], candidate[100], party[150], district[25];
    int count = 0;
    
    printf("\n========== RESULTS BY PARTY ==========\n\n");
    printf("Enter party name: ");
    scanf("%s", party_name);
    
    fp = fopen("votes.txt", "r");
    
    if (fp == NULL) {
        printf("No votes found!\n");
        separator();
        return;
    }
    
    printf("\nVotes for %s party:\n\n", party_name);
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%s", voter_nic, candidate, party, district);
        
        if (strcmp(party, party_name) == 0) {
            count++;
            printf("%d. Candidate: %s | District: %s\n", count, candidate, district);
        }
    }
    
    if (count == 0) {
        printf("No votes found for this party!\n");
    } else {
        printf("\nTotal votes for %s: %d\n", party_name, count);
    }
    
    fclose(fp);
    separator();
}

// Function to view candidate performance
void view_candidate_performance(char *candidate_name) {
    FILE *fp;
    char line[500];
    char voter_nic[50], candidate[100], party[150], district[25];
    int count = 0;
    
    printf("\n========== CANDIDATE PERFORMANCE ==========\n\n");
    
    fp = fopen("votes.txt", "r");
    
    if (fp == NULL) {
        printf("No votes found!\n");
        separator();
        return;
    }
    
    printf("Votes for candidate: %s\n\n", candidate_name);
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%s", voter_nic, candidate, party, district);
        
        if (strcmp(candidate, candidate_name) == 0) {
            count++;
        }
    }
    
    if (count == 0) {
        printf("No votes found for this candidate!\n");
    } else {
        printf("Total votes received: %d\n", count);
    }
    
    fclose(fp);
    separator();
}

// Function for candidates to view their own results
void candidate_view_results(char *candidate_name) {
    view_candidate_performance(candidate_name);
}

// Main results menu
void results() {
    char choice;
    char candidate_name[100];
    
    do {
        printf("\n========== ELECTION RESULTS MENU ==========\n\n");
        printf("1. Overall Results\n");
        printf("2. Results by District\n");
        printf("3. Results by Party\n");
        printf("4. View Candidate Performance\n");
        printf("0. Back to Main Menu\n\n");
        separator();
        
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        
        switch(choice) {
            case '1':
                display_overall_results();
                break;
            
            case '2':
                display_results_by_district();
                break;
            
            case '3':
                display_results_by_party();
                break;
            
            case '4':
                printf("\nEnter candidate name: ");
                scanf("%s", candidate_name);
                view_candidate_performance(candidate_name);
                break;
            
            case '0':
                printf("\nReturning to main menu...\n");
                separator();
                break;
            
            default:
                printf("\nInvalid choice! Please try again.\n");
                separator();
        }
        
    } while (choice != '0');
}