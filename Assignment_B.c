#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int voter();
int admin();
int adminMenu();
int login();
int updateC();
int updateV();
int registerVoter();
int candidatefunc();
int candDisplay();
int quickVote();
int showResults();
int showPercentVotes();
int showBarGraph();
int sortByVotes();
int quickVoteStats();
int id;

int classVotes[100];
int classTotalVotes = 0;

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
    char candName[50];
    char candParty[50];
    char candGender[10];
    int candAge;
    int votes;
};

struct voter voters[100];
struct candidate cand[100];
char line[200];
char lineC[200];
int voterCount = 0;
int candCount = 0;

int main()
{
    FILE *fp = fopen("voter.csv", "r");
    FILE *fc = fopen("candidate.csv", "r");

    if(!fp || !fc){
        printf("Unable to open a FILE!!\n");
        return 1;
    }

    int i = 0;
    while((fgets(line, sizeof(line), fp)) != NULL){
        char *token = strtok(line, ",");
        voters[i].voterID = atoi(token);

        token = strtok(NULL, ",");
        strcpy(voters[i].voterPass, token);

        token = strtok(NULL, ",");
        strcpy(voters[i].name, token);
        voters[i].name[strcspn(voters[i].name, "\n")] = 0;

        token = strtok(NULL, ",");
        voters[i].vote = token ? atoi(token) : 0;

        i++;
        voterCount++;
    }

    int c = 0;
    while (fgets(lineC, sizeof(lineC), fc) != NULL) {

        char *tokenC = strtok(lineC, ",");
        if(!tokenC) continue;
        cand[c].candID = atoi(tokenC);

        tokenC = strtok(NULL, ",");
        strcpy(cand[c].candName, tokenC);

        tokenC = strtok(NULL, ",");
        strcpy(cand[c].candParty, tokenC);

        tokenC = strtok(NULL, ",");
        strcpy(cand[c].candGender, tokenC);

        tokenC = strtok(NULL, ",");
        cand[c].candAge = atoi(tokenC);

        tokenC = strtok(NULL, ",");
        cand[c].votes = tokenC ? atoi(tokenC) : 0;

        c++;
    }
    candCount = c;

    fclose(fp);
    fclose(fc);

    int option;

main_menu:
    printf("\n========================\n");
    printf("         VOTE-IT\n");
    printf("========================\n");
    printf("1. Voter Login\n");
    printf("2. Admin Login\n");
    printf("3. Quick Classroom Voting\n");
    printf("4. Exit\n");
    printf("Select an option: ");
    scanf("%d", &option);

    switch(option)
    {
        case 1:
            voter();
            break;

        case 2:
            admin();
            break;

        case 3:
            quickVote();
            break;

        case 4:
            printf("Exiting...\n");
            return 0;

        default:
            printf("Invalid option. Try again.\n");
            break;
    }

    goto main_menu;
}

