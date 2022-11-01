#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <unistd.h>
#include <poll.h>
#include <ctype.h>
#include <stdlib.h>
#include <crypt.h>

#define USERNAME "SEED_Security_Student"
#define PASSWORD "rvrs3Eng1neeR"
#define PORT 49575 

#ifdef HARD
// MD5 hash generated using md5pass utility
#define MD5HASH "$1$tU01.NZp$vkL.aRuu6fU2ZLRU5esy0/"
int verifyMD5Hash(const char* pass)
{
   return strcmp(crypt(pass, MD5HASH), MD5HASH) == 0;
}
#endif

void validateCredentials()
{
   const unsigned int BUF_SIZE = 1000;
   
   char inUser[BUF_SIZE];
   char* inPass;
   bool validCredentials = false;
  
   while (!validCredentials)
   {
      memset(inUser, 0, sizeof(inUser));
      
      printf("Username: ");
      fgets(inUser, BUF_SIZE, stdin);
      inUser[strlen(inUser) - 1] = '\0'; // Remove newline character

      inPass = getpass("Password: ");
      if (inPass == NULL)
      {
         #if DEBUG
         perror("GETPASS FAILED");
         #endif
         continue;
      }
      else
      {
         #ifdef HARD
         validCredentials = (strcmp(USERNAME, inUser) == 0 &&
                             verifyMD5Hash(inPass) == 1);
         #else
         validCredentials = (strcmp(USERNAME, inUser) == 0 &&
                             strcmp(PASSWORD, inPass) == 0);
         #endif
         
         if (!validCredentials)
         {
            printf("INVALID CREDENTIALS, TRY AGAIN...\n");
         }
      }
   }
}

int socketRead(int sock, char* outBuf, int bufSize)
{
   if (sock > 0 && outBuf != NULL && bufSize > 0)
   {
      const int timeout = 10; // milliseconds
      struct pollfd fds;
      fds.fd = sock;
      fds.events = POLLIN;
      
      int ready = poll(&fds, 1, timeout);
      if (ready < 0)
      {
         #if DEBUG
         perror("POLL FAILED");
         #endif
      }
      else if (ready && (fds.revents & POLLIN))
      {
         char tmpBuf[bufSize];
         memset(tmpBuf, 0, bufSize);
         ssize_t Bytes = recv(sock, tmpBuf, bufSize, 0);
         if (Bytes < 0)
         {
            #if DEBUG
            perror("RECV FAILED");
            #endif
         }
         else
         {
            memcpy(outBuf, tmpBuf, bufSize);
            return Bytes;
         }
      }
   }
   return 0;
}

int socketWrite(int sock, char* inBuf, int bufSize)
{
   if (sock > 0 && inBuf != NULL && bufSize > 0)
   {
      const int timeout = 10; // milliseconds
      struct pollfd fds;
      fds.fd = sock;
      fds.events = POLLOUT;
      
      int ready = poll(&fds, 1, timeout);
      if (ready < 0)
      {
         #if DEBUG
         perror("POLL FAILED");
         #endif
      }
      else if (ready && (fds.revents & POLLOUT))
      {
         ssize_t Bytes = send(sock, inBuf, bufSize, 0);
         if (Bytes < 0)
         {
            #if DEBUG
            perror("SEND FAILED");
            #endif
         }
         else
         {
            return Bytes;
         }
      }
   }
   return 0;
}

int socketPeerOpen(int sock)
{
   if (sock > 0)
   {
      char buf[1];
      if (recv(sock, buf, 1, MSG_PEEK) > 0)
      {
         return 1;
      } 
   }
   return 0;
}

void socketInteract(int sock)
{
   const int bufSize = 5000;
   char buf[bufSize];

   while (socketPeerOpen(sock))
   {
      while (socketRead(sock, buf, bufSize) > 0)
      {
         fputs(buf, stdout);
      }  
      
      memset(buf, 0, bufSize);
      fgets(buf, bufSize, stdin);
      socketWrite(sock, buf, strlen(buf));
   }
}

int main(int argc, char* argv[])
{
   struct sockaddr_in serverAddress;
   int sockfd;
   
   if (argc != 2)
   {
      printf("USAGE: %s <IP_addr>\n", argv[0]);
      return 1;
   }

   serverAddress.sin_family = AF_INET;
   serverAddress.sin_port = htons(PORT);

   if (inet_aton(argv[1], &serverAddress.sin_addr) == 0)
   {
      #if DEBUG
      printf("INVALID ADDRESS!\n");
      #endif
      return 1;
   }

   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0)
   {
      #if DEBUG
      perror("SOCKET CREATION FAILED");
      #endif
      return 1;
   }
   
   validateCredentials(); // Check credentials before connecting to remote host

   if (connect(sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
   {
      perror("SOCKET CONNECTION FAILED");
      return 1;
   }

   socketInteract(sockfd);

   if (close(sockfd) < 0)
   {
      #if DEBUG
      perror("SOCKET CLOSING FAILED");
      #endif
      return 1;
   }

   return 0;
}

