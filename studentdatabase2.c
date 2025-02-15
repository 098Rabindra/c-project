#include <stdio.h>
#include <string.h>

void addstudent();
void studentrecord();
void searchstudent();
void delete();

struct student
{
    char first_name[20];
    char last_name[20];
    int roll_no;
    char class[10];
    char vill[20];
    float per;
};

void main()
{
    int choice = 0;  // Initialize the choice variable
    while (choice != 5)
    {
        printf("\t\t\t========STUDENT DATABASE MANAGEMENT SYSTEM======+\n");
        printf("\n\n\n\t\t\t\t  1.Add Student Record\n");
        printf("\t\t\t\t  2.Student Record\n");
        printf("\t\t\t\t  3.Search Students\n");
        printf("\t\t\t\t  4.Delete Record\n");
        printf("\t\t\t\t  5.Exit\n");
        printf("\t\t\t    ___________________________________\n");
        printf("\t\t\t\t  ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addstudent();
            break;
        case 2:
            studentrecord();
            break;
        case 3:
            searchstudent();
            break;
        case 4:
            delete();
            break;
        case 5:
            printf("\t\t\tExiting the system...\n");
            break;
        default:
            printf("\t\t\tInvalid choice. Please try again.\n");
            break;
        }
    }
}

void addstudent()
{
    char another;
    FILE *fp;
    struct student info;

    do
    {
        printf("\t\t\t\t\t========Add student info==========\n\n\n");
        fp = fopen("student_info.txt", "a");
        if (fp == NULL)
        {
            fprintf(stderr, "\t\t\tCan't open file\n");
            return;
        }

        printf("\n\t\tEnter First name : ");
        scanf("%s", info.first_name);
        printf("\t\tEnter Last name : ");
        scanf("%s", info.last_name);
        printf("\t\tEnter Roll no   : ");
        scanf("%d", &info.roll_no);
        printf("\t\tEnter class     : ");
        scanf("%s", info.class);
        printf("\t\tEnter address   : ");
        scanf("%s", info.vill);
        printf("\t\tEnter Percentage : ");
        scanf("%f", &info.per);
        printf("\n\t\t\t_____________________________________\n");

        fwrite(&info, sizeof(struct student), 1, fp);
        fclose(fp);

        printf("\t\t\tRecord stored Successfully\n");

        printf("\t\t\tDo You Want to add another record (y/n): ");
        scanf(" %c", &another);  // Notice the space before %c to consume the previous newline character
    } while (another == 'y' || another == 'Y');
}

void studentrecord()
{
    FILE *fp;
    struct student info;
    fp = fopen("student_info.txt", "r");
    if (fp == NULL)
    {
        printf("\t\t\tNo records found.\n");
        return;
    }

    printf("\t\t\t====Student Records====\n");
    while (fread(&info, sizeof(struct student), 1, fp))
    {
        printf("\n\t\t\t First Name: %s\n", info.first_name);
        printf("\t\t\t Last Name: %s\n", info.last_name);
        printf("\t\t\t Roll No: %d\n", info.roll_no);
        printf("\t\t\t Class: %s\n", info.class);
        printf("\t\t\t Village: %s\n", info.vill);
        printf("\t\t\t Percentage: %.2f\n", info.per);
        printf("\n\t\t\t\t----------------------------------------\n");
    }
    fclose(fp);
}

void searchstudent()
{
    FILE *fp;
    struct student info;
    int roll;
    printf("\t\t\tEnter the Roll Number to search: ");
    scanf("%d", &roll);

    fp = fopen("student_info.txt", "r");
    if (fp == NULL)
    {
        printf("\t\t\tNo records found.\n");
        return;
    }

    int found = 0;
    while (fread(&info, sizeof(struct student), 1, fp))
    {
        if (info.roll_no == roll)
        {
            printf("\n\tStudent Found!\n");
            printf("\n\tFirst Name: %s\n", info.first_name);
            printf("\tLast Name: %s\n", info.last_name);
            printf("\tRoll No: %d\n", info.roll_no);
            printf("\tClass: %s\n", info.class);
            printf("\tVillage: %s\n", info.vill);
            printf("\tPercentage: %.2f\n", info.per);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("\t\t\tStudent with Roll No %d not found.\n", roll);
    }
    fclose(fp);
}

void delete()
{
    FILE *fp, *temp;
    struct student info;
    int roll;
    printf("\t\t\tEnter the Roll Number to delete: ");
    scanf("%d", &roll);

    fp = fopen("student_info.txt", "r");
    if (fp == NULL)
    {
        printf("\t\t\tNo records found.\n");
        return;
    }

    temp = fopen("temp.txt", "w");
    if (temp == NULL)
    {
        printf("\t\t\tUnable to open temporary file.\n");
        fclose(fp);
        return;
    }

    int found = 0;
    while (fread(&info, sizeof(struct student), 1, fp))
    {
        if (info.roll_no != roll)
        {
            fwrite(&info, sizeof(struct student), 1, temp);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    if (found)
    {
        remove("student_info.txt");
        rename("temp.txt", "student_info.txt");
        printf("\t\t\tRecord deleted successfully.\n");
    }
    else
    {
        printf("\t\t\tStudent with Roll No %d not found.\n", roll);
    }
}

