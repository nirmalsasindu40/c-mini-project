#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "heder.h"

// Admin credentials (hardcoded for security)
#define ADMIN_USERNAME "voteadmin2004106"
#define ADMIN_PASSWORD "voteadmin2004"

int admin_logged_in = 0;

// Function to verify admin credentials
int verify_admin(char *username, char *password) {
    if (strcmp(username, ADMIN_USERNAME) == 0 && 
        strcmp(password, ADMIN_PASSWORD) == 0) {
        return 1; // Valid admin
    }
    return 0; // Invalid
}

// Function to check if results are published
int are_results_published() {
    FILE *fp = fopen("results_status.txt", "r");
    if (fp == NULL) {
        return 0; // Not published by default
    }
    
    char status[20];
    fscanf(fp, "%s", status);
    fclose(fp);
    
    if (strcmp(status, "PUBLISHED") == 0) {
        return 1;
    }
    return 0;
}

// Function to publish results
void publish_results() {
    FILE *fp = fopen("results_status.txt", "w");
    if (fp == NULL) {
        printf("Error publishing results!\n");
        return;
    }
    
    fprintf(fp, "PUBLISHED");
    fclose(fp);
    
    system("cls");
    doubleline();
    printf("RESULTS PUBLISHED SUCCESSFULLY\n");
    doubleline();
    printf("\nElection results are now visible to the public.\n");
    printf("Voters and candidates can now view the results.\n\n");
    separator();
}

// Function to unpublish results
void unpublish_results() {
    FILE *fp = fopen("results_status.txt", "w");
    if (fp == NULL) {
        printf("Error unpublishing results!\n");
        return;
    }
    
    fprintf(fp, "UNPUBLISHED");
    fclose(fp);
    
    system("cls");
    doubleline();
    printf("RESULTS UNPUBLISHED\n");
    doubleline();
    printf("\nElection results are now hidden from the public.\n\n");
    separator();
}

// Function to view system statistics
void view_statistics() {
    system("cls");
    doubleline();
    printf("SYSTEM STATISTICS\n");
    doubleline();
    
    // Count registered voters
    FILE *fp_voters = fopen("voter registration data.txt", "r");
    int voter_count = 0;
    char line[500];
    
    if (fp_voters != NULL) {
        while (fgets(line, sizeof(line), fp_voters)) {
            voter_count++;
        }
        fclose(fp_voters);
    }
    
    // Count registered candidates
    FILE *fp_candidates = fopen("candidate registration data.txt", "r");
    int candidate_count = 0;
    
    if (fp_candidates != NULL) {
        while (fgets(line, sizeof(line), fp_candidates)) {
            candidate_count++;
        }
        fclose(fp_candidates);
    }
    
    // Count votes cast
    FILE *fp_votes = fopen("votes.txt", "r");
    int vote_count = 0;
    
    if (fp_votes != NULL) {
        while (fgets(line, sizeof(line), fp_votes)) {
            vote_count++;
        }
        fclose(fp_votes);
    }
    
    // Count voted records
    FILE *fp_voted = fopen("voted_records.txt", "r");
    int voted_count = 0;
    
    if (fp_voted != NULL) {
        while (fgets(line, sizeof(line), fp_voted)) {
            voted_count++;
        }
        fclose(fp_voted);
    }
    
    // Check polling status
    int polling_active = is_polling_active();
    int results_published = are_results_published();
    
    printf("\n");
    printf("Total Registered Voters:      %d\n", voter_count);
    printf("Total Registered Candidates:  %d\n", candidate_count);
    printf("Total Votes Cast:             %d\n", vote_count);
    printf("Total Voters Who Voted:       %d\n", voted_count);
    
    if (voter_count > 0) {
        double turnout = ((double)voted_count / voter_count) * 100;
        printf("Voter Turnout:                %.2f%%\n", turnout);
    } else {
        printf("Voter Turnout:                N/A\n");
    }
    
    printf("\n");
    separator();
    printf("Polling Status:               %s\n", polling_active ? "ACTIVE" : "INACTIVE");
    printf("Results Status:               %s\n", results_published ? "PUBLISHED" : "UNPUBLISHED");
    separator();
    printf("\n");
}

