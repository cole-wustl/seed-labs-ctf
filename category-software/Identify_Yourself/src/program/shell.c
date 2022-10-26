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

#ifdef HARD
static const char* _md5_hash = "$1$NFo4QwBt$ZuSK3X/.MrhrqyGDz3Fow."; // Generated using md5pass utility

int verifyMD5Hash(const char* inKey)
{
   return strcmp(crypt(inKey, _md5_hash), _md5_hash) == 0;
}
#endif

void validateCredentials()
{
   const unsigned int BUF_SIZE = 1024;
   const char* _user = USER;
   const char* _pass = PASS;
   
   char inUser[BUF_SIZE];
   char* inPass;
   bool validCredentials = false;
  
   while (!validCredentials)
   {
      memset(inUser, 0, sizeof(inUser));
      
      printf("Username: ");
      scanf("%s", inUser);

      inPass = getpass("Password: ");
      if (inPass == NULL)
      {
         #if PRINT_ERRORS
         perror("GETPASS FAILED");
         #endif
         continue;
      }
      else
      {
         #ifdef HARD
         validCredentials = (strcmp(_user, inUser) == 0 &&
                             verifyMD5Hash(inPass) == 1);
         #else
         validCredentials = (strcmp(_user, inUser) == 0 &&
                             strcmp(_pass, inPass) == 0);
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
   int ret = 0;
   
   if (sock < 0 || outBuf == NULL || bufSize < 1)
   {
      ret = -1;
   }
   else
   {
      const int timeout = 100; // milliseconds
      struct pollfd fds;
      fds.fd = sock;
      fds.events = POLLIN;
      
      int ready = poll(&fds, 1, timeout);
      if (ready < 0)
      {
         #if PRINT_ERRORS
         perror("POLL FAILED");
         #endif
         ret = -1;
      }
      else if (ready && (fds.revents & POLLIN))
      {
         char tmpBuf[bufSize];
         ssize_t Bytes = read(sock, tmpBuf, sizeof(tmpBuf));
         if (Bytes < 0)
         {
            #if PRINT_ERRORS
            perror("READ FAILED");
            #endif
            ret = -1;
         }
         else if (Bytes > 0)
         {
            memcpy(outBuf, tmpBuf, (Bytes < bufSize ? Bytes : bufSize));
            ret = Bytes;
         }
      }
   }

   return ret;
}

int socketWrite(int sock, char* inBuf, int bufSize)
{
   int ret = 0;
   
   if (sock < 0 || inBuf == NULL || bufSize < 1)
   {
      ret = -1;
   }
   else
   {
      const int timeout = 100; // milliseconds
      int ret = 0;
      struct pollfd fds;
      fds.fd = sock;
      fds.events = POLLOUT;
      
      int ready = poll(&fds, 1, timeout);
      if (ready < 0)
      {
         #if PRINT_ERRORS
         perror("POLL FAILED");
         #endif
         ret = -1;
      }
      else if (ready && (fds.revents & POLLOUT))
      {
         ssize_t Bytes = write(sock, inBuf, bufSize);
         if (Bytes < 0)
         {
            #if PRINT_ERRORS
            perror("WRITE FAILED");
            #endif
            ret = -1;
         }
         else
         {
            ret = Bytes;
         }
      }
   }

   return ret;
}

int socketPeerOpen(int sock)
{
   int ret = 1;

   if (sock < 0)
   {
      ret = -1;
   }
   else
   {
      const int timeout = 100; // milliseconds
      int ret = 0;
      struct pollfd fds;
      fds.fd = sock;
      fds.events = POLLHUP;
      
      int ready = poll(&fds, 1, timeout);
      if (ready < 0)
      {
         #if PRINT_ERRORS
         perror("POLL FAILED");
         #endif
         ret = -1;
      }
      else if (ready && (fds.revents & POLLHUP))
      {
         ret = 0;
      }
   }

   return ret;
}

bool isEmptyString(char* str, int len)
{
   // Return true if str consists of only ' ' and '\n', false otherwise.
   if (str != NULL && len > 0)
   {
      for (int i = 0; i < len; i++)
      {
         if (isspace(str[i]) || str[i] == '\n')
         {
            continue;
         }
         else
         {
            return false;
         }
      }
   }
   return true;
}

void socketInteract(int sock)
{
   char buf[5000];
   bool read = true;

   while (socketPeerOpen(sock) == 1)
   {
      if (read)
      {
         while (read)
         {
            memset(buf, 0, sizeof(buf));
            if (socketRead(sock, buf, sizeof(buf)) > 0)
            {
               fputs(buf, stdout);
            }
            else
            {
               read = false;
            }
         }
      }
      else
      {
         memset(buf, 0, sizeof(buf));
         fgets(buf, sizeof(buf), stdin);
         if (strcmp(buf, "exit\n") == 0)
         {
            return;
         }
         else if (!isEmptyString(buf, strlen(buf)))
         {
            socketWrite(sock, buf, strnlen(buf, sizeof(buf)));
            read = true;
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
   
   validateCredentials(); // Check credentials before connecting to remote host

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

