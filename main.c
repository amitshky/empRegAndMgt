#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ENTER 13 //newline->10     carriage return->13
#define BKSP 8
#define TAB 9
#define SPACE 32

int input(char); //input function to enter username or password
int read_username(int);
void read_password();
int check_username(int);
int check_password(int);
void delete_user(int*);
void modify(int*,int);
void file_extract(FILE*);
void message(FILE*,int,char);

typedef struct
{
	int day;
	int month;
	int year;
}Date;

typedef struct
{
	Date dob;
	char contact[20];
	float salary;
	char address[50];
	char degree[50];
 }Details;
 
typedef struct
{
	char st_username[100];
	char st_password[100];
	Details details;
 }User;

//Global variable declaration:
char user[100];  //user -> username input variable
char password[100];  //password -> password input variable
User u[100],u1; // u -> array to store all file data   // u1 -> temporary User variable to save data to the file
char adm_password[100]; //admin's password is "admin123"

int main()
{
	system ("color f0"); //white   //to see list, type garbage
	
	FILE *fuser = fopen("user.dat","ab+");
	FILE *fadmin = fopen("admin.dat","rb");
	FILE *mb = fopen("msgboard.txt","a+");
	FILE *m_ad = fopen("amsg.txt","a+");
	FILE *nb = fopen("notice.txt","a+");
	
	int i=0,n=0,index,pw_ck,un_ck,x; // index -> stores the index of correct username   pw_ck -> flag variable to check password   un_ck -> flag variable to check if username is repeated
	char opt, loop, c9;
	
	if (fuser == NULL || mb == NULL || m_ad == NULL || nb == NULL || fadmin == NULL)
	{
		printf ("Error opening file.");
		exit(1);
	}	
	else
	{
		do
		{
			for(i=0,n=0;fread (&u[i],sizeof(User),1,fuser) == 1;i++)	//copying all file data to struct   //feof() returns non-zero when it reaches EOF
			{
				n++;
				/*printf ("%d\t",n);
				printf ("%s\t",u[i].st_username);
				printf ("Password: %s\t",u[i].st_password);
				printf ("D.O.B.(DD/MM/YYYY): %d/%d/%d\t",u[i].details.dob.day,u[i].details.dob.month,u[i].details.dob.year);
				printf ("Contact number: %s\t",u[i].details.contact);
				printf ("Salary: %.3f\t",u[i].details.salary);
				printf ("Address: %s\t",u[i].details.address);
				printf ("Qualification: %s\n",u[i].details.degree);*/
			}
			//getch();
			system ("cls");
			
			rewind(fuser);
			
			printf ("\t\tEMPLOYEE REGISTRATION AND MANAGEMENT SYSTEM\n\n");
			
			if (n == 0) // n will be zero if there are no users
			{
				printf ("Press:\n");
				printf ("a) to Login as Admin\n");
				printf ("b) to Register an account to begin\n");
				fflush(stdin);
				c9 = getch();
				
				switch(c9)
				{
					case'a':
						system("cls");
						goto register_admin; //case 'c'
						break;
					
					case 'b':
						system("cls");
						goto register_user; //case 'a'
						break;
					
					default:
						printf ("\"Please enter a valid choice.\"\n");
				}
			}
			
			else
			{
				printf ("Press:\na) to Register an account\nb) to Login\nc) to Login as Admin\n");
				fflush(stdin);
				opt = getch();
				system ("cls");
				switch (opt)
				{
					case 'a': //registering
						register_user: //goto label
						printf ("\tREGISTER:\n\n");
						un_ck = read_username(n);
						printf ("\n");
					
						if (un_ck == 1)
						{
							read_password();	
							printf ("\nSuccessfully registered!!!\nPress any key to continue...");
							getch();
							system("cls");
							
							printf ("Fill up your details\n");
							printf ("Enter D.O.B.(DD/MM/YYYY):\n");
							scanf ("%d%d%d",&u1.details.dob.day,&u1.details.dob.month,&u1.details.dob.year);
							printf ("Enter Contact number: ");
							scanf ("%s",u1.details.contact);
							printf ("Enter Salary: ");
							scanf ("%f",&u1.details.salary);
							printf ("Enter Address: ");
							scanf ("%s",u1.details.address);
							printf ("Enter Qualification: ");
							scanf ("%s",u1.details.degree);
							fwrite(&u1,sizeof(User),1,fuser);
						}
						rewind(fuser);
						break;
						
					case 'b': //loging-in
						printf ("\tLOGIN:\n\n");
						index = check_username(n);
						printf ("\n");
						pw_ck = check_password(index);
						if (index >= 0 && pw_ck >= 0)
						{
							printf ("\nSuccessfully Logged-in!!!\nPress any key to continue...");
							getch();
							system("cls");
							
							do
							{
								printf ("\t%s\n\n",u[index].st_username);
								printf ("D.O.B.(DD/MM/YYYY): %d/%d/%d\n",u[index].details.dob.day,u[index].details.dob.month,u[index].details.dob.year);
								printf ("Contact number: %s\n",u[index].details.contact);
								printf ("Salary: %.3f\n",u[index].details.salary);
								printf ("Address: %s\n",u[index].details.address);
								printf ("Qualification: %s\n",u[index].details.degree);
								
								//Now we put the messaging stuff here 
								printf ("\nPress:\n");
								printf ("1) View message board\n");
								printf ("2) Write on message board\n");
								printf ("3) Message Admin\n");
								printf ("4) View Notice\n");
								printf ("5) Edit your account\n");
								printf ("6) Logout\n");
								fflush(stdin);
								c9 = getch();
								
								switch(c9)
								{
									case '1': //view message board
										system ("cls");
										printf ("Message Board:\n");
										file_extract(mb);
										getch();
										system("cls");
										break;
									
									case '2': //write on message board
										system("cls");
										printf("what doth thee wanteth to post?:\n ");
										message(mb,index,'u');
										printf("Your post has been added");
										getch();
										system("cls");
										break;
									
									case '3': //message admin
										system("cls");
										printf("What do you want to write?:\n ");
										message(m_ad,index,'u');
										printf("Your mail has been sent");
										getch();
										system("cls");
										break;
									
									case '4': //view notice
										system("cls");
										printf("Notice Board: \n");
										file_extract(nb);
										getch();
										system("cls");
										break;
									
									case '5': //modify account
										system("cls");
										modify(&n,index);
										system("cls");
										break;
									
									case '6': //logout
										break;
									
									default:
										printf ("\"Please enter a valid choice.\"\n");
										printf ("\nPress any key to continue...\n");
										getch();
										system("cls");
										break;
								}
							}while(c9 != '6');
						}
						else
							printf ("\nInvalid Username or Password!!!\n");
						break;
						
					case 'c': //login as admin
						register_admin: //goto label
						printf ("\tADMIN LOGIN:\n\n");
						fread(&adm_password,sizeof(adm_password),1,fadmin);
						printf ("Enter password:");
						x = input('p');
						if (strcmp(adm_password,password) == 0)
						{
							do
							{
								system("cls");
								printf ("\tWelcome! Admin\n\n");
								printf ("1) View Message Board\n");
								printf ("2) Write on Message Board\n");
								printf ("3) Write on Notice board\n");
								printf ("4) View Mail\n");
								printf ("5) View notice\n");
								printf ("6) Delete an Employee account\n");
								printf ("7) Logout\n");
								fflush(stdin);
								c9 = getch();
								
								switch(c9)
								{
									case '1': //view message board
										system ("cls");
										printf ("Message Board:\n");
										file_extract(mb);
										getch();
										system("cls");
										break;
									
									case '2': //write on message board
										system("cls");
										printf ("what doth thee wanteth to post?:\n ");
										message(mb,index,'a');
										printf ("Your post has been added");
										getch();
										system("cls");
										break;
									
									case '3': //write on notice board
										system("cls");
										printf ("what's the notice ?:\n ");
										message(nb,index,'a');
										printf ("The notice has been added");
										getch();
										system("cls");
										break;
									
									case '4': //view mail
										system("cls");
										printf ("Your Mail:\n");
										file_extract(m_ad);
										getch();
										system("cls");
										break;
										
									case '5': //view notice
										system("cls");
										printf ("Notice Board: \n");
										file_extract(nb);
										getch();
										system("cls");
										break;
										
									case '6': //delete an account
										system("cls");
										delete_user(&n);
										getch();
										system("cls");
										break;
									
									case '7': //logout
										break;
									
									default:
										printf ("\"Please enter a valid choice.\"\n");
										printf ("\nPress any key to continue...\n");
										getch();
										system("cls");
										break;
								}
							}while(c9 != '7');
						}
						else
							printf ("\nInvalid password!!!");
						break;
					
					default:
						printf ("\"Please enter a valid choice.\"\n");
				}
			}
			
			printf ("\nPress 'e' to exit or any other key to continue...\n");
			loop = getch();
		}while(loop != 'e');
	}
	
	fclose(fuser);
	fclose(mb);
	fclose(m_ad);
	fclose(nb);
	fclose(fadmin);
	return 0;
}

