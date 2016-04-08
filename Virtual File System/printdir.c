//
//  printdir.c
//  Virtual File System
//
//  Created by ئ‍ارسلان ئابلىكىم on 4/6/16.
//  Copyright © 2016 BUPT. All rights reserved.
//

#include "printdir.h"
void prepend(char* s, const char* t)
{
    size_t len = strlen(t);
    size_t i;
    
    memmove(s + len, s, strlen(s) + 1);
    
    for (i = 0; i < len; ++i)
    {
        s[i] = t[i];
    }
}
void printdir(dir * thisdir){
    if (thisdir == NULL) return;
    if (thisdir->dirName[0] == '\0') return;
    char* s = malloc(sizeof(char)*100);
    strcpy(s, thisdir->dirName);
    if (thisdir->parentDirPos == -1){
        printf("%s",s);
        return;
    }
    fseek ( vfs , thisdir->parentDirPos , SEEK_SET );
    dir * tmp = malloc(sizeof(dir));
    fread(tmp,sizeof(dir),1,vfs);
    while (tmp->parentDirPos != -1){
        prepend(s, tmp->dirName);
        fseek ( vfs , tmp->parentDirPos , SEEK_SET );
        fread(tmp,sizeof(dir),1,vfs);
    }
    prepend(s, tmp->dirName);
    printf("%s",s);
    free(s);
}