#include <stdio.h>
#include <stdlib.h>
#include "heder.h"

char choice;

int main() {
    system("cls");
    doubleline();
    printf("WELCOME TO THE PARLIAMENT ELECTION SYSTEM\n");
    doubleline();
        
    do {
        printf("\n");
        printf("Main Menu:\n\n");
        printf("1. Admin Panel\n");
        printf("2. Voter Registration\n");
        printf("3. Voter Login\n");
        printf("4. Candidate Registration\n");
        printf("5. Candidate Login\n");
        printf("6. Party Registration\n");
        printf("7. Party Login\n");
        printf("8. Polling (Cast Vote)\n");
        printf("9. View Results\n");
        printf("0. Exit\n\n");
        
        separator();
        
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        
        switch(choice) {
            case '1':
               
                break;
            
            case '2':
                system("cls");
                doubleline();
                printf("VOTER REGISTRATION\n");
                doubleline();
                voter_registration();
                break;
            
            case '3':
                
                break;
            
            case '4':
                system("cls");
                doubleline();
                printf("CANDIDATE REGISTRATION\n");
                doubleline();
                candidate_registration();
                break;
            
            case '5':
                
                break;
            
            case '6':
                system("cls");
                loging_party();
                
<<<<<<< HEAD
               
               
                separator();
=======
>>>>>>> 7c7fb0d538d7ee70ad7dc6350fd733efd41287ca
                break;
            
            case '7':
                system("cls");
                doubleline();
                printf("PARTY LOGIN\n");
                doubleline();
                printf("\nParty login feature coming soon...\n\n");
                separator();
                break;
            
            case '8':
                
                break;
            
            case '9':
                system("cls");
                doubleline();
                printf("ELECTION RESULTS\n");
                doubleline();
                
                break;
            
            case '0':
                system("cls");
                doubleline();
                printf("EXITING SYSTEM\n");
                doubleline();
                printf("\nThank you for using the Parliament Election System.\n");
                printf("Goodbye!\n\n");
                separator();
                break;
            
            default:
                system("cls");
                printf("\n✗ Invalid choice! Please enter a valid option.\n\n");
                separator();
        }
        
    } while (choice != '0');
    
    return 0;
}