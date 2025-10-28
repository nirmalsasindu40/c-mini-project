#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "heder.h"

void voter_registration(){
    char name[100];
    int age[3];
    char district[20];
    char username[50];
    char nic[20];
    char password[25];
    FILE * fp;

    printf("enter your name - ");
    scanf("%s",name);

    printf("entyer your age - ");
    while(scanf("%d", age) != 1) {  
        printf("Invalid input! Please enter a number: ");
        while(getchar() != '\n');  
    }

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

    fprintf(fp, "%s|%d|%s|%s|%s|%s\n",name,age,district,username,nic,password);

    fclose(fp);

    printf("\nRegistration is successfull........\n\n\n");


    separator();




}

