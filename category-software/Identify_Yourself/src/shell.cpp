#include <cstdio>
#include <string>

#ifndef USER
#define USER "user"
#endif

#ifndef PASS
#define PASS "pass"
#endif

int main(int argc, char* argv[])
{
   const unsigned int BUF_SIZE = 1024;
   const std::string _user = USER;
   const std::string _pass = PASS;
   std::string inUser;
   std::string inPass;
   char buf[BUF_SIZE];

   if (argc != 2)
   {
      printf("Usage: ./shell <IP_addr>\n");
      return 1;
   }
   
   memset(buf, 0, BUF_SIZE);
   printf("Username: ");
   scanf("%s", buf);
   inUser = std::string(buf);

   memset(buf, 0, BUF_SIZE);
   printf("Password: ");
   scanf("%s", buf);
   inPass = std::string(buf);

   printf("Username: %s, Password: %s\n", inUser.c_str(), inPass.c_str());

   return 0;
}
