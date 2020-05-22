# CLARGS project

When developing a new command line utility, I wanted to
use command line arguments to modify the execution.  I had
recently developed a
[command line options processing utility for BASH](https://www.github.com/cjungmann/bash_clargs),
so I created this project to use a similar syntax to
easily set command line options with a C program.

The main idea is to create an array of structures
that can be used to save the option values as well
as to document the options' usage.

## What is Allowed

Although only single-dash, single-letter options are
supported, a dash may introduce several options.
The included **test** program will accept **-cv 10**
to set a flag (**-c**) and set a value (**-v 10**).

In all cases, if an option requires a value, subsequent
options following the same dash will be ignored.  For
example, `test -cv 10` will set both flag and value,
but `test -vc 10` will set the value, but ignore the
**-c**.  

## Example

Look at the **test.c** file listing for the entire
program, but this example illustrates how the
option definitions are made.  Please note the final
element of the array sets the *letter* member to '\0'
to signal the end of the array.

~~~c
DefLine defs[] = {
   { 'h', "Show this help.",       &show_help, NULL },
   { 'v', "Set an integer value.", &intval,    clargs_set_int },
   { 'f', "Set filename.",         &filename,  clargs_set_string },
   { 'c', "Set c flag.",           &cflag,     NULL },
   { '\0', "", NULL, NULL }
};
~~~



## Limitations

The library only supports single-dash, single-letter options.
This is more limited than, say **grep**, where both
**-E** and **--extended-regexp** are accepted.