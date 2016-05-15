	//
	//  mv.c
	//  Virtual File System
	//
	//  Created by ئ‍ارسلان ئابلىكىم on 4/6/16.
	//  Copyright © 2016 BUPT. All rights reserved.
	//

#include "mv.h"
#include "getDirectoryByString.h"
#include "removeLeaf.h"

bool mv(char *arg1,char * arg2){
	char * str = malloc(sizeof(arg1));
	strcpy(str, arg1);
	vfile * target = getFileByString(arg1);
	dir * targetDir = getDirectoryByString(str);
	dir * destination = getDirectoryByString(arg2);
	int i,targetPos;
	if (destination->filePoses[0]==-1) i=0;
	else for (i = 0; destination->filePoses[i]!=-1; i++);
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
	destination->filePoses[i] =targetPos;
	destination->filePoses[i+1] = -1;
	fseek ( vfs , destination->pos , SEEK_SET );
	fwrite(destination,sizeof(dir),1,vfs);
	removeLeaf(targetDir,target->fileName);
	return true;
}