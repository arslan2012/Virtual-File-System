//
//  setFileContent.c
//  Virtual File System
//
//  Created by 胡嘉杰 on 16/5/17.
//  Copyright © 2016年 BUPT. All rights reserved.
//

#include "setFileContent.h"
#include "getDirectoryByString.h"
bool setFileContent(char * fullFileName, char * newFileContent){
    char * str = malloc(sizeof(fullFileName));
    strcpy(str, fullFileName);
    vfile * target = getFileByString(fullFileName);
    dir * targetDir = getDirectoryByString(str);
    int targetPos;
    if(targetDir->filePoses[0]==-1) return false;
    else for (int j=0;targetDir->filePoses[j]!=-1;j++){
        vfile * tmp = malloc(sizeof(vfile));
        fseek ( vfs , targetDir->filePoses[j] , SEEK_SET );
        fread(tmp,sizeof(dir),1,vfs);
        if (strcmp(target->fileName, tmp->fileName)==0) {
            targetPos=targetDir->filePoses[j];
            free(tmp);
            break;
        }else free(tmp);
    }
    if (targetPos==-1) return false;
    else {
        strcpy(target->fileContent,newFileContent);
        target->fileContentLenth=(int)strlen(newFileContent);
        fseek ( vfs , targetPos , SEEK_SET );
        fwrite(target,sizeof(vfile),1,vfs);
        return true;
    }
}