int voter()
{
    int j = 0;
    int found = 0;

    printf("\n========================\n");
    printf("  Welcome to your booth \n");
    printf("========================\n");

retry:
    printf("Enter your Voter ID: ");
    scanf("%d", &id);

    printf("Enter your Password: ");
    scanf("%s", pass);

    for(j = 0; j < voterCount; j++){
        if(id == voters[j].voterID){
            found = 1;
            break;
        }
    }

    if(!found){
        printf("No such Voter ID. Try again.\n");
        goto retry;
    }

    if(strcmp(pass, voters[j].voterPass) != 0){
        printf("Incorrect Password.\n");
        goto retry;
    }

    if(voters[j].vote != 0){
        printf("You have already voted!\n");
        return 0;
    }

    printf("Login Successful. Welcome %s!\n", voters[j].name);

    candDisplay();

    printf("Enter Candidate ID to cast your vote: ");
    int chosenID;
    scanf("%d", &chosenID);

    int foundCand = 0;

    for (int k = 0; k < candCount; k++) {
        if (cand[k].candID == chosenID) {
            cand[k].votes++;
            foundCand = 1;
            break;
        }
    }

    if (!foundCand) {
        printf("Invalid Candidate ID! Vote not counted.\n");
        return 0;
    }

    voters[j].vote = 1;   
    updateV();
    updateC();

    printf("Your vote has been successfully recorded!\n");

    return 0;
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
        adminMenu();
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
    int choice;

admin_menu:
    printf("\n=========================\n");
    printf("      ADMIN PANEL\n");
    printf("=========================\n");
    printf("1. Register New Candidate\n");
    printf("2. Register New Voter\n");
    printf("3. Show Official Election Results\n");
    printf("4. Show Live Vote Percentages\n");
    printf("5. Show ASCII Vote Bar Graph\n");
    printf("6. Sort Candidates by Votes\n");
    printf("7. Logout\n");
    printf("Select an option: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            candidatefunc();
            break;
        case 2:
            registerVoter();
            break;
        case 3:
            showResults();
            break;
        case 4:
            showPercentVotes();
            break;
        case 5:
            showBarGraph();
            break;
        case 6:
            sortByVotes();
            break;
        case 7:
            printf("Logging out...\n");
            return 0;

        default:
            printf("Invalid input.\n");
    }

    goto admin_menu;
}


