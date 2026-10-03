#include <stdio.h>

struct Account
{
    int accountNo;
    char name[50];
    float balance;
};

void createAccount()
{
    struct Account a;
    FILE *fp;

    fp = fopen("accounts.dat", "ab");

    printf("Enter Account Number: ");
    scanf("%d", &a.accountNo);

    printf("Enter Name: ");
    scanf(" %[^\n]", a.name);

    printf("Enter Initial Balance: ");
    scanf("%f", &a.balance);

    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);

    printf("Account created successfully.\n");
}

void deposit()
{
    struct Account a;
    int accNo, found = 0;
    float amount;
    FILE *fp;

    fp = fopen("accounts.dat", "rb+");

    if(fp == NULL)
    {
        printf("No accounts found.\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while(fread(&a, sizeof(a), 1, fp))
    {
        if(a.accountNo == accNo)
        {
            printf("Enter Deposit Amount: ");
            scanf("%f", &amount);

            a.balance += amount;

            fseek(fp, -sizeof(a), SEEK_CUR);
            fwrite(&a, sizeof(a), 1, fp);

            printf("Amount deposited successfully.\n");
            found = 1;
            break;
        }
    }

    fclose(fp);

    if(!found)
        printf("Account not found.\n");
}

void withdraw()
{
    struct Account a;
    int accNo, found = 0;
    float amount;
    FILE *fp;

    fp = fopen("accounts.dat", "rb+");

    if(fp == NULL)
    {
        printf("No accounts found.\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while(fread(&a, sizeof(a), 1, fp))
    {
        if(a.accountNo == accNo)
        {
            printf("Enter Withdrawal Amount: ");
            scanf("%f", &amount);

            if(amount > a.balance)
            {
                printf("Insufficient balance.\n");
            }
            else
            {
                a.balance -= amount;

                fseek(fp, -sizeof(a), SEEK_CUR);
                fwrite(&a, sizeof(a), 1, fp);

                printf("Amount withdrawn successfully.\n");
            }

            found = 1;
            break;
        }
    }

    fclose(fp);

    if(!found)
        printf("Account not found.\n");
}

void balanceEnquiry()
{
    struct Account a;
    int accNo, found = 0;
    FILE *fp;

    fp = fopen("accounts.dat", "rb");

    if(fp == NULL)
    {
        printf("No accounts found.\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while(fread(&a, sizeof(a), 1, fp))
    {
        if(a.accountNo == accNo)
        {
            printf("\nAccount Number: %d", a.accountNo);
            printf("\nName: %s", a.name);
            printf("\nBalance: %.2f\n", a.balance);

            found = 1;
            break;
        }
    }

    fclose(fp);

    if(!found)
        printf("Account not found.\n");
}

int main()
{
    int choice;

    do
    {
        printf("\n===== Banking System =====");
        printf("\n1. Create Account");
        printf("\n2. Deposit");
        printf("\n3. Withdraw");
        printf("\n4. Balance Enquiry");
        printf("\n5. Exit");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                createAccount();
                break;

            case 2:
                deposit();
                break;

            case 3:
                withdraw();
                break;

            case 4:
                balanceEnquiry();
                break;

            case 5:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while(choice != 5);

    return 0;
}