int input(char type)
{
	int i=0;
	char ch;
	while (1)
	{
		ch = getch();
		if (ch == ENTER)
		{
			if (type == 'u')
				user[i] = '\0'; // if not kept then it will add second string to first due to lack of "null" character 
			if (type == 'p')
				password[i] = '\0';
			break;
		}
		else if (ch == BKSP)
		{
			if (i>0)
			{
				i--;
				printf ("\b \b");
			}
		}
		else if (ch == TAB || ch == SPACE)
		{
			continue;
		}
		else
		{
			if (type == 'u')
			{
				user[i] = ch;
				printf ("%c",ch);
				i++;
			}
			if (type == 'p')
			{
				password[i] = ch;
				printf ("*");
				i++;
			}
		}
	}
	return i;
}

int read_username(int n)
{
	int i=0,flag=1,length,x; //length -> to determine the length of username
	printf ("Enter Username:");
	length = input('u');
	if(length < 4)
	{
		printf ("\nThe Username must be at least 4 characters long\n");
		x = read_username(n);
		return x;
	}
	for(i=0;i<n;i++)
	{
		if(strcmp(user,u[i].st_username) == 0) //checking if the username already exists
		{
			flag = 0;
			printf ("\nThis Username already exists!!!");
			break;
		}
		else
		{
			flag=1;
		}
	}
	if (flag == 1)
	{
		strcpy(u1.st_username,user);
		//printf ("\nUsername:%s\n",u1.st_username);
	}
	return flag;
}

