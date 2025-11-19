#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int voter();
int admin();
int login();

int id;
char pass[50];
struct voter{
    int voterID;
    char voterPass[50];
    int vote;
};

    struct voter voters[100];
    char line[200];
int main()
{
    FILE *fp = fopen("voter.csv", "r");
    if(!fp){
        printf("Unable to open a FILE!!\n");
    }

    int i = 0;

    while((fgets(line, sizeof(line), fp)) != NULL){
        char *token = strtok(line, ",");
        voters[i].voterID = atoi(token);
        token = strtok(NULL, ",");
        strcpy(voters[i].voterPass, token);
        token = strtok(NULL, ",");
        voters[i].vote = atoi(token);
        i++;
    }

    int fmain;
    printf("========================\n"
           "         VOTE-IT       \n\n"
           "Your votes are safe here!\n"
           "========================\n");
    intro:
    printf("Are you a: \n"
           "1. Voter\n"
           "2. Admin\n");
    scanf("%d", &fmain);
    if(fmain == 1)
    {
        voter();
    }
    else if(fmain==2)
    {
        admin();
    }
    else
    {
        printf("Invalid input, try again.");
        goto intro;
    }
    fclose(fp);
    return 0;
}
int voter()
{   int j = 0;
    int found;
    printf("========================\n"
           "  Welcome to your booth \n"
           "========================\n");

    printf("Verify your identity: \n"
           "Enter your Voter ID: ");
    scanf("%d", &id);
    printf("Enter your password: ");
    scanf("%s", pass);
    for(j = 0; j < 100; j++){
        if(id == voters[j].voterID){
            found = 1;
            break;
        }
    }
    if(!found){
        printf("No such Voter ID.\n");
        return 0;
    }
    if(strcmp(pass, voters[j].voterPass) == 0){
        printf("Login Successful!\n");
    }
    else{
        printf("Incorrect Password.\n");
    }
    if(strcmp(pass, voters[j].voterPass) == 0){
        printf("Successfull!!");
    }
    
}
int admin(){}

//Add login system to both using Voter ID and admin ID