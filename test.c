#include <stdio.h>
#include "clargs.h"

int intval = 0;
const char* filename = "/var/log/syslog";
int cflag = 0;
int show_help = 0;

DefLine defs[] = {
   { 'h', "Show this help", &show_help, NULL },
   { 'v', "Set an integer value.", &intval, clargs_set_int },
   { 'f', "Set filename.", &filename, clargs_set_string },
   { 'c', "Set c flag.", &cflag, NULL },
   { '\0', "", NULL, NULL }
};

int main(int argc, const char **argv)
{
   clargs_process(defs, argc, argv);

   if (show_help)
      clargs_show(defs);
   else
   {
      printf("intval = %d.\n"
             "filename = %s.\n"
             "cflag = %d.\n",
             intval, filename, cflag);
   }
}