int check_username(int n)
{
	int i=0,x;
	printf ("Enter Username:"); 
	x = input('u');
	for(i=0;i<n;i++)
	{
		if(strcmp(user,u[i].st_username) == 0)
			return i; // return vayo vaney function end huncha
	}
	return -1;
}

void read_password()
{
	int length; //length -> to determine the length of password
	printf ("Enter password:");
	length = input('p'); 
	if(length < 4)
	{
		printf ("\nThe Password must be at least 4 characters long\n");
		read_password();
	}
	else
		strcpy(u1.st_password,password);
	//printf ("\npassword:%s\n",password);
}

int check_password(int index)
{
	int i=0,x;
	printf ("Enter password:");
	x = input('p'); 

	if(strcmp(password,u[index].st_password) == 0)
	{
		//printf ("\n\ncorrect password:%s\nyour input:%s\n",u[index].st_password,password);
		return 1; // password is correct
	}
	//printf ("\n\ncorrect password:%s\nyour input:%s\n",u[index].st_password,password);
	return -1;
}

void delete_user(int *num)
{
	int index,i;
	FILE *fp = fopen("user.dat","wb+");    
	printf ("Deleting an account\n");
	index = check_username(*num);
	if (index >= 0)
	{
		for (i=0;i<*num;i++)
		{
			if(strcmp(u[i].st_username,u[index].st_username) != 0)
			{
				fwrite (&u[i],sizeof(User),1,fp);
			}
		}
		rewind(fp);
		for(i=0,*num=0;fread(&u[i],sizeof(User),1,fp) == 1;i++)	// we also have to make changes in the memory
		{
			*num=*num+1;
		}
		
		printf ("\nAccount deleted!!!\n");
	}
	else
	{
		printf ("\nThe Account doesn't exist!!!\n");
		for (i=0;i<*num;i++)  // because if the user types a wrong username the whole file would still be overwritten with nothing
		{
			fwrite (&u[i],sizeof(User),1,fp);
		}
	}
	fclose(fp);
}

