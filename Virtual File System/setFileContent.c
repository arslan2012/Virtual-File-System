	//
	//  setFileContent.c
	//  Virtual File System
	//
	//  Created by 胡嘉杰 on 16/5/17.
	//  Copyright © 2016年 BUPT. All rights reserved.
	//

#include "setFileContent.h"
#include "getDirectoryByString.h"
#include "addLeaf.h"
_bool setFileContent(char * fullFileName, char * newFileContent){
	if(strcmp(fileName,"\0")!=0){//if file system has been mounted(init has been executed)
		vfs = fopen(fileName, "r+b");
		char * str = malloc(sizeof(fullFileName));
		strcpy(str, fullFileName);//backup the fullFileName, because strtok changes its value.
		dir * targetDir = getDirectoryByString(str);
		int targetPos=-1;//try and find the position of this file in this directory
		for (int j=0;targetDir->filePoses[j]!=-1;j++){
			vfile * tmp = malloc(sizeof(vfile));
			fseek ( vfs , targetDir->filePoses[j] , SEEK_SET );
			fread(tmp,sizeof(dir),1,vfs);
			if (strcmp(getSuffixByFullPath(fullFileName), tmp->fileName)==0) {
				targetPos=targetDir->filePoses[j];
				free(tmp);
				break;
			}else free(tmp);
		}
		if (targetPos==-1) {//if didn't find the file then create a new one.
			addLeaf(targetDir, getSuffixByFullPath(fullFileName));
		}
		vfile * target = getFileByString(fullFileName);//get the file.
		strcpy(target->fileContent,newFileContent);
		target->fileContentLenth=(int)strlen(newFileContent);
		fseek ( vfs , targetPos , SEEK_SET );
		fwrite(target,sizeof(vfile),1,vfs);
		if (vfs != NULL) fclose(vfs);
		return _true;
	}else return _false;
}