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