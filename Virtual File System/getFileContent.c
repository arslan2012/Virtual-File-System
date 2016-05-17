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
    vfile * target = getFileByString(fullFileName);
    return target->fileContent;
}