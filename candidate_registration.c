#include<stdio.h>
#include<string.h>
#include "heder.h"

void candidate_registration(){
    char name[100];
    char party[150];
    char district[25];
    int election_number[20];
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

    printf("enter your election_number : ");
    scanf("%d",election_number);

    printf("enter your NIC number : ");
    scanf("%s",nic);

    printf("enter your username : ");
    scanf("%S",username);

    printf("enter your password : ");
    scanf("%s",password);

    fp = fopen("candidate registration data.txt","a");

    if(fp == NULL){
        printf("file opening error");
        return;
    }

    fprintf(fp,"name : %s\n",name);
    fprintf(fp, "party : %s\n",party);
    fprintf(fp, "election number : %d\n",election_number);
    fprintf(fp, "NIC number : %s\n",nic);
    fprintf(fp, "username : %s\n",username);
    fprintf(fp, "password : %s\n",password);

    file_separator(fp);
    fclose(fp);
    
    printf("Registration is succesfull....\n");

    separator();

    
}
