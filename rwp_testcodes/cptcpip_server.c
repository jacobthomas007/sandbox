#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

void errormessage(char *);
int main(int argc, char *argv[])
{
	int sock;
	int s_bind;
	int s_accept;
	int s_listen;
	unsigned int c_len;
	struct sockaddr_in s_sock;
	struct sockaddr_in c_sock;
	char buffer[100];
	char pass[5];
	int size_recv;
//	if(argc < 2){
//	printf("Enter the port number <SERVER port>\n");
//	exit(0);
//	}
	unsigned short serverPORT = 8000;
	s_sock.sin_family = AF_INET;
	s_sock.sin_addr.s_addr = INADDR_ANY;
	s_sock.sin_port = htons(serverPORT);
	memset(buffer,0,sizeof(buffer));
	memset(pass,0,sizeof(pass));
	strcpy(pass,"123");
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock < 0)
		errormessage("socket creation failed");
	s_bind = bind(sock, (struct sockaddr *)&s_sock, sizeof(s_sock));
	if(s_bind < 0)
		errormessage("bind failed");
	s_listen = listen(sock, 3);
	if(s_listen < 0)
		errormessage("listen failed");
	printf("Server initialization ready, waiting for password \n");

	while(1)
	{
		s_accept = accept(sock,(struct sockaddr *)&c_sock, &c_len);
		if(s_accept < 0)
			errormessage("accept failed");
		printf("Connected... verifing password...\n");
		size_recv = recv(s_accept,buffer,sizeof(buffer),0);
		if(size_recv < 0 )
		errormessage("recv failed");
		#if PACKET_DEBUG
		printf("DATA = %s  \n %d\n", buffer,(int)strlen(buffer));
		#endif
		if(strcmp(buffer,pass) == 0 )
		printf("Password success..\n");
		else
		errormessage("Password failed.. connection closed");
		#if PACKET_DEBUG	
		printf("DATA = %s  \n %d\n", buffer,(int)strlen(buffer));
		#endif
		memset(buffer,0,sizeof(buffer));
		recv(s_accept,buffer,sizeof(buffer),0);
		printf("DATA = %s  \n %d\n", buffer,(int)strlen(buffer));

	}
	return 0;
}
void errormessage(char *message)
{
	perror(message);
	exit(1);
}
