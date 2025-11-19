#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int voter();
int admin();
int adminMenu();
int login();
void updated();
int registerVoter();
int candidatefunc();
int id;
char pass[50];
char passAdmin[50];
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
    char candGender[10];
    int candAge;
};

struct voter voters[100];
char line[200];
int voterCount = 0;

int main()
{
    FILE *fp = fopen("voter.csv", "r");
    if(!fp){
        printf("Unable to open a FILE!!\n");
        return 1;
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
        voterCount++;
    }
    registerVoter();
    int fmain;
    printf("========================\n"
           "         VOTE-IT       \n\n"
           "Your votes are safe here!\n"
           "========================\n");
    intro:
    printf("Are you a: \n"
           "1. Voter\n"
           "2. Admin\n");
    printf("Select an option: ");
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
int admin()
{
    int adminID;
    int adminActualID = 123;
    char passActualAdmin[50] = "admin123";
    loginAdmin:
    printf("Enter your Admin ID: ");
    scanf("%d", &adminID);
    printf("Enter your password: ");
    scanf("%s", &passAdmin);
    if(adminID != 123)
    {
        printf("No such Admin ID\n");
        goto loginAdmin;
    }
    else
    {
        if(strcmp(passAdmin, passActualAdmin)==0)
        {
        printf("Successfully logged in as Admin\n");
        }
        else
        {
            printf("Incorrect password");
            goto loginAdmin;
        }
    }
    return 0;
}
int adminMenu()
{
    int adMenu;
    printf("=========================\n"
           "  Welcome to Admin Panel \n"
           "=========================\n");
    printf("1. Add/Register Candidate\n"
           "2. Add/Register New Voter\n"
           "3. Register a Classroom\n"
           "4. Logout\n");
    printf("Select one of the options (1-4): ");
    scanf("%d", &adMenu);

    if(adMenu==2)
    {
        registerVoter();
    }
    else if(adMenu==1)
    {

    }
    else if(adMenu==3)
    {

    }
    else if(adMenu==4)
    {
        main();
    }
    else
    {
        printf("Invalid Input, try again");
        adminMenu();
    }
}

void update() {
    FILE *fp = fopen("voter.csv", "w"); 
    if (fp == NULL) {
        printf("Error updating file!\n");
        return;
    }
    for (int i = 0; i < voterCount; i++) {
        fprintf(fp, "%d,%s,%s,%d\n", voters[i].voterID, voters[i].voterPass, voters[i].name, voters[i].vote);
    }
    fclose(fp);
    printf("Voter FILE updated successfully.\n");
}

int registerVoter(){
    int new_num;
    printf("==========================================\n"
           "    Welcome to NEW voter Registration! \n"
           "==========================================\n");
           printf("Enter the number of new voters that you want to register:-");
           scanf("%d", &new_num);
           voterCount += new_num;
           int a = voterCount - new_num;
           for(int i = 0; i < new_num; i++){
            printf("Enter the details of the voter no. %d\n", i);
            printf("Enter voter's ID:- ");
            scanf("%d", &voters[a].voterID);
            printf("Enter voter's password:- ");
            scanf("%s", voters[a].voterPass);
            printf("Enter voter's name:- ");
            scanf("%s", voters[a].name);
            voters[a].vote = 0;
            a++;
           }
    update();
    return 0;

}
int candidatefunc()
{
    int new_cand;
    printf("================================\n"
           "       Add New Candidates!      \n"
           "================================\n");
    printf("Enter the number of new candidates you want to register:- ");
    scanf("%d", &new_cand);
}

