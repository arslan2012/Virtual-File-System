#Virtual File System
![Build](https://img.shields.io/appveyor/ci/gruntjs/grunt/master.svg?style=flat)
##What is this?
This is a part of School project of the class ***Operating System Concept*** that require us to do 3 modules (*File* System, *Memory* management, and *Process* management)
##Change log
###2016-03-28
finished basic create and folder function using linked list.
###2016-04-05
finished basic create mount ls touch rm function using struct and file saving.
###2016-04-08
Splited functions into different files.
added file attribute, simple file content editing.
*Bug:because getch() doesn't work, used getchar instead in open file function, so i can't get backspace key, used \ key instead.*
###2016-05-15
Improved file attributions,added basic move function.
###2016-05-17
minor bug fix,preparing the code for module merging.
optimized main.c and file handling
###2016-05-18
added initializing system disk function
###2016-05-19
fixed bug in main, current directory not refreshing
fixed bug in remove, when next dir doesn't exist.
minor data loss, rewrited some code