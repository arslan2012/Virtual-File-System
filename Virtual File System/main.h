//
//  main.h
//  Virtual File System
//
//  Created by ئ‍ارسلان ئابلىكىم on 3/17/16.
//  Copyright © 2016 BUPT. All rights reserved.
//

#ifndef main_h
#define main_h
#define NAMELENTH 10
#define CONTENTLENTH 100
#define FILEAMOUNT 100

enum boolean
{
    false,
    true
};
struct vfile{
    char fileContent[CONTENTLENTH];
    char fileName[NAMELENTH];
};
struct dir{
    char dirName[NAMELENTH];
    int pos;
    int childDirPos;
    int parentDirPos;
    int nextDirPos;
    int filePoses[FILEAMOUNT];
};

void prepend(char*, const char*);
void printdir(struct dir *);
void showDirectoryTree(struct dir *);
enum boolean setCurrentDirectory(struct dir **,char *);
enum boolean ifdir(char *);
int getNewPos(enum boolean);
enum boolean addLeaf(struct dir *,char *);
enum boolean removeLeaf(struct dir *,char *);
enum boolean mv(char *,char *);
#endif /* main_h */
