//
//  getFileContent.c
//  Virtual File System
//
//  Created by 胡嘉杰 on 16/5/17.
//  Copyright © 2016年 BUPT. All rights reserved.
//

#include "getFileContent.h"
#include "getDirectoryByString.h"
char * getFileContent(char * fullFileName){
    if(strcmp(fileName,"\0")!=0){
    vfs = fopen(fileName, "r+b");
    vfile * target = getFileByString(fullFileName);
        fclose(vfs);
        return target->fileContent;
    }else return "\0";
}