#include <stdio.h>
#include <string.h>
#include <windows.h>
#define RESET "\033[0m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define MAGENTA "\033[35m"

struct Account_creation
{
    char Name[100];
    char Address[100];
    int phone_num;
    char Account_No[100];
    int Deposit;
};
struct Account_creation user[100];
FILE *fr, *fw;
void welcomemasage()
{
    printf(CYAN BOLD "\t\t\t\t*******************************************************************************\n" RESET);
    printf(CYAN BOLD "\t\t\t\t||                                                                           ||\n" RESET);
    printf(GREEN BOLD "\t\t\t\t||             _    _   ______    _          _         ________              ||\n" RESET);
    printf(GREEN BOLD "\t\t\t\t||            | |  | | |  _____| | |        | |       |  _____  |            ||\n" RESET);
    printf(GREEN BOLD "\t\t\t\t||            | |__| | | |____   | |        | |       | |     | |            ||\n" RESET);
    printf(GREEN BOLD "\t\t\t\t||            |  __  | |  ____|  | |        | |       | |     | |            ||\n" RESET);
    printf(GREEN BOLD "\t\t\t\t||            | |  | | | |_____  | |______  | |_____  | |_____| |            ||\n" RESET);
    printf(GREEN BOLD "\t\t\t\t||            |_|  |_| |_______| |________| |_______| |_________|            ||\n" RESET);
    printf(CYAN BOLD "\t\t\t\t||                                                                           ||\n" RESET);
    printf(CYAN BOLD "\t\t\t\t||                                                                           ||\n" RESET);
    printf(CYAN BOLD "\t\t\t\t||===========================================================================||\n" RESET);
    printf(CYAN BOLD "\t\t\t\t||                                                                           ||\n" RESET);
    printf(YELLOW BOLD "\t\t\t\t||                     W E L C O M E   T O   S O U M E N ' S                 ||\n" RESET);
    printf(CYAN BOLD "\t\t\t\t||                                                                           ||\n" RESET);
    printf(MAGENTA BOLD "\t\t\t\t||                 * B A N K   M A N A G E M E N T   S Y S T E M *           ||\n" RESET);
    printf(CYAN BOLD "\t\t\t\t||                                                                           ||\n" RESET);
    printf(CYAN BOLD "\t\t\t\t||                                                                           ||\n" RESET);
    printf(CYAN BOLD "\t\t\t\t*******************************************************************************\n" RESET);
}

int readCounter()
{
    FILE *fcounter = fopen("counter.txt", "r");
    int counter = 0;

    if (fcounter != NULL)
    {
        fscanf(fcounter, "%d", &counter);
        fclose(fcounter);
    }

    return counter;
}

void writeCounter(int counter)
{
    FILE *fcounter = fopen("counter.txt", "w");

    if (fcounter != NULL)
    {
        fprintf(fcounter, "%d", counter);
        fclose(fcounter);
    }
}

void CreatAccount()
{
    int i;
    int counter = readCounter();
    for (i = 0; i < 1; i++)
    {
        printf("\n");
        printf("\t\t\t\tEnter Name: ");
        scanf("\t\t\t\t %s", user[i].Name);
        printf("\n");
        printf("\t\t\t\tEnter Address: ");
        scanf(" %s", user[i].Address);
        printf("\n");
        printf("\t\t\t\tEnter Phone Number: ");
        scanf("%d", &user[i].phone_num);
        printf("\n");
        printf("\t\t\t\tEnter Account_No: ");
        scanf(" %s", user[i].Account_No);
        user[i].Deposit = 0;
        printf("\n");
    }
    fw = fopen("Userdata.txt", "a");
    if (fw == NULL)
    {
        printf("Unable to open file");
    }
    for (i = 0; i < 1; i++)
    {
        fprintf(fw, "Name: %s\nAddress: %s\nPhone Num: %d\nAccount_NO: %s\n\n", user[i].Name, user[i].Address, user[i].phone_num, user[i].Account_No);
        counter++;
        writeCounter(counter);
    }
    fclose(fw);
}

void readUserdata(){
    FILE *fr;
    int i;
    fr = fopen("userdata.txt", "r");
    if (fr == NULL)
    {
        printf("\t\t\t\tUnable to open userdata file\n");
        return;
    }
    int count = readCounter();
    for (i = 0; i < count; i++)
    {
        fscanf(fr, "Name: %99[^\n]\nAddress: %99[^\n]\nPhone Num: %d\nAccount_NO: %99[^\n]\n\n",
               user[i].Name, user[i].Address, &user[i].phone_num, user[i].Account_No);
        user[i].Deposit = 0;
    }
}

