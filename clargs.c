#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "clargs.h"

int intval = 0;
const char *filename="/var/log/syslog";

DefLine tops[] = {
   { 'a', "Option a saves an integer value.", &intval, clargs_set_int },
   { 'b', "Option b saves a string value.", &filename, clargs_set_string },
   { '\0', "", NULL, NULL}
};

const DefLine *seek_option(const DefLine *options, char letter)
{
   const DefLine *ptr = options;
   while (ptr->letter)
   {
      if (ptr->letter == letter)
         return ptr;
      ++ptr;
   }

   return NULL;
}

void clargs_show(const DefLine *options)
{
   const DefLine *ptr = options;
   while (ptr->letter)
   {
      printf("-%c: %s\n", ptr->letter, ptr->help);
      ++ptr;
   }
}

void clargs_set_int(const DefLine *option, const char *value)
{
   *((int*)option->target) = atoi(value);
}

void clargs_set_string(const DefLine *option, const char *value)
{
   *((const char **)option->target) = value;
}

void clargs_process(const DefLine *options, int argc, const char **argv)
{
   // The initial value won't be used due to prefix increment in while loop
   const char **ptr = argv;
   
   const char **end = &argv[argc];
   const char *str;

   const DefLine *option;
   ClargSet setfunc = NULL;

   while (++ptr < end)
   {
      str = *ptr;
      if (setfunc)
      {
         assert(option);
         (*setfunc)(option, str);
         setfunc = NULL;
         option = NULL;
      }
      else
      {
         while (*++str)
         {
            if ((option = seek_option(options, *str)))
            {
               if (option->setfunc)
               {
                  setfunc = option->setfunc;
                  break;
               }
               else
                  *(int*)option->target = 1;
            }
            else
            {
               printf("Unknown option %c.\n", *str);
            }
         }
      }
   }
}


