struct _clarg_def_line;

typedef void (*ClargSet)(const struct _clarg_def_line*, const char*);

typedef struct _clarg_def_line
{
   // The first three must be set:
   char       letter;     // Letter, following a dash '-', used to set option
   const char *help;      // string describing the option
   void       *target;    // Fungible pointer on which setfunc may work

   ClargSet   setfunc;    // optional function pointer to process the option value
} DefLine;

#define CLARGS_END_DEF {'\0',NULL,NULL,NULL}

void clargs_set_int(const DefLine *option, const char *value);
void clargs_set_string(const DefLine *option, const char *value);

void clargs_show(const DefLine *options);
void clargs_process(const DefLine *options, int argc, const char **argv);