// Function to view polling time configuration
void view_polling_time() {
    FILE *fp = fopen("polling_time.txt", "r");
    if (fp == NULL) {
        printf("\nPolling time not configured yet!\n\n");
        return;
    }
    
    int start_day, start_month, start_year, start_hour, start_minute;
    int end_day, end_month, end_year, end_hour, end_minute;
    
    fscanf(fp, "%d/%d/%d %d:%d %d/%d/%d %d:%d", 
           &start_day, &start_month, &start_year, &start_hour, &start_minute,
           &end_day, &end_month, &end_year, &end_hour, &end_minute);
    fclose(fp);
    
    system("cls");
    doubleline();
    printf("CURRENT POLLING SCHEDULE\n");
    doubleline();
    
    printf("\nPolling Start: %02d/%02d/%d at %02d:%02d\n", 
           start_day, start_month, start_year, start_hour, start_minute);
    printf("Polling End:   %02d/%02d/%d at %02d:%02d\n\n", 
           end_day, end_month, end_year, end_hour, end_minute);
    
    if (is_polling_active()) {
        printf("Status: POLLING IS CURRENTLY ACTIVE\n");
    } else {
        printf("Status: POLLING IS NOT ACTIVE\n");
    }
    
    separator();
}

// Function to delete all votes (reset election)
void reset_election() {
    char confirm[10];
    
    printf("\n");
    doubleline();
    printf("WARNING: RESET ELECTION\n");
    doubleline();
    printf("\nThis will delete ALL votes and voting records.\n");
    printf("Voter and candidate registrations will remain.\n");
    printf("\nType 'RESET' to confirm: ");
    scanf("%s", confirm);
    
    if (strcmp(confirm, "RESET") == 0) {
        // Delete votes
        remove("votes.txt");
        remove("voted_records.txt");
        
        // Unpublish results
        FILE *fp = fopen("results_status.txt", "w");
        if (fp != NULL) {
            fprintf(fp, "UNPUBLISHED");
            fclose(fp);
        }
        
        system("cls");
        doubleline();
        printf("ELECTION RESET SUCCESSFUL\n");
        doubleline();
        printf("\nAll votes have been deleted.\n");
        printf("The election can now be restarted.\n\n");
    } else {
        printf("\nReset cancelled.\n\n");
    }
    
    separator();
}

// Admin dashboard menu
void admin_dashboard() {
    char choice;
    
    do {
        printf("\n");
        doubleline();
        printf("ADMIN DASHBOARD\n");
        doubleline();
        
        printf("\n1. Set Polling Time\n");
        printf("2. View Polling Schedule\n");
        printf("3. Publish Results\n");
        printf("4. Unpublish Results\n");
        printf("5. View Admin Results (Preview)\n");
        printf("6. View System Statistics\n");
        printf("7. Reset Election (Delete All Votes)\n");
        printf("0. Logout\n\n");
        
        separator();
        
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        
        switch(choice) {
            case '1':
                system("cls");
                doubleline();
                printf("SET POLLING TIME\n");
                doubleline();
                admin_set_polling_time();
                break;
                
            case '2':
                view_polling_time();
                break;
                
            case '3':
                publish_results();
                break;
                
            case '4':
                unpublish_results();
                break;
                
            case '5':
                system("cls");
                doubleline();
                printf("ADMIN RESULTS PREVIEW\n");
                doubleline();
                display_overall_results();
                break;
                
            case '6':
                view_statistics();
                break;
                
            case '7':
                reset_election();
                break;
                
            case '0':
                admin_logged_in = 0;
                system("cls");
                doubleline();
                printf("ADMIN LOGOUT\n");
                doubleline();
                printf("\nYou have been logged out successfully.\n\n");
                separator();
                return;
                
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
        
    } while(choice != '0');
}

// Main admin panel function
void admin_panel() {
    char username[100];
    char password[100];
    int attempts = 0;
    
    system("cls");
    doubleline();
    printf("ADMIN LOGIN\n");
    doubleline();
    
    while (attempts < 3) {
        printf("\nEnter admin username: ");
        scanf("%s", username);
        
        printf("Enter admin password: ");
        scanf("%s", password);
        
        if (verify_admin(username, password)) {
            admin_logged_in = 1;
            system("cls");
            doubleline();
            printf("LOGIN SUCCESSFUL\n");
            doubleline();
            printf("\nWelcome, Administrator!\n");
            separator();
            
            admin_dashboard();
            return;
        } else {
            attempts++;
            system("cls");
            doubleline();
            printf("LOGIN FAILED\n");
            doubleline();
            printf("\nInvalid credentials! Attempt %d of 3\n", attempts);
            
            if (attempts >= 3) {
                printf("\nToo many failed attempts. Access denied.\n");
                separator();
                return;
            }
        }
    }
}

// Check if admin is logged in
int is_admin_logged_in() {
    return admin_logged_in;
}