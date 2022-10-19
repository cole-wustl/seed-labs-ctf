#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <unistd.h>
#include <poll.h>

#ifndef USER
#define USER "user"
#endif

#ifndef PASS
#define PASS "pass"
#endif

#ifndef PORT
#define PORT 49575 
#endif

#ifndef PRINT_ERRORS
#define PRINT_ERRORS 1
#endif

void validateCredentials()
{
   const unsigned int BUF_SIZE = 1024;
   const char* _user = USER;
   const char* _pass = PASS;
   
   char inUser[BUF_SIZE];
   char inPass[BUF_SIZE];
   bool validCredentials = false;
   
   while (!validCredentials)
   {
      memset(inUser, 0, sizeof(inUser));
      memset(inPass, 0, sizeof(inPass));
      
      printf("Username: ");
      scanf("%s", inUser);

      printf("Password: ");
      scanf("%s", inPass);

      validCredentials = (strcmp(_user, inUser) == 0 &&
                          strcmp(_pass, inPass) == 0);
      
      if (!validCredentials)
      {
         printf("INVALID CREDENTIALS, TRY AGAIN...\n");
      }
   }
}

void socketInteract(int sock)
{
   const int timeout = 100; // milliseconds
   int ready;
   struct pollfd fds;
   fds.fd = sock;
   fds.events = POLLIN | POLLOUT; // Data to read; writing is possible

   while (true)
   {
      ready = poll(&fds, 1, timeout);
      if (ready == -1)
      {
#if PRINT_ERRORS
         perror("POLL FAILED");
#endif
         return;
      }
      else if (ready > 0)
      {
         if (fds.revents & POLLIN) // New data to read
         {
            char buf[2048];
            ssize_t bytes = 0;
            memset(buf, 0, sizeof(buf));
            bytes = read(fds.fd, buf, sizeof(buf));
            if (bytes == -1)
            {
#if PRINT_ERRORS
               perror("READ FAILED");
#endif
               return;
            }
            else if (bytes > 0)
            {
               printf("%s", buf);
            }
         }
         else if (fds.revents & POLLOUT) // Able to write
         {
            char buf[2048];
            ssize_t bytes = 0;
            char* ret = NULL;
            memset(buf, 0, sizeof(buf));
            ret = fgets(buf, sizeof(buf), stdin);
            if (ret == NULL)
            {
#if PRINT_ERRORS
               perror("FGETS FAILED");
#endif
               return;
            }
            bytes = write(fds.fd, buf, sizeof(buf));
            if (bytes == -1)
            {
#if PRINT_ERRORS
               perror("WRITE FAILED");
#endif
               return;
            }
            if (strcmp(buf, "exit\n") == 0)
            {
               return;
            }
         }
      }
   }
}

int main(int argc, char* argv[])
{
   struct sockaddr_in serverAddress;
   
   if (argc != 2)
   {
      printf("USAGE: %s <IP_addr>\n", argv[0]);
      return 1;
   }

   validateCredentials();
   
   serverAddress.sin_family = AF_INET;
   serverAddress.sin_port = htons(PORT);

   if (inet_aton(argv[1], &serverAddress.sin_addr) == 0)
   {
#if PRINT_ERRORS
      printf("INVALID ADDRESS!\n");
#endif
      return 1;
   }

   int sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd == -1)
   {
#if PRINT_ERRORS
      perror("SOCKET CREATION FAILED");
#endif
      return 1;
   }

   if (connect(sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
   {
#if PRINT_ERRORS
     perror("SOCKET CONNECTION FAILED");
#endif
      return 1;
   }

   socketInteract(sockfd);

   if (close(sockfd) == -1)
   {
#if PRINT_ERRORS
      perror("SOCKET CLOSING FAILED");
#endif
      return 1;
   }

   return 0;
}

