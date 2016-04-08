//
//  setCurrentDirectory.c
//  Virtual File System
//
//  Created by ئ‍ارسلان ئابلىكىم on 4/6/16.
//  Copyright © 2016 BUPT. All rights reserved.
//

#include "setCurrentDirectory.h"
bool setCurrentDirectory(dir ** currentDirectory,char * arg){
    if (strcmp(arg, "..")==0){
        if((*(currentDirectory))->parentDirPos != -1){
            fseek ( vfs , (*(currentDirectory))->parentDirPos , SEEK_SET );
            fread(*currentDirectory,sizeof(dir),1,vfs);
            return true;
        }else return false;
        
    }
    if((*(currentDirectory))->childDirPos != -1){
        dir * tmp = malloc(sizeof(dir));
        fseek ( vfs , (*(currentDirectory))->childDirPos , SEEK_SET );
        fread(tmp,sizeof(dir),1,vfs);
        do{
            if (strcmp(tmp->dirName,arg)==0){
                *currentDirectory = tmp;
                return true;
            }
            if (tmp->nextDirPos == -1) {
                break;
            }else{
                fseek ( vfs , tmp->nextDirPos , SEEK_SET );
                fread(tmp,sizeof(dir),1,vfs);
            }
        }while (1);
        free(tmp);
    }
    return false;
}