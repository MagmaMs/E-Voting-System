#include<stdio.h>
#include<string.h>

int voter();
int admin();
int login();

struct voter{
    int voterID;
    char voterPass[50];
    int vote;
};
int main()
{
    FILE *fp = fopen("voter.csv", "r");
    if(!fp){
        printf("Unable to open a FILE!!\n");
    }

    struct voter voters[100];
    char line[200];
    int i = 0;

    FILE *fp = fopen("voter.csv", "r");
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
    scanf("%d", fmain);
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
}
int voter()
{
    printf("========================\n"
           "  Welcome to your booth \n"
           "========================\n");

    printf("Verify your identity: \n"
           "Enter your Voter ID: ");
    scanf("%d", &voterID);
    printf("Enter your password: ");
    scanf("%s", &voterPass);
}
int admin(){}

//Add login system to both using Voter ID and admin ID