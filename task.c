#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printHelp();

void printMainMenu();

void printUserModMenu();

int addUser();

int delUser();

int addGroup();

int delGroup();

int seeDetails(char* user);

int addUserToGroup(char* user);

int modUser();

int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		int exit = 0;
		while(!exit)
		{
			int op = 0;
			while (op < 1 || op > 6)
			{
				printf("Select Option:\n");
				printMainMenu();
				scanf("%d", &op);

				getchar();
			} 
			switch (op)
			{
				case 1:
					if(addUser())
						printf("\n\nUser Added Successfully!\n\n");
					else
						printf("\n\nCouldn't Add User!\n\n");
					break;
				case 2:
					if(delUser())
						printf("\n\nUser Deleted Successfully!\n\n");
					else
						printf("\n\nCouldn't Delete User!\n\n");
					break;
				case 3:
					modUser();
					break;
				case 4:
					if(addGroup())
						printf("\n\nGroup Added Successfully!\n\n");
					else
						printf("\n\nCouldn't Add Group!\n\n");
					break;
				case 5:
					if(delGroup())
						printf("\n\nGroup Deleted Successfully!\n\n");
					else
						printf("\n\nCouldn't Delete Group!\n\n");
					break;
				case 6:
					exit = 1;
					break;
			}
		}
	}
	else if(argc == 2 && (strcmp(argv[1], "--help") || strcmp(argv[1], "-h")))
		printHelp();
	else
		printHelp();
}

void printHelp()
{
	printf("\nUsage: task [OPTIONS]\nGeneral Options:\n\n--help, -h:	display help for command.\n");
	return;
}

void printMainMenu()
{
	printf("1) Add User\n");
	printf("2) Delete User\n");
	printf("3) Modify User\n");
	printf("4) Add Group\n");
	printf("5) Delete Group\n");
	printf("6) Exit\n");
	return;
}

void printUserModMenu()
{
	printf("1) See Account Details\n");
	printf("2) Set Account Expiration Date\n");
	printf("3) Add User To Group\n");
	printf("4) Change User Name\n");
	printf("5) Lock User\n");
	printf("6) Unlock User\n");
	printf("7) Set Password Expiration Date\n");
	printf("8) Remove Password Expiration Date\n");
	printf("9) Exit\n");
	return;
}

int addUser()
{
	char user[50];

	printf("Enter name of user to be added: ");
	scanf("%s", user);
	
	getchar();

	char cmd[100] = "sudo useradd -m ";
	strcat(cmd, user);
	int userFail = system(cmd);
	
	if(userFail)
	{
		printf("Adding user failed!\n");
		return 0;
	}

	strcpy(cmd, "sudo passwd ");
	strcat(cmd, user);

	int pwdFail = system(cmd);

	if(pwdFail)
	{
		strcpy(cmd, "sudo userdel -r ");
		strcat(cmd, user);
		system(cmd);
	}

	return !pwdFail;
}

int delUser()
{
	char user[50];

	printf("Enter name of user to be deleted: ");
	scanf("%s", user);
	
	getchar();

	char cmd[100] = "sudo userdel -r ";
	strcat(cmd, user);
	int userFail = system(cmd);
	
	if(userFail)
	{
		printf("Deleting user failed!\n");
		return 0;
	}

	return !userFail;
}

int addGroup()
{
	char group[50];

	printf("Enter name of group to be added: ");
	scanf("%s", group);
	
	getchar();

	char cmd[100] = "sudo groupadd ";
	strcat(cmd, group);
	int groupFail = system(cmd);
	
	if(groupFail)
	{
		printf("Adding group failed!\n");
		return 0;
	}

	return !groupFail;
}

int delGroup()
{
	char group[50];

	printf("Enter name of group to be deleted: ");
	scanf("%s", group);
	
	getchar();

	char cmd[100] = "sudo groupdel ";
	strcat(cmd, group);
	int groupFail = system(cmd);
	
	if(groupFail)
	{
		printf("Deleting group failed!\n");
		return 0;
	}

	return !groupFail;
}

int seeDetails(char* user)
{
	char cmd[100] = "sudo chage -l ";
	strcat(cmd, user);
	int detailsFail = system(cmd);
	return !detailsFail;
}

