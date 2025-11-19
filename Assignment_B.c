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
    char name[50];
    int vote;
};

struct candidate{
    int candID;
    char cadName[50];
    char candParty[50];

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
        char *token = strtok(line, ","); // makes segments
        voters[i].voterID = atoi(token);
        token = strtok(NULL, ",");
        strcpy(voters[i].voterPass, token);
        token = strtok(NULL, ",");
        strcpy(voters[i].name, token);
        voters[i].name[strcspn(voters[i].name, "\n")] = 0; //removes \n
        token = strtok(NULL, ","); // 4th token: vote
        if (token != NULL){ 
            voters[i].vote = atoi(token); // converts string into int and also updates and stores
        } else {
            // Handle case where vote is missing, perhaps set to a default value
            voters[i].vote = 0; 
        }
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
    int found = 0;
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
        printf("Login Successful!\n"
               "Welcome %s!!\n", voters[j].name);
    }
    else{
        printf("Incorrect Password.\n");
    }
    if(voters[j].vote != 0) {
    printf("You have already voted! Access denied.\n");
    return 0;
}
}
int admin(){}

//Add login system to both using Voter ID and admin ID