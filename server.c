#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h> //for read and write functions

void error(char *msg){
  perror(msg);
  exit(1);
}

int main(int argc, char *argv[]){

  int sockfd, newsockfd, portno, clilen;
  char buffer[256];
  struct sockaddr_in server_addr, cli_addr;
  int n;
  if(argc<2){
    fprintf(stderr, "ERROR, no port provided\n" );
    exit(1);
  }
  sockfd = socket(AF_INET, SOCK_STREAM,0);
  if(sockfd<0){
    error("ERROR opening socket");
  }
  else{
    printf("Port opened successfully %s \n",(argv[1]) );
  }
  bzero((char *)&server_addr, sizeof(server_addr));
  portno = atoi(argv[1]);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(portno);
  if(bind(sockfd,(struct sockaddr *) &server_addr,sizeof(server_addr))<0){
    error("ERROR on binding");
  }
  printf("Listening for incoming connections\n");
  listen(sockfd,5);
  clilen = sizeof(cli_addr);
  newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
  if(newsockfd < 0){
    error("ERROR on accept");
  }
  bzero(buffer,256);
  n = read(newsockfd,buffer,256);
  if(n<0){
    error("ERROR reading from socket");
  }
  printf("Here is the message: %s\n", buffer);
  n = write(newsockfd,"Server says: I got ur message.\n",30);
  if(n<0){
    error("ERROR writing to socket");
  }
  return 0;
}
