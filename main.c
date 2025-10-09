#include <stdio.h>
#include<stdlib.h>
#include "heder.h"

char choice;

int main(){
    system("cls");
    doubleline();
    printf("WELCOME TO THE PARLIMENT ELECTION SYSTEM\n");
    doubleline();
    do{

    printf("Menu:\n\n");
    printf("1.Adimn panel\n");
    printf("2.Voter Registration\n");
    printf("3.Voter loging\n");
    printf("4.Candidate Registration\n");
    printf("5.Candidate login\n");
    printf("6.party registertion\n");
    printf("7.party login\n");
    printf("8.polling\n");
    printf("9.results\n");
    printf("0.exit\n\n");

    separator();

    printf("enter your choice : ");
    scanf(" %c",&choice);

    switch(choice){
        case '1':
            system("cls");
            doubleline();
            printf("you are in ADMIN PANEL\n");
            doubleline();
            break;

        case '2':
            system("cls");
            doubleline();
            printf("you are in Voter Registration\n");
            doubleline();
            voter_registration();
            break;

        case '3':
            system("cls");
            doubleline();
            printf("you are in voter login\n");
            doubleline();
            break;

        case '4': 
            system("cls");
            doubleline();
            printf("you are in candidate registertion\n");
            doubleline();
            candidate_registration();
            break;

        case '5':
            system("cls");
            doubleline();
            printf("you are in candidate login\n");
            doubleline();
            break;

        case '6':
            system("cls");
            doubleline();
            printf("you are in party registration\n\n");
            doubleline();
            break;

        case '7':
            system("cls");
            doubleline();
            printf("you are in party loging\n");
            doubleline();
            break;

        case '8':
            system("cls");
            doubleline();
            printf("you are in polling\n");
            doubleline();
            break;
        case '9':
            system("cls");
            doubleline();
            printf("you are in results\n");
            doubleline();
            break;

        case '0':
            system("cls");
            doubleline();
            printf("you are exiting..............\n");
            doubleline();
            break;

        default:
            system("cls");
            printf("\nenter the corrrect valied number..................\n");


        
    }


    } while (choice != '0');
    
    

}