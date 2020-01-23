#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<netdb.h> 
#include<ctype.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<signal.h>
#include<linux/input.h>
# define time 100000
short int flip=0;
short int tflag=0;
short int fd=0,fd1=0;
void handle()
{
close(fd);
close(fd1);
//close(fd2);
tflag=1;
sleep(1);
exit(0);
}

short int lock_flag=0;


void *motion_ps4()
{

fd1=open("/dev/input/event17",O_RDWR);
struct input_event ev;
while(1)
{
if(tflag==1)
pthread_exit(NULL);
read(fd1,&ev,sizeof(ev));
if(ev.type==3 && (ev.code ==0))
{
if(ev.value<-7000)
system("sudo ./press.out 115");
else if(ev.value>5000)
system("sudo ./press.out 114");
usleep(time);
//puts("nice");
}
else if(ev.type==3 && ev.code==2)
{
if(ev.value<-7000)
system("sudo ./bright_down.out");
else if(ev.value>5000)
system("sudo ./bright_up.out");
usleep(time);
}
}
}
void *read_ps4()
{
fd=open("/dev/input/event18",O_RDWR);
struct input_event ev;
short int prec=0;
short int bflag=0;
while(1)
{
if(tflag==1)
pthread_exit(NULL);
read(fd,&ev,sizeof(ev));
if((ev.type==1)||((ev.type==3)&&(ev.code==16 || ev.code==17 || ev.code==1 || ev.code==4)))
if(ev.value==1 || ev.value==-1)
{
switch(ev.code)
{
case 317:
        system("sudo ./press.out 113");
	break;
case 318:
	break;
case 307:
	
                system("sudo ./press.out 99");
	       break;
case 308:
	        system("sudo ./press.out 28");

               break;
case 304:
	        system("sudo ./press.out 57");

               break;
case 305:
	        system("sudo ./press.out 14");

               break;
case 310:
	      if(prec==0)
	        system("sudo ./press.out 114");
	      else
		 system("sudo ./bright_up.out");


               break;
case 311:
               if(prec==0)
	        system("sudo ./press.out 115");
	       else
		  system("sudo ./bright_down.out");
	       

               break;
case 312:
	        if(lock_flag==0)
	        {
		system("sudo ./lock_screen.out");
                lock_flag=1;
		}

		else if(lock_flag==1)
		{
		system("sudo ./unlock_screen.sh");
		lock_flag=0;
                }
               break;
case 313:
	       // system("espeak 'switching'");
		if(flip==0)
		flip=1;
		else
		flip=0;
		break;
case 17:
	if(flip==0)
	{
	     if(ev.value==-1)
	  system("sudo ./press.out 103");
	   else
           system("sudo ./press.out 108");
	}
	else
	{
	if(ev.value==-1)
	system("sudo ./zoom.out");
	else
	system("sudo ./zoomout.out");
	}

               break;
case 16:
	     if(ev.value==-1)
	system("sudo ./press.out 105");
	     else
        system("sudo ./press.out 106");
               break;
case 314:
	 if(flip==1)
        system("./mail.sh");
	 else
        system("./mailsend.sh");
               break;
case 315:
	 if(flip==0)
	 system("xdotool click 3");
	 else
	 system("./lol.sh");
               break;
case 316:
	       
	      system("./press.out 125");
               break;	       
}
}
else if(ev.value>140 && ev.code==1)
{
system("sudo ./press.out 114");
usleep(time);
prec=0;
}
else if(ev.value<120 && ev.code==1)
{
system("sudo ./press.out 115");
usleep(time);
prec=0;
}
else if(ev.value>180 && ev.code==4)
{
system("sudo ./bright_up.out");
usleep(time);
prec=1;
}
else if(ev.value<120 && ev.code==4)
{
system("sudo ./bright_down.out");
usleep(time);
prec=1;
}
}
}


void *read_file(void *str)
{
int fd=open((char *)str,O_RDONLY);
if(fd==-1)
{
FILE *out = popen("./fb1", "w");
fwrite("file does not exist",1,20,out);
fflush(out);
pclose(out);
}
else
{
close(fd);
char *st="./fb1";
char stat[50]="cat                      | ./fb1";
strcpy(stat+4,(char *)str);
strcpy(stat+25,st);
puts(stat);
//system(stat);
}
}