void modify(int *num,int index_cmp)
{
	int index,i,pw_ck,x,flag=0;
	char ch;
	FILE *fp = fopen("user.dat","wb+");    
	printf ("To edit your account please enter your current Username and Password\n");
	index = check_username(*num);
	printf ("\n");
	pw_ck = check_password(index_cmp);
	if (index == index_cmp && pw_ck >= 0)
	{
		do
		{
			system("cls");
			printf ("What do you want to edit?:\n");
			printf ("a) Username\n");
			printf ("b) Password\n");
			printf ("c) D.O.B.\n");
			printf ("d) Contact number\n");
			printf ("e) Salary\n");
			printf ("f) Address\n");
			printf ("g) Qualification\n");
			printf ("h) Exit\n\n");
			ch = getch();
			switch(ch)
			{
				case 'a':
					x = read_username(*num);
					strcpy(u[index].st_username,u1.st_username);
					flag = 1;
					break;
				
				case 'b':
					read_password();
					strcpy(u[index].st_password,u1.st_password);
					flag = 1;
					break;
					
				case 'c':
					printf ("D.O.B.(DD/MM/YYYY):\n");
					scanf ("%d%d%d",&u[index].details.dob.day,&u[index].details.dob.month,&u[index].details.dob.year);
					flag = 1;
					break;
					
				case 'd':
					printf ("Contact number:");
					scanf ("%s",u[index].details.contact);
					flag = 1;
					break;
				
				case 'e':
					printf ("Salary:");
					scanf ("%f",&u[index].details.salary);
					flag = 1;
					break;
					
				case 'f':
					printf ("Address:");
					scanf ("%s",&u[index].details.address);
					flag = 1;
					break;
				
				case 'g':
					printf ("Qualification:");
					scanf ("%s",&u[index].details.degree);
					flag = 1;
					break;
				
				case 'h':
					if(flag == 1)// flag 1 thiena vaney ani change na gari gako vaie  "account modified" deykhau thio 
						printf ("\nAccount has been modified!!!\n");
					break;
				
				default:
					printf ("\"Please enter a valid choice.\"\n");
			}
			printf ("\nPress any key to continue...\n");
			getch();
		}while(ch != 'h');
		rewind(fp);
		for (i=0;i<*num;i++) 
		{
			fwrite (&u[i],sizeof(User),1,fp);
		}
	}
	else
	{
		printf ("\nInvalid Username or Password!!!\n");
		for (i=0;i<*num;i++)  // because if the user types a wrong username the whole file would be overwritten with nothing
		{
			fwrite (&u[i],sizeof(User),1,fp);
		}
	}
	fclose(fp);
}

void file_extract(FILE *fp)
{
	char ch;
	rewind(fp);
	while(1)
	{
		ch = fgetc(fp);
		if(ch == EOF)
			break;
		printf ("%c",ch);
	}
}

void message(FILE *fp,int index,char type)
{
	char msgb[250];
	rewind(fp);
	fflush(stdin);
	gets(msgb);
	
	if(type == 'u')
		fprintf(fp,"From: %s\n %s\n\n",u[index].st_username,msgb);
	
	if(type == 'a')
		fprintf(fp,"From: Admin\n %s\n\n",msgb);
}

