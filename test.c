#include <stdio.h>
#include "clargs.h"

typedef void (*announcer_t)(void);

void Polite_Announce(void) { printf("Pleased to meet you.\n"); }
void Rude_Announce(void) { printf("What are you looking at?\n"); }

int intval = 0;
const char* filename = "/var/log/syslog";
int cflag = 0;
int show_help = 0;
announcer_t Announcer = Polite_Announce;

void Announce_Setter(const DefLine *option, const char *value)
{
   printf("Announce setter for %s\n", option->help);
   Announcer = (announcer_t)option->target;
}


DefLine defs[] = {
   { 'h', "Show this help.",          &show_help,      NULL },
   { 'v', "Set an integer value.",    &intval,         clargs_set_int },
   { 'f', "Set filename.",            &filename,       clargs_set_string },
   { 'c', "Set c flag.",              &cflag,          NULL },
   { 'p', "Use polite announcement.", Polite_Announce, Announce_Setter },
   { 'r', "Use rude announcement.",   Rude_Announce,   Announce_Setter },
   CLARGS_END_DEF
};

int main(int argc, const char **argv)
{
   clargs_process(defs, argc, argv);

   if (show_help)
      clargs_show(defs);
   else
   {
      (*Announcer)();
      printf("\n");

      printf("intval = %d.\n"
             "filename = %s.\n"
             "cflag = %d.\n",
             intval, filename, cflag);
   }
}
