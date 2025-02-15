//2loginsereen
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int menu();
void signup();
void login();
void forgot();
void change_password();
void delete_account();

struct dob
{
	int dd;
	int mm;
	int yyyy;
};
struct account
{
	char first_name[20];
	char last_name[20];
	char username[30];
	char phone[15];
	char gender;
	char pass1[20];
	struct dob d;
};


int main()
{
	while(1)
	{
		switch (menu())
		{
			case 1:
				signup();
			break;
			case 2:
				login();
			break;
			case 3:
				forgot();
			break;
			case 4:
				change_password();
			break;
		    case 5:
				delete_account();
			break; 
			case 6:
				exit(0);
			default:
				printf("Invalid choice\n");
			break;
		}
	}
	return 0;
}

int menu()
{
	int c;
	printf("\n*********************************MAIN MENU****************************\n");
	printf("1.SIGNUP\n");
	printf("2.LOGIN\n");
	printf("3.FORGOT PASSWORD OR USERNAME\n");
	printf("4.CHANGE PASSWORD\n");
	printf("5.DELETE ACCOUNT\n");
	printf("6.EXIT\n");
	printf("Enter Your Choice : ");
	scanf("%d",&c);
	return c;
	
}

void takepassword(char *pass)
{
    int i = 0;
    char ch;
    
    while (1)
    {
        ch = getch();  // Use getch() for non-echoed password input.
        
        // Enter key (13) to finish the input.
        if (ch == 13)  
        {
            pass[i] = '\0';  // Null-terminate the string.
            break;
        }
        // Backspace key (8) to delete the last character.
        else if (ch == 8)  
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");  // Move the cursor back, print a space, and move back again.
            }
        }
        // Ignore Tab or Space characters.
        else if (ch == 9 || ch == 32)
        {
            continue;
        }
        // For other characters, add to the password and show a *.
        else
        {
            pass[i++] = ch;
            printf("*");
        }
    }
    return ;
}

//signup
void signup()
{
	struct account u;
	
	
	char pass2[20];
	printf("\n***** CREATING NEW ACCOUNT *****\n");
	printf("Enter First Name : ");
	scanf("%s",u.first_name);
	printf("Enter Last Name : ");
	scanf("%s",u.last_name);
	printf("Enter your username: ");
	scanf("%s",u.username);
	printf("Enter Your Phone Number: ");
	scanf("%s",u.phone);
	fflush(stdin);
	printf("Enter Gender (M/F): ");
	scanf("%c",&u.gender);
	printf("Enter your DOB (DD/MM/YYYY): ");
	scanf("%d/%d/%d",&u.d.dd,&u.d.mm,&u.d.yyyy);
	
	printf("Enter password : \n");
	takepassword(u.pass1);

    
    printf("\nConfirm password : \n");
	scanf("%s",pass2);
	
	if(strcmp(u.pass1,pass2) !=0)
	{
		printf("Password do not Match. Account Creation Failed.\n");
		return;
	}
	else
	{
		printf("ACCOUNT CREATED SUCCESSFULLY\n");	

		
		FILE *fp=fopen("account.txt","w");
        if(fp == NULL)
        {
            printf("Error opening file.\n");
            return;
        }
	    fwrite(&u, sizeof(struct account), 1, fp);
		fclose(fp);
    }
}




//login

void login()
 {
    char user[30], log_pass[20];
    struct account u;
    FILE *fp = fopen("account.txt", "r");

    if (fp == NULL) 
	{
        printf("Error opening file.\n");
        return;
    }

    int found = 0;
    // Search for the account in the file
    
    while (fread(&u, sizeof(struct account), 1, fp)) 
	{
        printf("Enter Username: ");
        scanf("%s", user);

        if (strcmp(u.username, user) == 0) 
		{  // Username found
            while (1) 
			{
                printf("Enter password: ");
                takepassword(log_pass);

                if (strcmp(u.pass1, log_pass) == 0) 
				{  // Password correct
                    printf("\n*******************************\n");
                    printf("\nWELCOME || %s ||\n", u.username);
                    printf("\n*******************************\n");
                    printf("Your Details:\n");
                    printf("Username: %s\n", u.username);
                    printf("First name: %s\n", u.first_name);
                    printf("Last name: %s\n", u.last_name);
                    printf("Phone number: %s\n", u.phone);
                    printf("Gender: %c\n", u.gender);
                	printf("DOB : %d/%d/%d",u.d.dd,u.d.mm,u.d.yyyy);
                    printf("\n");
                    fclose(fp);
                    return;
                } 
				else 
				{
                    printf("\nIncorrect password.\n");
                    
                }
            }
        }
    }

    printf("Account not found.\n");
    fclose(fp);
}                            


