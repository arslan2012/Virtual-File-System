//
//  getDirectoryByString.c
//  Virtual File System
//
//  Created by ئ‍ارسلان ئابلىكىم on 4/6/16.
//  Copyright © 2016 BUPT. All rights reserved.
//

#include "getDirectoryByString.h"

dir * getDirectoryByString(char * arg){
    char *tok= strtok (arg,"/");
    dir * tmp = malloc(sizeof(dir));
    fseek ( vfs , sizeof(int) , SEEK_SET );
    fread(tmp,sizeof(dir),1,vfs);
    while (tok != NULL) {
        size_t len = strlen(tok);
        char *str = malloc(len + 2); /* one for extra char, one for trailing zero */
        strcpy(str, tok);
        str[len] = '/';
        str[len + 1] = '\0';
        if (strcmp(str,"")==0) return tmp;
        fseek ( vfs , tmp->childDirPos , SEEK_SET );
        fread(tmp,sizeof(dir),1,vfs);
        do{
            if (strcmp(tmp->dirName,str)==0){
                break;
            }
            else if (tmp->nextDirPos != -1){
                fseek ( vfs , tmp->nextDirPos , SEEK_SET );
                fread(tmp,sizeof(dir),1,vfs);
            }else{
                return NULL;
            }
        }while (1);
        tok = strtok (NULL, "/");
    }
    return tmp;
}