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

bool mv(bool remove,char *arg1,char * arg2){
	char * str1 = malloc(sizeof(arg1));
	char * str2 = malloc(sizeof(arg1));
	strcpy(str1, arg1);//backup arg1,arg2 because strtok changes its value
	strcpy(str2, arg2);
	vfile * target = getFileByString(arg1);//get the file
	if (target==NULL) return false;
	dir * targetDir = getDirectoryByString(str1);//get the file directory
	dir * destination = getDirectoryByString(arg2);//get the destination directory
	char * desiredName = getSuffixByFullPath(str2);//get the desired name
	int i = 0,targetPos;
	for (i = 0; destination->filePoses[i]!=-1; i++);//find the last pos, so we can insert the new file pos there.
	
	for (int j=0;targetDir->filePoses[j]!=-1;j++){//find the target file position
		vfile * tmp = malloc(sizeof(vfile));
		fseek ( vfs , targetDir->filePoses[j] , SEEK_SET );
		fread(tmp,sizeof(dir),1,vfs);
		if (strcmp(target->fileName, tmp->fileName)==0) {
			targetPos=targetDir->filePoses[j];
			if (desiredName[strlen(desiredName)-1] != '/') {//write the new name to file, if assigned.
				strcpy(tmp->fileName,desiredName);
				fseek ( vfs , targetDir->filePoses[j] , SEEK_SET );
				fwrite(tmp,sizeof(dir),1,vfs);
			}
			free(tmp);
			break;
		}else free(tmp);
	}
	if (targetPos==-1) return false;
	destination->filePoses[i] =targetPos;//change the destination directory so that it know it has a new file
	destination->filePoses[i+1] = -1;
	fseek ( vfs , destination->pos , SEEK_SET );//write the destination directory
	fwrite(destination,sizeof(dir),1,vfs);
	if (remove) {
		bool tmp = removeLeaf(targetDir,(desiredName[strlen(desiredName)-1] != '/')?desiredName:target->fileName);//remove the target file from the old dir
		if (!tmp) {
			printf("remove original file failed while moving\n");
		}
	}
	return true;
}