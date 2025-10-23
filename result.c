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

// Main results menu
void results() {
    char choice;
    
    do {
        printf("\n========== ELECTION RESULTS MENU ==========\n\n");
        printf("1. Overall Results\n");
        printf("0. Back to Main Menu\n\n");
        separator();
        
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        
        switch(choice) {
            case '1':
                display_overall_results();
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