#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#define red     "\x1b[31m"
#define green   "\x1b[32m"
#define yellow  "\x1b[33m"
#define blue    "\x1b[34m"
#define magent "\x1b[35m"
#define cyan    "\x1b[36m"
#define reset   "\x1b[0m"
#define bold_on  "%c[1m"
#define bold_off "%c[0m"
# define bold {printf(bold_on,27);}
# define bold_ {printf(bold_off,27);}
void prompt()
{
	char pwd[100];
	bold
        printf( red  "pizza_shell:" reset);
        getcwd(pwd,sizeof(pwd));
	bold
	printf(blue "%s" reset "$ ",pwd);
}
void main()
	{
	char command[100];
	char copy[100];
	char search[100]="./google ";
	char news[100]="./news ";
	while(1)
	{
	char *c;
	memset(command,0,sizeof(command));
	prompt();  //this prints the screen prompt
        gets(command);
	strcpy(copy,command); 
        if(strtok(copy," ")==NULL)
	puts("this is the pizza shell extension");
	else if(strcmp(strtok(copy," "),"stat")==0 || strcmp(strtok(copy," "),"stats")==0)
	system("screenfetch");
	else if(strcmp(strtok(copy," "),"exit")==0)
	exit(0);
	else if(strcmp(strtok(copy," "),"cd")==0)
	{
	strtok(command," ");
	if(chdir(strtok(NULL," "))==-1)
	printf("Directory not present");	
	}
	else if(strcmp(strtok(copy," "),"search")==0)
	{
	strtok(command," ");	
	strcpy(search+9,strtok(NULL,"'"));
//	puts(search);
	system(search);
	}
	else if(strcmp(strtok(copy," "),"news")==0)
	{
	strtok(command," ");
	strcpy(news+7,strtok(NULL,"'"));
//	puts(news);
	system(news);
	}
	else
	system(command);
	}
	}
