#include<stdio.h>
#include<string.h>

int voter();
int admin();

char voterPass[50];
int voterID;
int main()
{
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
