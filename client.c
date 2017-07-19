#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h> //for exit system call
#include<unistd.h> //for read and write functions

void error(char *msg){
  perror(msg);
  exit(0);
}

int main(int argc, char *argv[])
{
  int sockfd, portno ,n;
  char buffer[256];
  struct sockaddr_in server_addr;
  struct hostent *server;

  if(argc<3){
    fprintf(stderr,"usage %s hostname port\n", argv[0] );
    exit(0);
  }
  portno = atoi(argv[2]);
  sockfd = socket(AF_INET,SOCK_STREAM,0);
  if(sockfd<0){
    error("Error opening socket");
  }
  else{
    printf("Socket opened successfully\n");
  }

  server = gethostbyname(argv[1]);
  if(server == NULL){
    fprintf(stderr, "ERROR no such host\n" );
    exit(0);
  }
  bzero((char *)&server_addr,sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr,server->h_length);
  server_addr.sin_port = htons(portno);
  if(connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr))<0){
    error("ERROR connecting");
  }
  printf("Please enter the message\n" );
  bzero(buffer,256);
  fgets(buffer,256,stdin);
  n = write(sockfd,buffer,strlen(buffer));
  if(n<0){
    error("ERROR writing to socket");
  }
  bzero(buffer,256);
  n = read(sockfd,buffer,255);
  if(n<0){
    error("ERROR reading from socket");
  }
  printf("%s\n",buffer);
  return 0;
}
