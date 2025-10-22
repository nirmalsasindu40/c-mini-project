#include<stdio.h>
#include<string.h>
#include "heder.h"

void candidate_registration(){
    char name[100];
    char party[150];
    char district[25];
    int election_number[20];
    int age[3];
    char nic[50];
    char username[55];
    char password[25];
    FILE * fp;
    
    printf("enter your name : ");
    scanf("%s",name);

    printf("enter your party : ");
    scanf("%s",party);

    printf("enter your district : ");
    scanf("%s",district);
    
    printf("Enter your election number: ");
    while(scanf("%d", &election_number) != 1) {  
        printf("Invalid input! Please enter a number: ");
        while(getchar() != '\n');  
    }

    printf("enter your age - ");
     while(scanf("%d", age) != 1) {  
        printf("Invalid input! Please enter a number: ");
        while(getchar() != '\n');  
    }

    printf("enter your NIC number : ");
    scanf("%s",nic);

    printf("enter your username : ");
    scanf("%s",username);

    printf("enter your password : ");
    scanf("%s",password);

    fp = fopen("candidate registration data.txt","a");

    if(fp == NULL){
        printf("file opening error");
        return;
    }

    fprintf(fp,"%s|%s|%s|%d|%s|%s|%s\n",name,party,district,election_number,nic,username,password);

    fclose(fp);
    
    printf("Registration is succesfull....\n");

    separator();

    
}
