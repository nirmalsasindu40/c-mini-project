#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "heder.h"
//function for read the candidate registration data file
int count_all_votes(char names[][100], char parties[][150], char districts[][25], 
                    int election_numbers[], int vote_counts[], int max_candidates) {
    FILE *fp_candidates = fopen("candidate registration data.txt", "r");
    if (fp_candidates == NULL) {
        printf("No candidates registered!\n");
        return 0;
    }