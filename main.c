#include <stdio.h>
#include <stdlib.h>
#include "heder.h"

char choice;

int main() {
    system("cls");
    doubleline();
    printf("WELCOME TO THE PARLIAMENT ELECTION SYSTEM\n");
    doubleline();
    
<<<<<<< HEAD

    printf("Menu:\n\n");
    printf("1.Adimn panel\n");
    printf("2.Voter Registration\n");
    printf("3.Voter loging\n");
    printf("4.Candidate Registration\n");
    printf("5.Candidate login\n");
    printf("6.party registertion\n");
    printf("6.party login\n");
    printf("7.polling\n");
    printf("8.results\n");
    printf("0.exit\n\n");

    separator();

    printf("enter your choice : ");
    scanf(" %c",&choice);

    switch(choice){
        case '1':
            printf("\nyou are in ADMIN PANEL\n");
            break;

        case '2':
            printf("\nyou are Voter Registration\n");
            voter_registration();
            break;

        case '3':
            printf("\nyou are in Candidate Registration\n");
            candidate_registration();
            break;

        case '4': 
            printf("\nyou are in party registertion\n");
            break;

        case '5':
            printf("\nyou are in polling\n");
            break;

        case '6':
            printf("\nyou are in results\n\n");
            loging_party();
            break;

        case '0':
            printf("\nyou are choosed exit................\n\n");
            break;

        default:
            printf("\nenter the corrrect valied number\n");


=======
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
                doubleline();
                printf("PARTY REGISTRATION\n");
                doubleline();
                printf("\nParty registration feature coming soon...\n\n");
                separator();
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
>>>>>>> TG_2097_B1
        
    } while (choice != '0');
    
    return 0;
}