//
//  main.h
//  Virtual File System
//
//  Created by ئ‍ارسلان ئابلىكىم on 3/17/16.
//  Copyright © 2016 BUPT. All rights reserved.
//

#ifndef main_h
#define main_h

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define NAMELENTH 10
#define CONTENTLENTH 100
#define FILEAMOUNT 100

extern FILE *vfs;
typedef enum bool
{
    false,
    true
}bool;
typedef enum attribute
{
    readonly,
    readwrite,
}attribute;
typedef struct vfile{
    enum attribute attribute;
    char fileContent[CONTENTLENTH];
    int fileContentLenth;
    char fileName[NAMELENTH];
}vfile;
typedef struct dir{
    char dirName[NAMELENTH];
    int pos;
    int childDirPos;
    int parentDirPos;
    int nextDirPos;
    int filePoses[FILEAMOUNT];
}dir;

#endif /* main_h */
