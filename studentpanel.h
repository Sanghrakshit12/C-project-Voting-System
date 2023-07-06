#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

void studentPanel();
int isValid(char userID[15]);
int isVoted(char userID[15]);
int isBanned(char userID[15]);
void saveVote(char userID[15],char voteInput);
int extractYear(char userID[15]);
int extractRollNo(char userID[15]);
int checkBranchCode(char userID[15]);

void studentPanel()
{
    char userID[13];
    char voteInput;
    while(1)
	{
		printf("\n\n  To exit press 0");
        printf("\n  Enter user ID:");
        scanf("%s",userID);
        if(strcmp(userID, "0")==0)
				return;
        if(isValid(userID)!=1)
        {
            printf("\n  Invalid User ID(Press Enter)");
            getch();
            continue;
        }
        if(isBanned(userID)!=0)
        {
            printf("\nThis User ID is currently banned...\nContact Admin for the reason...(Press Enter to continue)");
            getch();
            continue;
        }
        if(isVoted(userID)!=0)
        {
            printf("\n  Your PRN entered is already voted\n  Contact Admin for furthur query");
            getch();
            continue;
        }
        printf("\n\n  Candidates for election:");
		for (int i = 0; i < numberOfCandidates; i++)
        {
            printf("\n  %d. %s",i+1,candidateArray[i].cname);
        }
        printf("\n\n  Your Vote(Enter Number):");
        voteInput=getch();
        printf("*");
        if(voteInput-48 < 1 || voteInput-48 > numberOfCandidates)
        {
            printf("\nInvalid Vote\nTry Again...");
            getch();
            continue;
        }
        saveVote(userID,voteInput);
        printf("\n\nThanks for your precious vote(Press Enter)");
        getch();
    }
};

int isValid(char userID[13])
{
    if(strlen(userID)!=12)
        return 0;
    
    int inputedYear=extractYear(userID);
    int inputedRollNo = extractRollNo(userID);
    
    if(inputedYear!=currentValidID.year || checkBranchCode(userID)!=1 || inputedRollNo>currentValidID.totalVoters)
        return 0;

    return 1;
}


int isVoted(char userID[13])
{
    int location=extractRollNo(userID);
    if(studentVotes[location-1]=='0')
        return 0;
    else
        return 1;
}

int isBanned(char userID[13])
{
    int location=extractRollNo(userID);
    if(studentVotes[location-1]=='$')
        return 1;
    else
        return 0;
}

void saveVote(char userID[13],char voteInput)
{
    char filename[20];
    sprintf(filename,"candidate%d.txt",voteInput-48);
    FILE *fp = fopen(filename,"r+");
    int location=extractRollNo(userID);
    studentVotes[location-1]=voteInput;
    candidateArray[voteInput-49].votes++;
    fseek(fp, 0, SEEK_SET);
    fprintf(fp,"%d\n",candidateArray[voteInput-49].votes);
    fseek(fp, 0, SEEK_END);
    fprintf(fp,"\n%d",location);
    fclose(fp);
}

int extractYear(char userID[13])
{
    int year=0;
    char tmp;
    for(int i=0;i<4;i++){
        tmp=userID[i];
		year=(year*10)+(tmp-48);
    }
    return year;
}

int extractRollNo(char userID[13])
{
    int rollno=0;
    char tmp;
    for(int i=9;i<12;i++){
        tmp=userID[i];
		rollno=(rollno*10)+(tmp-48);
    }
    return rollno;
}


int checkBranchCode(char userID[13])
{
    char branchCode[6];
    for(int i=4;i<9;i++){
        branchCode[i-4]=userID[i];
    }
    branchCode[5]='\0';
    if(strcmp(branchCode,currentValidID.branch)==0)
        return 1;
    else
        return 0;
}
