#include <stdio.h>
#include<stdlib.h>
#include "heder.h"

char choice;

int main(){
    system("cls");
    printf("==========================================================================================\n");
    printf("WELCOME TO THE PARLIMENT ELECTION SYSTEM\n");
    printf("==========================================================================================\n\n1");

    do{

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
            system("cls");
            printf("\nyou are in ADMIN PANEL\n");
            break;

        case '2':
            system("cls");
            printf("\nyou are Voter Registration\n");
            voter_registration();
            break;

        case '3':
            system("cls");
            printf("\nyou are in Candidate Registration\n");
            candidate_registration();
            break;

        case '4': 
            system("cls");
            printf("\nyou are in party registertion\n");
            break;

        case '5':
            system("cls");
            printf("\nyou are in polling\n");
            break;

        case '6':
            system("cls");
            printf("\nyou are in results\n\n");
            break;

        case '0':
            system("cls");
            printf("\nyou are choosed exit................\n\n");
            break;

        default:
            system("cls");
            printf("\nenter the corrrect valied number\n");


        
    }


    } while (choice != '0');
    
    

}