#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	char adm_password[100];
	FILE * admin = fopen("admin.dat","w");
	
	printf ("password:");
	scanf ("%s",adm_password);
	
	fwrite (&adm_password,sizeof(adm_password),1,admin);
	
	getch();
	return 0;
}
