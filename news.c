#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<pthread.h>
#include <openssl/ssl.h>
#include<fcntl.h>




int main(int argc, char** argv)
{
	struct sockaddr_in servaddr;
	struct hostent *hp;
	int sock_id;

  char request[300] = "GET /rss/search?q=";
  char request1[]="&hl=en-IN&gl=IN&ceid=IN:en  HTTP/1.1\r\n"
                "Host: news.google.com \r\n"
                "User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:61.0) Gecko/20100101 Firefox/61.0 \r\n"
                "\r\n";
         
  char re[40];
  short int ln=0;
  short int rgl=0;
  while(ln<(strlen(argv[1])))
  {
  if(argv[1][rgl]==' ')
  {
   re[ln++]='+';
   rgl+=1;
  }
  else
  re[ln++]=argv[1][rgl++];
  }
  re[ln]='\0';
  strcpy(request+strlen(request),re);
  strcpy(request +strlen(request),request1);
 // puts(request);
        sock_id = socket(AF_INET,SOCK_STREAM,0);
	
	memset(&servaddr,0,sizeof(servaddr));
	
	
	hp = gethostbyname("news.google.com");
		
	memcpy((char *)&servaddr.sin_addr.s_addr, (char *)hp->h_addr, hp->h_length);
	
	
	servaddr.sin_port = htons(443);
	servaddr.sin_family = AF_INET;



SSL_load_error_strings ();
SSL_library_init ();
SSL_CTX *ssl = SSL_CTX_new (SSLv23_client_method ());


SSL *sslcon = SSL_new(ssl);
SSL_set_fd(sslcon, sock_id);
	
	
	connect(sock_id, (struct sockaddr *)&servaddr, sizeof(servaddr));
	
	
SSL_connect(sslcon);
int visit=0;	
SSL_write(sslcon,request,sizeof(request));
int val=0;
	int stat = 0;
	char buf;
	int count =0;
	int f=0;
//	char *str="data-currency-value";
	while(1)
	{
	short int count=100;
	SSL_read(sslcon,&buf,1);
//	putchar(buf);
if(buf=='<' && SSL_read(sslcon,&buf,1) && buf=='t' && SSL_read(sslcon,&buf,1) && buf=='i' &&SSL_read(sslcon,&buf,1) && buf=='t' &&SSL_read(sslcon,&buf,1) && buf=='l' &&SSL_read(sslcon,&buf,1) && buf=='e' &&SSL_read(sslcon,&buf,1) && buf=='>')
{
printf("\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
printf("\n");
while(SSL_read(sslcon,&buf,1),putchar(buf),buf!='<');
printf("\n");
//printf("\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
}

else if(buf=='h' && SSL_read(sslcon,&buf,1) && buf=='r' && SSL_read(sslcon,&buf,1) && buf=='e' &&SSL_read(sslcon,&buf,1) && buf=='f' &&SSL_read(sslcon,&buf,1) && buf=='=' &&SSL_read(sslcon,&buf,1) && buf=='"')
{
printf("\n");
while(SSL_read(sslcon,&buf,1),putchar(buf),buf!='"');	
printf("\n");
//printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
printf("\n");
printf("\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------")
;
if(visit==50)
exit(0);
visit++;
}	
   else	if(buf=='>' &&   SSL_read(sslcon,&buf,1) && buf=='>' && SSL_read(sslcon,&buf,1) && buf=='>' &&   SSL_read(sslcon,&buf,1) && buf=='>' &&  SSL_read(sslcon,&buf,1) && buf=='>' &&  SSL_read(sslcon,&buf,1) && buf=='>' && SSL_read(sslcon,&buf,1) && buf=='>' && SSL_read(sslcon,&buf,1) && buf=='>' && SSL_read(sslcon,&buf,1) && buf=='>')
	return 0;
	}

	return 0;


}