void readdepositdata()
{
    FILE *fr = fopen("deposit.txt", "r");
    int count = readCounter();
    char tempName[50];
    char tempAccountNo[100];
    int tempDeposit;

    if (fr == NULL)
    {
        printf("\t\t\t\tUnable to open deposit file\n");
        return;
    }
    while (fscanf(fr, "Name: %49[^\n]\nAccount No: %99[^\n]\nDeposit: %d\n\n",
                  tempName, tempAccountNo, &tempDeposit) == 3)
    {
        for (int i = 0; i < count; i++)
        {
            if (strcmp(user[i].Name, tempName) == 0 && strcmp(user[i].Account_No, tempAccountNo) == 0)
            {
                user[i].Deposit += tempDeposit;
                break;
            }
        }
    }

    fclose(fr);
}

void writeUserdata()
{
    FILE *fw = fopen("Userdata.txt", "w"); // Open the file in write mode
    if (fw == NULL)
    {
        printf("Error! Unable to open Userdata.txt file\n");
        return;
    }

    int count = readCounter();
    for (int i = 0; i < count; i++)
    {
        fprintf(fw, "Name: %s\nAddress: %s\nPhone Num: %d\nAccount_NO: %s\n\n",
                user[i].Name, user[i].Address, user[i].phone_num, user[i].Account_No);
    }

    fclose(fw);
}

