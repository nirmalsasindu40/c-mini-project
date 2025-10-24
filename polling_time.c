#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "heder.h"

// Function to set polling time
void admin_set_polling_time() {
    int start_day, start_month, start_year, start_hour, start_minute;
    int end_day, end_month, end_year, end_hour, end_minute;
    
    printf("\n=== SET POLLING TIME ===\n\n");
    
    printf("Enter polling START date and time:\n");
    printf("Day (1-31): ");
    scanf("%d", &start_day);
    printf("Month (1-12): ");
    scanf("%d", &start_month);
    printf("Year: ");
    scanf("%d", &start_year);
    printf("Hour (0-23): ");
    scanf("%d", &start_hour);
    printf("Minute (0-59): ");
    scanf("%d", &start_minute);
    
    printf("\nEnter polling END date and time:\n");
    printf("Day (1-31): ");
    scanf("%d", &end_day);
    printf("Month (1-12): ");
    scanf("%d", &end_month);
    printf("Year: ");
    scanf("%d", &end_year);
    printf("Hour (0-23): ");
    scanf("%d", &end_hour);
    printf("Minute (0-59): ");
    scanf("%d", &end_minute);
    
    // Save to file
    FILE *fp = fopen("polling_time.txt", "w");
    if (fp == NULL) {
        printf("\nError: Could not save polling time!\n\n");
        separator();
        return;
    }
    
    fprintf(fp, "%d/%d/%d %d:%d %d/%d/%d %d:%d",
            start_day, start_month, start_year, start_hour, start_minute,
            end_day, end_month, end_year, end_hour, end_minute);
    
    fclose(fp);
    
    // Set polling status to active
    FILE *fp_status = fopen("polling_status.txt", "w");
    if (fp_status != NULL) {
        fprintf(fp_status, "1");
        fclose(fp_status);
    }
    
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

// Function to check if polling is currently active
int is_polling_active() {
    FILE *fp = fopen("polling_time.txt", "r");
    if (fp == NULL) {
        return 0; // No polling time set
    }
    
    int start_day, start_month, start_year, start_hour, start_minute;
    int end_day, end_month, end_year, end_hour, end_minute;
    
    fscanf(fp, "%d/%d/%d %d:%d %d/%d/%d %d:%d",
           &start_day, &start_month, &start_year, &start_hour, &start_minute,
           &end_day, &end_month, &end_year, &end_hour, &end_minute);
    
    fclose(fp);
    
    // Get current time
    time_t now = time(NULL);
    struct tm *current_time = localtime(&now);
    
    // Create time structures for comparison
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