int updateV() {
    FILE *fp = fopen("voter.csv", "w"); 
    if (fp == NULL) {
        printf("Error updating file!\n");
        return 0;
    }
    for (int i = 0; i < voterCount; i++) {
        fprintf(fp, "%d,%s,%s,%d\n", voters[i].voterID, voters[i].voterPass, voters[i].name, voters[i].vote);
    }
    fclose(fp);
    printf("Voter FILE updated successfully.\n");
}
int updateC() {
    FILE *fp = fopen("candidate.csv", "w"); 
    if (fp == NULL) {
        printf("Error updating file!\n");
        return 0;
    }
    for (int i = 0; i < candCount; i++) {
        fprintf(fp, "%d,%s,%s,%s,%d,%d\n", cand[i].candID, cand[i].candName, cand[i].candParty, cand[i].candGender, cand[i].candAge, cand[i].votes);
    }
    fclose(fp);
    printf("Candidate FILE updated successfully.\n");
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
            printf("Enter the details of the voter no. %d\n", i+1);
            printf("Enter voter's ID:- ");
            scanf("%d", &voters[a].voterID);
            printf("Enter voter's password:- ");
            scanf("%s", voters[a].voterPass);
            printf("Enter voter's name:- ");
            scanf("%s", voters[a].name);
            voters[a].vote = 0;
            a++;
           }
    updateV();
    return 0;

}
int candidatefunc()
{   
    FILE *wipe = fopen("candidate.csv", "w"); //flushes the candidate file so that there is no stray info left
    fclose(wipe); 
    int new_cand;
    printf("================================\n"
           "       Add New Candidates!      \n"
           "================================\n");
    printf("Enter the number of new candidates you want to register:- ");
    scanf("%d", &new_cand);
    for(int i = 0; i < new_cand; i++){
            printf("Enter the details of the voter no. %d\n\n", i+1);
            printf("Enter candidate's ID:- ");
            scanf("%d", &cand[i].candID);
            printf("Enter candidate's name:- ");
            scanf("%s", cand[i].candName);
            printf("Enter candidate's Party:- ");
            scanf("%s", cand[i].candParty);
            printf("Enter candidate's gender:- ");
            scanf("%s", cand[i].candGender);
            printf("Enter candidate's age:- ");
            scanf("%d", &cand[i].candAge);
            cand[i].votes = 0;
           }
           candCount = new_cand;
    updateC();
}
int candDisplay() 
{
    printf("\n=================================\n");
    printf("       LIST OF CANDIDATES\n");
    printf("=================================\n");

    if(candCount == 0) {
        printf("No candidates registered yet.\n");
        return 0;
    }

    for(int i = 0; i < candCount; i++) {
        printf("\nCandidate %d:\n", i+1);
        printf("ID       : %d\n", cand[i].candID);
        printf("Name     : %s\n", cand[i].candName);
        printf("Party    : %s\n", cand[i].candParty);
        printf("Gender   : %s\n", cand[i].candGender);
        printf("Age      : %d\n", cand[i].candAge);
        printf("Votes    : %d\n", cand[i].votes);
        printf("---------------------------------\n");
    }

    return 0;
}
int quickVote()
{
    int choice;
    for(int i = 0; i < 100; i++){
        classVotes[i] = 0; }

    printf("\n====================================\n");
    printf("         QUICK CLASSROOM VOTING\n");
    printf("====================================\n");

    if (candCount == 0) {
        printf("No candidates available!\n");
        return 0;
    }

    printf("Candidates available:\n");
    for (int i = 0; i < candCount; i++) {
        printf("%d. %s (%s)\n", cand[i].candID, cand[i].candName, cand[i].candParty);
    }

    printf("\nStart entering votes (Candidate ID).\n");
    printf("Enter 0 to stop voting.\n\n");

    while (1) {
        printf("Vote: ");
        scanf("%d", &choice);

        if (choice == 0) {
            printf("Voting session ended.\n");
            break;
        }

        int found = 0;
        for (int i = 0; i < candCount; i++) {
            if (cand[i].candID == choice) {
                classVotes[i]++;       
                classTotalVotes++;      
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Invalid Candidate ID! Try again.\n");
        }
    }

    FILE *fclass = fopen("classVote.csv", "w");
    if (!fclass) {
        printf("Error creating classVote.csv!\n");
        return 0;
    }

    fprintf(fclass, "CandID,CandName,Party,ClassVotes\n");
    for (int i = 0; i < candCount; i++) {
        fprintf(fclass, "%d,%s,%s,%d\n",
                cand[i].candID,
                cand[i].candName,
                cand[i].candParty,
                classVotes[i]);
    }

    fclose(fclass);

    printf("\nClassroom voting results saved to classVote.csv!\n");
    quickVoteStats();
    return 0;
}
int showResults()
{
    printf("\n=================================\n");
    printf("      OFFICIAL ELECTION RESULTS\n");
    printf("=================================\n");

    if(candCount == 0) {
        printf("No candidates found!\n");
        return 0;
    }

    int winnerIndex = 0;

    for(int i = 0; i < candCount; i++) {
        printf("\nCandidate %d:\n", i+1);
        printf("ID       : %d\n", cand[i].candID);
        printf("Name     : %s\n", cand[i].candName);
        printf("Party    : %s\n", cand[i].candParty);
        printf("Votes    : %d\n", cand[i].votes);

        if(cand[i].votes > cand[winnerIndex].votes) {
            winnerIndex = i;
        }
    }

    printf("\n=================================\n");
    printf("            WINNER\n");
    printf("=================================\n");
    printf("Name   : %s\n", cand[winnerIndex].candName);
    printf("Party  : %s\n", cand[winnerIndex].candParty);
    printf("Votes  : %d\n", cand[winnerIndex].votes);
    printf("=================================\n");

    return 0;
}
int sortByVotes()
{
    struct candidate temp[100];


    for (int i = 0; i < candCount; i++) {
        temp[i] = cand[i];
    }

    for (int i = 0; i < candCount - 1; i++) {
        for (int j = 0; j < candCount - i - 1; j++) {

            if (temp[j].votes < temp[j+1].votes) {
                struct candidate swap = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = swap;
            }
        }
    }

    printf("\n=================================\n");
    printf("   CANDIDATES SORTED BY VOTES\n");
    printf("=================================\n");

    for (int i = 0; i < candCount; i++) {
        printf("\nRank %d\n", i+1);
        printf("Name   : %s\n", temp[i].candName);
        printf("Party  : %s\n", temp[i].candParty);
        printf("Votes  : %d\n", temp[i].votes);
        printf("---------------------------------\n");
    }

    return 0;
}
int showBarGraph()
{
    if(candCount == 0){
        printf("No candidates available.\n");
        return 0;
    }
    printf("\n=================================\n");
    printf("         OFFICIAL VOTE GRAPH\n");
    printf("=================================\n\n");

    int maxVotes = 1;
    for(int i = 0; i < candCount; i++) {
        if(cand[i].votes > maxVotes)
            maxVotes = cand[i].votes;
    }
    int maxBarWidth = 50; 
    for(int i = 0; i < candCount; i++) {
        int barLen = (cand[i].votes * maxBarWidth) / maxVotes;
        printf("%-20s | ", cand[i].candName);
        for(int j = 0; j < barLen; j++)
            printf("█");
        printf(" (%d)\n", cand[i].votes);
    }
    return 0;
}
int showPercentVotes()
{
    printf("\n=================================\n");
    printf("       VOTE PERCENTAGE CHART\n");
    printf("=================================\n");

    int totalVotes = 0;

    for (int i = 0; i < candCount; i++) {
        totalVotes += cand[i].votes;
    }

    if (totalVotes == 0) {
        printf("No votes have been cast yet.\n");
        return 0;
    }

    for (int i = 0; i < candCount; i++) {
        float percent = (cand[i].votes * 100.0) / totalVotes;

        printf("\nCandidate: %s (%s)\n", cand[i].candName, cand[i].candParty);
        printf("Votes: %d (%.2f%%)\n", cand[i].votes, percent);
        printf("---------------------------------\n");
    }

    return 0;
}
int quickVoteStats()
{
    printf("\n=================================\n");
    printf("      QUICK VOTE STATISTICS\n");
    printf("=================================\n");

    if(classTotalVotes == 0) {
        printf("No quick votes have been cast yet.\n");
        return 0;
    }

    printf("\n------------ SORTED ORDER -----------\n");

    struct candidate temp[100];
    int tempVotes[100];

    for(int i = 0; i < candCount; i++) {
        temp[i] = cand[i];
        tempVotes[i] = classVotes[i];
    }

    for(int i = 0; i < candCount - 1; i++) {
        for(int j = 0; j < candCount - i - 1; j++) {
            if(tempVotes[j] < tempVotes[j+1]) {
                int v = tempVotes[j];
                tempVotes[j] = tempVotes[j+1];
                tempVotes[j+1] = v;

                struct candidate c = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = c;
            }
        }
    }

    for(int i = 0; i < candCount; i++) {
        printf("Rank %d → %s (%s) : %d votes\n",
               i+1,
               temp[i].candName,
               temp[i].candParty,
               tempVotes[i]);
    }

    printf("\n------------ PERCENTAGES -----------\n");

    for(int i = 0; i < candCount; i++) {
        float percent = (classVotes[i] * 100.0) / classTotalVotes;

        printf("%s (%s): %.2f%%\n",
               cand[i].candName,
               cand[i].candParty,
               percent);
    }

    

    printf("\n----------- ASCII GRAPH ------------\n");
    int maxVotes = 1;
    for(int i = 0; i < candCount; i++) {
        if(classVotes[i] > maxVotes)
            maxVotes = classVotes[i];
    }
    int maxBarWidth = 50;
    for(int i = 0; i < candCount; i++) {
        int barLen = (classVotes[i] * maxBarWidth) / maxVotes;
        printf("%-20s | ", cand[i].candName);
        for(int j = 0; j < barLen; j++)
            printf("█");
        printf(" (%d)\n", classVotes[i]);
    }

    printf("\n-------------- WINNER --------------\n");

    int winnerIndex = 0;
    for(int i = 1; i < candCount; i++) {
        if(classVotes[i] > classVotes[winnerIndex]) {
            winnerIndex = i;
        }
    }

    printf("Winner: %s (%s)\n",
           cand[winnerIndex].candName,
           cand[winnerIndex].candParty);

    printf("====================================\n");

    return 0;
}