void voice(char *str)
{
FILE *out = popen("./fb1", "w");
fwrite(str,1,strlen(str),out);
fflush(out);
pclose(out);
}
void main(int argc,char **argv)
{
	signal(SIGQUIT,handle);
        pthread_t ps4,psm;
	pthread_create(&ps4,NULL,(void *)read_ps4,NULL);
	pthread_create(&psm,NULL,(void *)motion_ps4,NULL);
	
	pthread_t l;
//	pthread_create(&l,NULL,read_file,"lol.txt");
//	pthread_detach(l);
//	voice("Welcome to the linux control interface");
	char mousemove1[20];short mm1=0;
	char mousemove2[20];short mm2=0;
	char bflag='0';
	char bright[50]="xrandr --output eDP-1-1 --brightness 0.9";
	int sockid,port;
	char *data;
	struct sockaddr_in server,client;
	sockid = socket(AF_INET,SOCK_STREAM,0);

	socklen_t size = (socklen_t)sizeof(server);
	client.sin_family = AF_INET;
	client.sin_port = htons(atoi(argv[1]));
	client.sin_addr.s_addr = INADDR_ANY;
	system("ifconfig | grep 'inet 1' ");
	int choice;
	char buffer[500];
	char statis;
	int j=0;
	char com[50];

        bind(sockid,(struct sockaddr *)&client,sizeof(client));
	listen(sockid,10000);
		 
	
               while(1)
	       {
	       short int rel=0;
	       char request[50];
	       char search[100]="./google.out ";
	       char mousemove[100]="xdotool mousemove                                           ";
               memset(mousemove1,0,20);
	       memset(mousemove2,0,20);
	       mm1=0;
	       mm2=0;
                int new = accept(sockid,NULL,0);
		
		recv(new,buffer,150,0);
		puts(buffer);
		int z = 0;
		while(buffer[z]!='$')
			z++;

		if(buffer[z+1]=='$')
	        {
		if(buffer[z+2]=='L')
		{
	//	system("./mail_lock.sh");
	        if(lock_flag==0)
		{
		system("sudo ./lock_screen.out");
		lock_flag=1;
		}
//		voice("screen locked");

		}
		else if (buffer[z+2]=='U')
		{
		if(lock_flag==1)
		{
		system("sudo ./unlock_screen.sh");
		lock_flag=0;
		}
          //      system("./mail_unlock.sh");
	//	system("sudo ./unlock_screen.sh");
//		voice("screen unlocked");

		}
		else if (buffer[z+2]=='A')
		{
		system("sudo ./press.out 115");
		system("sudo ./press.out 115");
		system("sudo ./press.out 115");
                system("sudo ./press.out 115");
		}
		else if(buffer[z+2]=='S')
		{
		system("sudo ./press.out 114");
		system("sudo ./press.out 114");
		system("sudo ./press.out 114");
                system("sudo ./press.out 114");
		}
		else if(buffer[z+2]=='$')
		{
		rel=z+3;
		while(buffer[rel++]!='$');
		buffer[rel-1]='\0';
                strcpy(search + strlen(search) , buffer+z+12);
		puts(search);
		system(search);
		}
		else
		{
		z+=2;
		while(mousemove1[mm1++]=buffer[z++],buffer[z]!=',');
		z++;
		while(mousemove2[mm2++]=buffer[z++],buffer[z]!='$');
		mousemove1[mm1]='\0';
		mousemove2[mm2]='\0';
		short mm1len=strlen(mousemove1);
		short mm2len=strlen(mousemove2);
		for(int i=18;i<(18+mm1len);i++)
		mousemove[i]=mousemove1[i-18];
	        for(int i=(20+mm1len);i<=(19+mm1len+mm2len);i++)
		{
                mousemove[i]=mousemove2[i-20-mm1len];
              //  printf("%c",mousemove[i]);
		} 
		

	//	puts(mousemove);
	system(mousemove);
		}
		}


		else	if((buffer[z+1]=='%') && (buffer[z+2]=='5'))
		{
//			puts("enter pressed");
			system("sudo ./press.out 28");
		}

		else if((buffer[z+1]=='~')||(buffer[z+1]<58)||(buffer[z+1]=='%')||(buffer[z+1]=='`')) 
                switch(buffer[z+1])
		{
			case '0':
				system("sudo ./press.out 108");
				
			      				break;
			case '1':
			        if(buffer[z+2]=='$')
				system("sudo ./press.out 103");
				else
				switch(buffer[z+2])
				{
				case '1':
                                system("sudo ./switch_tab.out");
				break;
				case '2':
                                system("sudo ./delete_tab.out");
                                break;
				 case '3':
                               system("./new_tab.out");
                                break;
				 case '4':
				system("./info_tab.out");

                                break;
				 case '5':
                                system("./save_tab.out");
                                break;




				}
				break;
				
			case '2':
				system("sudo ./press.out 105");
	//			send(sockid,&message,strlen(message),0);
				
				break;
			case '3':
				system("sudo ./press.out 106");
	//			send(sockid,&message,strlen(message),0);
				
				break;
			case ')':
				system("sudo xdotool click 1");
	//			send(sockid,&message,strlen(message),0);
				
				break;
			case '(':
				system("sudo xdotool click 3");
				break;
			case '-':
	            	/*	if(bflag!='0')
				{
				bflag--;
				bright[strlen(bright)-1]=bflag;
				bright[strlen(bright)]='\0';
				}
				system(bright);
			//	puts(bright);
			//	*/
			        system("sudo ./bright_up.out");
				break;
			case '~':
			/*	 if(bflag!='9')
                                {
                                bflag++;
				bright[strlen(bright)-1]=bflag;
				bright[strlen(bright)]='\0';
                                }
			//	puts(bright);
                                system(bright);
				*/
				system("sudo ./bright_down.out");
				break;
			
			case '%':
				system("sudo ./press.out 14");
				break;
			case '6':
				system("sudo ./terminal.out");
				break;
			case '+':
			       	system("sudo ./home.out");
			       break;
                         case '7':

                                                                                         system("xdotool mousemove_relative -- 0 -10");


                                                                                        break;
                                                                                 case '8':
                                                                                 system("xdotool mousemove_relative -- -10 0");
                                     
                                            break;
                                                                                 case '9':
                                                                                 system("xdotool mousemove_relative 10 0");
                                                                                 break;
                                                                                case '5':
                                                                                system("xdotool mousemove_relative 0 10");
										
			       break;
		}

	       else{
		            
		         //       char com[50];
		              
		                while(buffer[z+1]!='$')
		                {
					char com[50];
					int j=0;
			
					com[j++] = buffer[++z];
 	                char sys[50] = "sudo ./sim_press.out      ";
                      com[j]='\0';
  	               //  strcat(sys,&com[j-1]);
			 if(com[j-1]=='%')
			 {
			 strcat(sys," _");
			 z+=2;
			 system(sys);
			 }
			 else
			 {
		         strcat(sys,&com[j-1]);
		//	 puts(sys);
                         system(sys);
			 }
	                 }
			
		system("sudo ./sim_press.out ^");	
	       }	

			
		}
                
	pthread_join(ps4,NULL);
	pthread_join(psm,NULL);
//	close(sockid);	
	}
	