int setAccountExpiration(char* user)
{
	char cmd[100] = "sudo chage -E ";

	char date[100];
	printf("Enter Expiration Date For Account: ");
	scanf("%s", date);
	getchar();

	strcat(cmd, date);
	strcat(cmd, " ");
	strcat(cmd, user);
	int detailsFail = system(cmd);
	return !detailsFail;
}

int addUserToGroup(char* user)
{
	char group[50];

	printf("Enter name of new user group: ");
	scanf("%s", group);
	
	getchar();

	char cmd[100] = "sudo usermod -aG ";
	strcat(cmd, group);
	strcat(cmd, " ");
	strcat(cmd, user);

	int groupFail = system(cmd);
	
	if(groupFail)
	{
		printf("Adding user to group failed!\n");
		return 0;
	}

	return !groupFail;
}

int changeName(char* user)
{
	char newName[100];
	printf("Enter new user name: ");
	scanf("%s", newName);
	
	getchar();

	char cmd[100] = "sudo usermod -l ";
	strcat(cmd, newName);
	strcat(cmd, " ");
	strcat(cmd, user);
	int userFail = system(cmd);

	if(!userFail)
		strcpy(user, newName);

	return !userFail;
}

int lockUser(char* user)
{
	char cmd[100] = "sudo usermod -L -e 1 ";
	strcat(cmd, user);
	int userFail = system(cmd);

	return !userFail;
}

int unlockUser(char* user)
{
	char cmd[100] = "sudo usermod -U ";
	strcat(cmd, user);
	int userFail = system(cmd);

	return !userFail;
}

int setPasswordExpiration(char* user)
{
	char cmd[100] = "sudo chage -M ";

	char days[100];
	printf("Enter Number of Days Till Expiration: ");
	scanf("%s", days);
	getchar();

	strcat(cmd, days);
	strcat(cmd, " ");
	strcat(cmd, user);
	int expireFail = system(cmd);
	return !expireFail;
}

int unsetPasswordExpiration(char* user)
{
	char cmd[100] = "sudo chage -M -1 ";

	strcat(cmd, user);
	int expireFail = system(cmd);
	return !expireFail;
}

int modUser()
{
	char user[50];

	printf("Enter name of user to be modified: ");
	scanf("%s", user);

	getchar();

	int exit = 0;
	while(!exit)
	{
		int op = 0;
		while (op < 1 || op > 9)
		{
			printf("Select Option:\n");
			printUserModMenu();
			scanf("%d", &op);

			getchar();
		} 
		switch (op)
		{
			case 1:
				if(!seeDetails(user))
					printf("\n\nCouldn't Show User Details\n\n");
				break;
			case 2:
				if(setAccountExpiration(user))
					printf("\n\nExpiration Date Modified Successfully!\n\n");
				else
					printf("\n\nCouldn't Modify User Expiration Date!\n\n");
				break;
			case 3:
				if(addUserToGroup(user))
					printf("\n\nUser Added To Group Successfully!\n\n");
				else
					printf("\n\nCouldn't Add User To Group!\n\n");
				break;
			case 4:
				if(changeName(user))
					printf("\n\nUser Name Changed Successfully!\n\n");
				else
					printf("\n\nCouldn't Change User Name!\n\n");
				break;
			case 5:
				if(lockUser(user))
					printf("\n\nUser Locked Successfully!\n\n");
				else
					printf("\n\nCouldn't Lock User!\n\n");
				break;
			case 6:
				if(unlockUser(user))
					printf("\n\nUser Unlocked Successfully!\n\n");
				else
					printf("\n\nCouldn't Unlock User!\n\n");
				break;
			case 7:
				if(setPasswordExpiration(user))
					printf("\n\nPassword Expiration Set Successfully!\n\n");
				else
					printf("\n\nCouldn't Set Password Expiration!\n\n");
				break;
			case 8:
				if(unsetPasswordExpiration(user))
					printf("\n\nPassword Expiration Removed Successfully!\n\n");
				else
					printf("\n\nCouldn't Remove Password Expiration!\n\n");
				break;
			case 9:
				exit = 1;
				break;
		}
	}
	return 0;
}