//Forgot
void forgot() {
    struct account u;
    char choice;
    char username[20], password[20], phone[20];
    
    FILE *fp = fopen("account.txt", "r");
    if (fp == NULL) 
	{
        printf("Error opening file!\n");
        return;
    }

    // Read the first account from the file
    if (fread(&u, sizeof(struct account), 1, fp) != 1) 
	{
        printf("No account found in file!\n");
        fclose(fp);
        return;
    }

    printf("\n*********FORGET********\n");
    printf("\n1. Search by Username\n");
    printf("2. Search by Password\n");
    printf("3. Search by Phone No\n");
    printf("4. Main Menu\n");
    printf("Enter your Choice: ");
    scanf(" %c", &choice);  // Fix to use %c for reading a character input

    switch(choice)
	{
        case '1':
            printf("Enter Your Username: ");
            scanf("%s", username);
            
            if (strcmp(username, u.username) != 0) 
			{
                printf("USERNAME NOT FOUND!!\n");
            } 
			else
			 {
                printf("ACCOUNT FOUND:\n");
                printf("Username   : %s\n", u.username);
                printf("First Name : %s\n", u.first_name);
                printf("Last Name  : %s\n", u.last_name);
                printf("Phone No   : %s\n", u.phone);
                printf("Password   : %s\n", u.pass1);
            }
            break;
            
        case '2':
            printf("Enter Your Password: ");
            scanf("%s", password);
            
            if (strcmp(password, u.pass1) != 0) 
			{
                printf("ACCOUNT NOT FOUND!!\n");
            } 
			else 
			{
                printf("ACCOUNT FOUND:\n");
                printf("Username   : %s\n", u.username);
                printf("First Name : %s\n", u.first_name);
                printf("Last Name  : %s\n", u.last_name);
                printf("Phone No   : %s\n", u.phone);
                printf("Password   : %s\n", u.pass1);
            }
            break;
            
        case '3':
            printf("Enter Your Phone No: ");
            scanf("%s", phone);
            
            if (strcmp(phone, u.phone) != 0) 
			{
                printf("ACCOUNT NOT FOUND!!\n");
            }
			else 
			{
                printf("ACCOUNT FOUND:\n");
                printf("Username   : %s\n", u.username);
                printf("First Name : %s\n", u.first_name);
                printf("Last Name  : %s\n", u.last_name);
                printf("Phone No   : %s\n", u.phone);
                printf("Password   : %s\n", u.pass1);
            }
            break;
            
        case '4':
            return;

        default:
            printf("Invalid Choice\n");
            break;
    }

    fclose(fp);  // Close the file after operations
}



//password change
void change_password()
{
	struct account u;
	int num1,num2;
	srand(time(0));

start:
	num1=rand();
	printf("\nRandom number : %d\n", num1);
	
	printf("Enter above Number : ");
	scanf("%d",&num2);
	
	if(num1 == num2)
	{
		
		FILE *fp = fopen("account.txt","r+");
		fread(&u, sizeof(struct account),1 ,fp);
		
		printf("Enter New Password : \n");
		takepassword(u.pass1);
		
		char pass2[20];
		printf("\nConfirm Password : \n");
		scanf("%s",&pass2);
		
		if(strcmp(u.pass1,pass2))
		{
			printf("--------------------------------------");
			printf("\nPassword Do no Match. Try again.\n");
			printf("--------------------------------------\n");
			goto start;
		}
		else
		{
			fseek(fp, 0, SEEK_SET);
			fwrite(&u,sizeof(struct account),1,fp);
			printf("PASSWORD CHANGE SUCCESSFULLY\n");
			getch();
		}
		fclose(fp);
		
	}
	else
	{
		printf("Please input the correct number \n");
		goto start;
	}
}

//Delete account
void delete_account()
{
	FILE *fp=fopen("account.txt","r");
	
	char c = fgetc(fp);
	if(fp == NULL || fgetc(fp) == EOF)
	{
		printf("NO ACCONT TO DELETED\n");
		return;
	}
	else
	{
	printf("ARE TOU SURE[Y/N]");
	char ch = getche();//Get the user input without requiring Enter
	if(ch == 'Y' || ch == 'y')
	{
		fclose(fp);
		fp=fopen("account.txt","w"); //open the file for writing (delting account)
		fprintf(fp, " "); //Empty the file by writing a space(it can't be done by writing nothing too
		printf("\nACCOUNT DELETED SUCCESSFULLY\n");
		getch();
	}
	else if(ch == 'N' || ch == 'n')
	{
		printf("\nACCOUNT DELETED STOPPED\n");
		return ;
	}
	}

	
}


























