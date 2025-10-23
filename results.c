#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "heder.h"

// Function to count votes for each candidate using parallel arrays
int count_all_votes(char names[][100], char parties[][150], char districts[][25], 
                    int election_numbers[], int vote_counts[], int max_candidates) {
    FILE *fp_candidates = fopen("candidate registration data.txt", "r");
    if (fp_candidates == NULL) {
        printf("No candidates registered!\n");
        return 0;
    }
    
    // Load all candidates
    char line[500];
    int candidate_count = 0;
    char nic[50], username[55], password[25];
    
    while (fgets(line, sizeof(line), fp_candidates) && candidate_count < max_candidates) {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%s",
               names[candidate_count],
               parties[candidate_count],
               districts[candidate_count],
               &election_numbers[candidate_count],
               nic, username, password);
        
        vote_counts[candidate_count] = 0;
        candidate_count++;
    }
    fclose(fp_candidates);
    
    // Count votes from votes.txt
    FILE *fp_votes = fopen("votes.txt", "r");
    if (fp_votes == NULL) {
        return candidate_count;
    }
    
    while (fgets(line, sizeof(line), fp_votes)) {
        int voted_election_number;
        sscanf(line, "%d|", &voted_election_number);
        
        // Find matching candidate and increment vote count
        for (int i = 0; i < candidate_count; i++) {
            if (election_numbers[i] == voted_election_number) {
                vote_counts[i]++;
                break;
            }
        }
    }
    fclose(fp_votes);
    
    return candidate_count;
}

// Function to sort candidates by votes (descending order) using parallel arrays
void sort_by_votes(char names[][100], char parties[][150], char districts[][25], 
                   int election_numbers[], int vote_counts[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (vote_counts[j] < vote_counts[j + 1]) {
                // Swap vote counts
                int temp_votes = vote_counts[j];
                vote_counts[j] = vote_counts[j + 1];
                vote_counts[j + 1] = temp_votes;
                
                // Swap election numbers
                int temp_num = election_numbers[j];
                election_numbers[j] = election_numbers[j + 1];
                election_numbers[j + 1] = temp_num;
                
                // Swap names
                char temp_name[100];
                strcpy(temp_name, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], temp_name);
                
                // Swap parties
                char temp_party[150];
                strcpy(temp_party, parties[j]);
                strcpy(parties[j], parties[j + 1]);
                strcpy(parties[j + 1], temp_party);
                
                // Swap districts
                char temp_district[25];
                strcpy(temp_district, districts[j]);
                strcpy(districts[j], districts[j + 1]);
                strcpy(districts[j + 1], temp_district);
            }
        }
    }
}

// Function to display overall results
void display_overall_results() {
    char names[100][100];
    char parties[100][150];
    char districts[100][25];
    int election_numbers[100];
    int vote_counts[100];
    
    int candidate_count = count_all_votes(names, parties, districts, 
                                          election_numbers, vote_counts, 100);
    
    if (candidate_count == 0) {
        printf("No candidates found!\n\n");
        return;
    }
    
    // Sort by vote count
    sort_by_votes(names, parties, districts, election_numbers, vote_counts, candidate_count);
    
    // Calculate total votes
    int total_votes = 0;
    for (int i = 0; i < candidate_count; i++) {
        total_votes += vote_counts[i];
    }
    
    printf("\n");
    doubleline();
    printf("           ELECTION RESULTS - OVERALL           \n");
    doubleline();
    printf("\nTotal Votes Cast: %d\n\n", total_votes);
    separator();
    
    printf("%-5s %-25s %-20s %-15s %-10s %-10s\n", 
           "Rank", "Candidate Name", "Party", "District", "Votes", "Percentage");
    separator();
    
    for (int i = 0; i < candidate_count; i++) {
        double percentage = (total_votes > 0) ? 
                          ((double)vote_counts[i] / total_votes * 100) : 0.0;
        
        printf("%-5d %-25s %-20s %-15s %-10d %.2f%%\n",
               i + 1, names[i], parties[i], districts[i], 
               vote_counts[i], percentage);
    }
    
    separator();
    
    // Display winner if votes exist
    if (total_votes > 0) {
        printf("\n*** WINNER ***\n");
        printf("Candidate: %s\n", names[0]);
        printf("Party: %s\n", parties[0]);
        printf("District: %s\n", districts[0]);
        printf("Total Votes: %d\n", vote_counts[0]);
        double winner_percentage = ((double)vote_counts[0] / total_votes * 100);
        printf("Vote Share: %.2f%%\n\n", winner_percentage);
    } else {
        printf("\nNo votes have been cast yet.\n\n");
    }
}

