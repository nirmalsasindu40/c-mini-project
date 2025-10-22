#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "heder.h"



int loging_party(){
        doubleline();
        printf("               party Loging Potal\n");
        doubleline();
        char username[10];
        char pwd[10];
        char choisse;
        printf("Enter Username: ");
        scanf("%s",username);
        printf("Enter Passwerd: ");
        scanf("%s",pwd);
        if (strcmp(username,"p") == 0 && strcmp(pwd,"p") == 0){
                do{
                Party_Registration();
                
                printf("\n\nbdjhscjsd (Y/N) : " );
                scanf(" %c",&choisse);
                
                } while(choisse == 'y' || choisse == 'Y');
        }


}
int Party_Registration(){

        char name[20];
        int code;
        char leader[25];
        FILE *fp;
        doubleline();
        printf("\t\t\tWELCOME TO THE PARLIMENT ELECTION SYSTEM\n");
        doubleline();
        printf("\n\t\t----------- Party Registration ------------\n");

        printf("Enter Party Name: ");
        scanf("%s",name);
        printf("Enter Party code: ");
        scanf("%d",&code);
        printf("Enter Party Leader: ");
        scanf("%s",leader);

        fp = fopen("Party_Registration.txt","w");

        if (fp == NULL){

                printf("File dose not exist plase check!\n");
                
        }
        fprintf(fp,"%s %d %s",name,code,leader);
        fclose(fp);


        printf("Party Registered Successfully!\n");
        

       

}













