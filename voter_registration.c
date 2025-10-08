#include<stdio.h>
#include<string.h>
#include "heder.h"

void voter_registration(){
    char name[100];
    char district[20];
    char username[50];
    char nic[20];
    char password[25];
    FILE * fp;

    printf("enter your name - ");
    scanf("%s",name);

    printf("enter your district - ");
    scanf("%s",district);

    printf("enter your user name - ");
    scanf("%s",username);

    printf("enter your NIC number - ");
    scanf("%s",nic);

    printf("enter your PASSWORD - ");
    scanf("%s",password);

    
    fp = fopen("voter registration data.txt","a");

    if (fp == NULL){
        printf("file opening error");
        return;
    }

    fprintf(fp,"name : %s\n",name);
    fprintf(fp,"username : %s\n",username);
    fprintf(fp,"NIC number : %s\n",nic);
    fprintf(fp,"password : %s\n",password);
    fprintf(fp,"district : %s\n",district);
    file_separator(fp);

    fclose(fp);

    printf("\nRegistration is successfull........\n\n\n");


    separator();



}