// Function to display results by district
void display_results_by_district() {
    char search_district[25];
    
    printf("Enter district name: ");
    scanf("%s", search_district);
    
    char names[100][100];
    char parties[100][150];
    char districts[100][25];
    int election_numbers[100];
    int vote_counts[100];
    
    int candidate_count = count_all_votes(names, parties, districts, 
                                          election_numbers, vote_counts, 100);
    
    // Filter candidates by district using parallel arrays
    char filtered_names[100][100];
    char filtered_parties[100][150];
    int filtered_votes[100];
    int filtered_count = 0;
    
    for (int i = 0; i < candidate_count; i++) {
        if (strcasecmp(districts[i], search_district) == 0) {
            strcpy(filtered_names[filtered_count], names[i]);
            strcpy(filtered_parties[filtered_count], parties[i]);
            filtered_votes[filtered_count] = vote_counts[i];
            filtered_count++;
        }
    }
    
    if (filtered_count == 0) {
        printf("\nNo candidates found for district: %s\n\n", search_district);
        return;
    }
    
    // Sort filtered results
    for (int i = 0; i < filtered_count - 1; i++) {
        for (int j = 0; j < filtered_count - i - 1; j++) {
            if (filtered_votes[j] < filtered_votes[j + 1]) {
                int temp_votes = filtered_votes[j];
                filtered_votes[j] = filtered_votes[j + 1];
                filtered_votes[j + 1] = temp_votes;
                
                char temp_name[100];
                strcpy(temp_name, filtered_names[j]);
                strcpy(filtered_names[j], filtered_names[j + 1]);
                strcpy(filtered_names[j + 1], temp_name);
                
                char temp_party[150];
                strcpy(temp_party, filtered_parties[j]);
                strcpy(filtered_parties[j], filtered_parties[j + 1]);
                strcpy(filtered_parties[j + 1], temp_party);
            }
        }
    }
    
    // Calculate total votes in district
    int total_votes = 0;
    for (int i = 0; i < filtered_count; i++) {
        total_votes += filtered_votes[i];
    }
    
    printf("\n");
    doubleline();
    printf("    ELECTION RESULTS - %s DISTRICT    \n", search_district);
    doubleline();
    printf("\nTotal Votes in District: %d\n\n", total_votes);
    separator();
    
    printf("%-5s %-25s %-20s %-10s %-10s\n", 
           "Rank", "Candidate Name", "Party", "Votes", "Percentage");
    separator();
    
    for (int i = 0; i < filtered_count; i++) {
        double percentage = (total_votes > 0) ? 
                          ((double)filtered_votes[i] / total_votes * 100) : 0.0;
        
        printf("%-5d %-25s %-20s %-10d %.2f%%\n",
               i + 1, filtered_names[i], filtered_parties[i], 
               filtered_votes[i], percentage);
    }
    
    separator();
    
    if (total_votes > 0) {
        printf("\n*** DISTRICT WINNER ***\n");
        printf("Candidate: %s (%s)\n", filtered_names[0], filtered_parties[0]);
        printf("Votes: %d (%.2f%%)\n\n", 
               filtered_votes[0],
               ((double)filtered_votes[0] / total_votes * 100));
    }
}

