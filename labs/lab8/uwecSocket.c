#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
/*#include <sys/types.h>*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "uwecSocket.h"

//int main() {
int callServer(char* host, int portno){
  /* Socket pointer*/
  int sockfd;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    fprintf(stderr,"ERROR opening socket\n");
    exit(0);
  }

  /* port number*/
  /*int portno = 9601;*/

  /* server address structure*/
  struct sockaddr_in serv_addr;

  /*Set all the values in the server address to 0*/
  memset(&serv_addr, '0', sizeof(serv_addr)); 

  /* Setup the type of socket (internet vs filesystem)*/
  serv_addr.sin_family = AF_INET;

   /* Setup the port number
 *      htons - is host to network byte order
 *           network byte order is most sig byte first
 *                which might be host or might not be*/
  serv_addr.sin_port = htons(portno);


  /* Setup the server host address*/
  struct hostent *server;
  /*  server = gethostbyname("thing2.cs.uwec.edu");*/
  server = gethostbyname(host);
  if (server == NULL) {
    fprintf(stderr,"ERROR, no such host\n");
    exit(0);
  }
  memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);  /// dest, src, size

  /* Connect to the server*/
  if (connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    printf("ERROR connecting\n");
    exit(0);
  }

 return sockfd;
}


void writeInt(int x, int socket){
  /*char buffer[256];
  printf("Please enter the message: ");
  memset(&buffer, '\0', 256); 
  fgets(buffer,255,stdin);
*/
  printf("Writing %d\n", x);
  int n = write(socket,&x,sizeof(int));
  if (n < 0) {
    printf("ERROR writing to socket\n");
    exit(0);
  }
}

int readInt(int socket){
 // memset`(&buffer, '\0', 256);
  int x;
  int n = read(socket,&x,sizeof(int));
  //printf("Got %d\n", x);
  if (n < 0) {
    printf("ERROR reading from socket\n");
    exit(0);
  }
  //printf("%s\n",x);

  //close(sockfd);
  return x;
}

int setupServerSocket(int portno){
  /*Get a socket of the right type*/
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    printf("ERROR opening socket");
    exit(1);
  }

  /*port number*/
  //int portno = 9601;

  /*server address structure*/
  struct sockaddr_in serv_addr;

  /*Set all the values in the server address to 0*/
  memset(&serv_addr, '0', sizeof(serv_addr)); 

  /*Setup the type of socket (internet vs filesystem)*/
  serv_addr.sin_family = AF_INET;

  /*Basically the machine we are on...*/
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  /* Setup the port number*/
  /* htons - is host to network byte order*/
  /* network byte order is most sig bype first*/
  /*   which might be host or might not be*/
  serv_addr.sin_port = htons(portno);

  /* Bind the socket to the given port*/
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    printf("ERROR on binding\n");
    exit(1);
  }
return sockfd;
}


int serverSocketAccept(int serverSocket){
  /* set it up to listen*/
  listen(serverSocket,5);
  

  int newsockfd;
  struct sockaddr_in cli_addr;
  socklen_t clilen = sizeof(cli_addr);

  /* Wait for a call*/
 // printf("waiting for a call...\n");
  newsockfd = accept(serverSocket, (struct sockaddr *) &cli_addr, &clilen);
  //printf("connected\n");
  if (newsockfd < 0) {
    printf("ERROR on accept");
    exit(1);
  }
 return newsockfd;
}

/*
  char buffer[256];
  memset(&buffer, '\0', 256);
  //  bzero(buffer,256);
  int n = read(newsockfd,buffer,255);
  if (n < 0) {
    printf("ERROR reading from socket\n");
    exit(1);
  }

  printf("Here is the message: %s\n",buffer);
  n = write(newsockfd,"I got your message",18);
  if (n < 0) {
    printf("ERROR writing to socket\n");
    exit(1);
  }

  close(newsockfd);
  close(sockfd);
  return 0;
}

}*/
