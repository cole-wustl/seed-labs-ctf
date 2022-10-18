#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#ifndef USER
#define USER "user"
#endif

#ifndef PASS
#define PASS "pass"
#endif

#ifndef PORT
#define PORT 3314
#endif

int main(int argc, char* argv[])
{
   const unsigned int BUF_SIZE = 1024;
   const char* _user = USER;
   const char* _pass = PASS;
   
   char inUser[BUF_SIZE];
   char inPass[BUF_SIZE];

   if (argc != 2)
   {
      printf("USAGE: %s <IP_addr>\n", argv[0]);
      return 1;
   }
   
   printf("Username: ");
   scanf("%s", inUser);

   printf("Password: ");
   scanf("%s", inPass);

   printf("Username: %s, Password: %s\n", inUser, inPass);

   int sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd == -1)
   {
      printf("SOCKET CREATION FAILED!\n");
      return 1;
   }

   return 0;
}