// Function to display results by party
void display_results_by_party() {
    char names[100][100];
    char parties[100][150];
    char districts[100][25];
    int election_numbers[100];
    int vote_counts[100];
    
    int candidate_count = count_all_votes(names, parties, districts, 
                                          election_numbers, vote_counts, 100);
    
    if (candidate_count == 0) {
        printf("No candidates found!\n\n");
        return;
    }
    
    // Get unique parties and sum their votes
    char unique_parties[50][150];
    int party_votes[50] = {0};
    int party_count = 0;
    
    for (int i = 0; i < candidate_count; i++) {
        int found = 0;
        for (int j = 0; j < party_count; j++) {
            if (strcmp(unique_parties[j], parties[i]) == 0) {
                party_votes[j] += vote_counts[i];
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(unique_parties[party_count], parties[i]);
            party_votes[party_count] = vote_counts[i];
            party_count++;
        }
    }
    
    // Sort parties by votes
    for (int i = 0; i < party_count - 1; i++) {
        for (int j = 0; j < party_count - i - 1; j++) {
            if (party_votes[j] < party_votes[j + 1]) {
                int temp_votes = party_votes[j];
                party_votes[j] = party_votes[j + 1];
                party_votes[j + 1] = temp_votes;
                
                char temp_party[150];
                strcpy(temp_party, unique_parties[j]);
                strcpy(unique_parties[j], unique_parties[j + 1]);
                strcpy(unique_parties[j + 1], temp_party);
            }
        }
    }
    
    // Calculate total votes
    int total_votes = 0;
    for (int i = 0; i < party_count; i++) {
        total_votes += party_votes[i];
    }
    
    printf("\n");
    doubleline();
    printf("         ELECTION RESULTS - BY PARTY         \n");
    doubleline();
    printf("\nTotal Votes: %d\n\n", total_votes);
    separator();
    
    printf("%-5s %-30s %-15s %-10s\n", "Rank", "Party Name", "Total Votes", "Percentage");
    separator();
    
    for (int i = 0; i < party_count; i++) {
        double percentage = (total_votes > 0) ? 
                          ((double)party_votes[i] / total_votes * 100) : 0.0;
        
        printf("%-5d %-30s %-15d %.2f%%\n",
               i + 1, unique_parties[i], party_votes[i], percentage);
    }
    
    separator();
    
    if (total_votes > 0) {
        printf("\n*** LEADING PARTY ***\n");
        printf("Party: %s\n", unique_parties[0]);
        printf("Total Votes: %d (%.2f%%)\n\n", 
               party_votes[0],
               ((double)party_votes[0] / total_votes * 100));
    }
}

// Function to view individual candidate's performance
void view_candidate_performance(char *candidate_name) {
    char names[100][100];
    char parties[100][150];
    char districts[100][25];
    int election_numbers[100];
    int vote_counts[100];
    
    int candidate_count = count_all_votes(names, parties, districts, 
                                          election_numbers, vote_counts, 100);
    
    int found = 0;
    int total_votes = 0;
    
    // Calculate total votes
    for (int i = 0; i < candidate_count; i++) {
        total_votes += vote_counts[i];
    }
    
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(names[i], candidate_name) == 0) {
            found = 1;
            
            printf("\n");
            doubleline();
            printf("       YOUR CAMPAIGN PERFORMANCE       \n");
            doubleline();
            
            printf("\nCandidate: %s\n", names[i]);
            printf("Party: %s\n", parties[i]);
            printf("District: %s\n", districts[i]);
            printf("Election Number: %d\n\n", election_numbers[i]);
            
            separator();
            printf("Votes Received: %d\n", vote_counts[i]);
            
            if (total_votes > 0) {
                double percentage = ((double)vote_counts[i] / total_votes * 100);
                printf("Vote Share: %.2f%%\n", percentage);
                
                // Find rank
                int rank = 1;
                for (int j = 0; j < candidate_count; j++) {
                    if (vote_counts[j] > vote_counts[i]) {
                        rank++;
                    }
                }
                printf("Current Rank: %d out of %d candidates\n", rank, candidate_count);
            } else {
                printf("No votes cast yet.\n");
            }
            separator();
            printf("\n");
            break;
        }
    }
    
    if (!found) {
        printf("\nCandidate data not found.\n\n");
    }
}

// Main results function (public access)
void results() {
    // Check if results are published
    FILE *fp_status = fopen("results_status.txt", "r");
    if (fp_status != NULL) {
        char status[20];
        fscanf(fp_status, "%s", status);
        fclose(fp_status);
        
        if (strcmp(status, "UNPUBLISHED") == 0) {
            printf("\n");
            doubleline();
            printf("RESULTS NOT AVAILABLE\n");
            doubleline();
            printf("\nElection results have not been published yet.\n");
            printf("Please contact the administrator.\n\n");
            separator();
            return;
        }
    } else {
        // If file doesn't exist, results not published
        printf("\n");
        doubleline();
        printf("RESULTS NOT AVAILABLE\n");
        doubleline();
        printf("\nElection results have not been published yet.\n");
        printf("Please contact the administrator.\n\n");
        separator();
        return;
    }
    
    char choice;
    
    printf("=== ELECTION RESULTS ===\n\n");
    printf("1. Overall Results\n");
    printf("2. Results by District\n");
    printf("3. Results by Party\n");
    printf("0. Back to Main Menu\n\n");
    separator();
    
    printf("Enter your choice: ");
    scanf(" %c", &choice);
    
    system("cls");
    
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
        case '0':
            return;
        default:
            printf("Invalid choice!\n");
    }
    
    separator();
}

// Candidate-specific results view (after login)
void candidate_view_results(char *candidate_name) {
    char choice;
    
    printf("\n=== RESULTS DASHBOARD ===\n\n");
    printf("1. My Performance\n");
    printf("2. Overall Results\n");
    printf("3. District Results\n");
    printf("4. Party Results\n");
    printf("0. Back\n\n");
    separator();
    
    printf("Enter your choice: ");
    scanf(" %c", &choice);
    
    system("cls");
    doubleline();
    
    switch(choice) {
        case '1':
            view_candidate_performance(candidate_name);
            break;
        case '2':
            display_overall_results();
            break;
        case '3':
            display_results_by_district();
            break;
        case '4':
            display_results_by_party();
            break;
        case '0':
            return;
        default:
            printf("Invalid choice!\n");
    }
    
    separator();
}