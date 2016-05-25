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
	if(strcmp(fileName,"\0")!=0){//if file system has been mounted(init has been executed)
		vfs = fopen(fileName, "r+b");
		vfile * target = getFileByString(fullFileName);
		if (vfs != NULL) fclose(vfs);
		if (target!=NULL)//if file exist.
			return target->fileContent;
		else return "\0";
	}else return "\0";
}