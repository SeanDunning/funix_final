# funix_final
**WORK IN PROGRESS**

Credits for main.cpp and funix.h go to my instructor Sean Davis

Description: 

This program is designed to emulate the UNIX operating system. Features will be added over time. 

Features incorporated:

mkdir: 

mkdir [filename] // Only one file can be created at a time

cd:

cd [directory name] // Can only move up one step, or down one step. Only .. works for parent directory at the moment

ls:

ls [-l] // -l option will show permissions and time of creation, time corresponding to each command input since 
        // beginning of operation

umask:

umask [0-7] // Will set permissions for new directories made corresponding to octal values

chmod:

chmod [permissions] [directory_name] // will change permissions of directory/ only reads in octals at the moment
Example: "chmod 755 filename" will change permissions to rwxr-xr-x

#end
