#include <stdio.h>
#include <string.h>

#ifndef USER
#define USER "user"
#endif

#ifndef PASS
#define PASS "pass"
#endif

#define BUF_SIZE 1024

int main(int argc, char* argv[])
{
   if (argc != 2)
   {
      printf("Usage: ./shell <IP_addr>\n");
      return 1;
   }

   char buf[BUF_SIZE];
   memset(buf, 0, BUF_SIZE);
   
   printf("Username: ");

   char* ret = fgets(buf, BUF_SIZE, stdin);
   if (ret != NULL)
   {
      fputs(buf, stdout);
   }

   return 0;
}