void updateDepositFile()
{
    FILE *fdeposit = fopen("deposit.txt", "w");
    int count = readCounter();

    if (fdeposit == NULL)
    {
        printf("\t\t\t\tUnable to open deposit file\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        if (user[i].Deposit > 0)
        {
            fprintf(fdeposit, "Name: %s\nAccount No: %s\nDeposit: %d\n\n", user[i].Name, user[i].Account_No, user[i].Deposit);
        }
    }

    fclose(fdeposit);
}

void deletedeposit()
{
    FILE *fw;
    int i;
    fw = fopen("deposit.txt", "w");
    if (fw == NULL)
    {
        printf("\t\t\t\tEror! Unable to open file");
    }
    int count = readCounter();
    for (i = 0; i < count; i++)
    {
        fprintf(fw, "Name: %s\nAccount No: %s\nDeposit: %d\n\n", user[i].Name, user[i].Account_No, user[i].Deposit);
    }
    fclose(fw);
}

void deleteuserdata()
{
    FILE *fw = fopen("userdata.txt", "w");
    if (fw == NULL)
    {
        printf("\t\t\t\tError! Unable to open file\n");
        // return;
    }
    int count = readCounter();
    for (int i = 0; i < count; i++)
    {
        fprintf(fw, "Name: %s\nAddress: %s\nPhone Num: %d\nAccount_NO: %s\n\n",
                user[i].Name, user[i].Address, user[i].phone_num, user[i].Account_No);
    }
    fclose(fw);
}

// void deleteuserdata(){
//     FILE *fw;
//     int i;
//     fw = fopen("userdata.txt","w");
//     if (fw == NULL)
//     {
//         printf("\t\t\t\tEror! Unable to open file");
//     }
//     int count = readCounter();
//     for ( i = 0; i < count; i++)
//     {
//         fscanf(fr, "Name: %99[^\n]\nAddress: %99[^\n]\nPhone Num: %d\nAccount_NO: %99[^\n]\n\n",
//                user[i].Name, user[i].Address, &user[i].phone_num, user[i].Account_No);
//     }
//     fclose(fw);
// }

void BalanceInquiry()
{
    char name[50];
    char userlogindata[100];
    int flag = 0;
    int i;
    printf("\n");
    printf("\t\t\t\tEnter Name: ");
    scanf(" %s", name);
    printf("\n");
    printf("\t\t\t\tEnter Account No: ");
    scanf("%s", userlogindata);
    printf("\n");
    int count = readCounter();
    readUserdata();
    readdepositdata();

    for (i = 0; i < count; i++)
    {
        if (strcmp(user[i].Name, name) == 0 && strcmp(user[i].Account_No, userlogindata) == 0)
        {
            flag = 1;
            break;
        }
    }

    if (flag)
    {
        system("cls");
                int m;
                printf("\t\t\t\t\tLoading");
                for (m = 0; m < 5; m++)
                {
                    printf(".");
                    Sleep(200);
                }
         system("cls");
        int q;
        printf("\n\n");
        printf("\t\t\t\t\t\t  Log In Success!\n");
        printf("\t\t\t\t\t\t  #-------------#\n\n");
        printf("\t\t\t\t\t\xB2\xB2 Hello %s,You have $%d left \xB2\xB2\n", name, user[i].Deposit);
        printf("\t\t\t\t\t***************************************\n");
        printf("\t\t\t\t\n\n");
        readUserdata();
    }
    else
    {
        printf("\t\t\t\tSorry! Account doesn't Find\n\n");   
    }
}

void closeAccount()
{
    char name[50];
    char userlogindata[100];
    int flag = 0;
    int pos = -1;
    int i;
    system("cls"); 
    printf("\n");
    printf("\t\t\t\tEnter Name: ");
    scanf(" %s", name);
    printf("\n");
    printf("\t\t\t\tEnter Account No: ");
    scanf("%s", userlogindata);
    printf("\n");
    int count = readCounter();
    readUserdata();
    readdepositdata();

    for (i = 0; i < count; i++)
    {
        if (strcmp(user[i].Name, name) == 0 && strcmp(user[i].Account_No, userlogindata) == 0)
        {
            pos = i;
            flag = 1;
            break;
        }
    }
    if(flag){
    char k;
    printf("\n");
    printf("\t\t\t\t\xB2 You have $%d left \xB2\n\n", user[i].Deposit);
    printf("\t\t\t\t*Please Withdraw First*\n\n");
    printf("\t\t\t\tEnter y for proced :");
    scanf(" %c", &k);
    printf("\n");
    if (k == 'y')
    {
        if (pos != -1)
        {
            for (i = pos; i < count - 1; i++)
            {
                user[i] = user[i + 1];
            }
            count--;
            writeCounter(count);
            deletedeposit();
            deleteuserdata();
            printf("\n");
            printf("\t\t\t\tUser Removed Successfully\n\n");
        }
    }
      } 
       else
        {
            printf("\t\t\t\tSorry! Account Doesn't Found\n");
        }
    }


int main()
{

    // printf(CYAN BOLD"\t\t\t\t\xB2 \xB2 WELCOME TO SOUMEN'S BANK MANAGWMENT PROJECT \xB2 \xB2\n");
    welcomemasage();
    Sleep(5000);
    system("cls");
    while (1)
    {
        int n, i;
        printf(CYAN BOLD"\t\t\t\t#**************************************************************#\n\n"RESET);
        printf(CYAN"\t\t\t\t1. Create Account\n\n");
        printf("\t\t\t\t2. Deposits/Withdraws\n\n");
        printf("\t\t\t\t3. Balance Inquiry\n\n");
        printf("\t\t\t\t4. Close Account\n\n");
        printf("\t\t\t\t5. Exit\n\n");
        printf("\t\t\t\t>> ");
        scanf("\t\t\t\t%d", &n);
        if (n == 1)
        {
            system("cls");
            CreatAccount();
        }

        if (n == 2)
{
    int flag = 0;
    char name[50];
    char userlogindata[100];
    int NewDeposit;
    system("cls");
    printf("\n");
    printf("\t\t\t\tPlease Log in First\n\n");
    printf("\t\t\t\tEnter Name: ");
    scanf("%s", name);
    printf("\n");
    printf("\t\t\t\tEnter Account No: ");
    scanf("%s", userlogindata);
    printf("\n");
    
    int count = readCounter();
    readUserdata();
    readdepositdata();
    
    int i;
    for (i = 0; i < count; i++)
    {
        if (strcmp(user[i].Name, name) == 0 && strcmp(user[i].Account_No, userlogindata) == 0)
        {
            flag = 1;
            break;
        }
    }

    if (flag)
    {
        system("cls");
        int q;
        printf("\t\t\t\t\tLoading");
        for (int i = 0; i < 6; i++)
        {
            Sleep(200);
            printf(".");
        }
        system("cls");
        printf("\n");
        printf("\t\t\t\t\t  Log In Success!\n");
        printf("\t\t\t\t\t  #-------------#\n\n");
        printf("\t\t\t\tYou have $%d left\n\n", user[i].Deposit);
        printf("\t\t\t\t1. deposit\n\n\t\t\t\t2. withdraw\n\n");
        printf("\t\t\t\t>> ");
        scanf("%d", &q);

        if (q == 1)
        {
            printf("\n");
            printf("\t\t\t\tHow much do you deposit: ");
            scanf("%d", &NewDeposit);
            user[i].Deposit += NewDeposit;
            updateDepositFile(); // Update deposit.txt with new deposit amount
            writeUserdata();     // Update Userdata.txt with updated user data
            printf("\n");
            printf("\t\t\t\tDeposit successful. New balance: $%d\n\n", user[i].Deposit);
        }
        else if (q == 2)
        {
            printf("\n");
            printf("\t\t\t\tHow much do you withdraw: ");
            int withdrawal;
            scanf("%d", &withdrawal);
            if (withdrawal <= user[i].Deposit)
            {
                user[i].Deposit -= withdrawal;
                updateDepositFile(); // Update deposit.txt with new deposit amount
                writeUserdata();     // Update Userdata.txt with updated user data
                printf("\n");
                printf("\t\t\t\tWithdrawal successful. Remaining balance: $%d\n\n", user[i].Deposit);
            }
            else
            {
                printf("\n");
                printf("\t\t\t\tInsufficient funds. Current balance: $%d\n\n", user[i].Deposit);
            }
        }
    }
    else
    {
        printf("\n");
        printf("\t\t\t\tSorry! Account doesn't Find\n");
        printf("\t\t\t\t---------------------------\n\n");
    }
}

        if (n == 3)
        {
            system("cls");
            BalanceInquiry();
        }

        if (n == 4)
        {
            system("cls");
            int i;
            printf("\t\t\t\t\tLoading");
            for ( i = 0; i < 6; i++)
            {
                Sleep(200);
                printf(".");
                
            }
            system("cls");
            
            closeAccount();
        }

        if (n == 5)
        {
            break;
        }
    }

    return 0;
}