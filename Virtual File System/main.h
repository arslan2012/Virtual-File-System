//
//  main.h
//  Virtual File System
//
//  Created by ئ‍ارسلان ئابلىكىم on 3/17/16.
//  Copyright © 2016 BUPT. All rights reserved.
//

#ifndef main_h
#define main_h
enum boolean
{
    false,
    true
};
struct vfile{
    int contentLenth;
    char * content;
    char * name;
    struct vfile * nextFileInThisDir;
};
struct dir{
    char * dirname;
    struct dir * childDir;
    struct dir * parentDir;
    struct dir * nextDir;
    struct vfile * files;
};

void prepend(char*, const char*);
void printdir(struct dir *);
void showDirectoryTree(struct dir *);
enum boolean setCurrentDirectory(struct dir **,char *);
enum boolean ifdir(char *);
enum boolean addLeaf(struct dir *,char *);
enum boolean removeLeaf(struct dir *,char *);
enum boolean mv(char *,char *);
#endif /* main_h */
