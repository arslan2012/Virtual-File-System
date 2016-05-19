	//
	//  addLeaf.c
	//  Virtual File System
	//
	//  Created by ئ‍ارسلان ئابلىكىم on 4/6/16.
	//  Copyright © 2016 BUPT. All rights reserved.
	//

#include "addLeaf.h"
#include "getNewPos.h"
bool addLeaf(dir * thisdir,char * arg){
	if (arg[strlen(arg)-1] == '/'){//check if creating a directory or file
		dir * new = malloc(sizeof(dir));//create a new directory
		strcpy(new->dirName,arg);
		new->childDirPos = -1;
		new->parentDirPos = thisdir->pos;
		new->nextDirPos = -1;
		new->filePoses[0] = -1;
		if (thisdir->childDirPos == -1){//change the parent directory so that it know it has a new child
			int pos = getNewPos(true);
			new->pos = pos;
			fseek ( vfs , new->pos , SEEK_SET );
			fwrite(new,sizeof(dir),1,vfs);
			thisdir->childDirPos=pos;
			fseek ( vfs , thisdir->pos , SEEK_SET );
			fwrite(thisdir,sizeof(dir),1,vfs);
		}else {//find the last next dir to append to
			dir * tmp = malloc(sizeof(dir));;
			fseek ( vfs , thisdir->childDirPos , SEEK_SET );
			fread(tmp,sizeof(dir),1,vfs);
			while(tmp->nextDirPos != -1){
				if(strcmp(tmp->dirName,arg)==0){
					free(new);
					return false;
				}
				fseek ( vfs , tmp->nextDirPos , SEEK_SET );
				fread(tmp,sizeof(dir),1,vfs);
			}
			if(strcmp(tmp->dirName,arg)==0){
				free(new);
				return false;
			}
			int pos = getNewPos(true);
			new->pos = pos;
			fseek ( vfs , new->pos , SEEK_SET );//write the new dir to disk
			fwrite(new,sizeof(dir),1,vfs);
			tmp->nextDirPos=pos;
			fseek ( vfs , tmp->pos , SEEK_SET );//write to the parent dir
			fwrite(tmp,sizeof(dir),1,vfs);
		}
		free(new);
	}else {// if its a file
		char *argument=malloc(sizeof(char)*3);
		scanf("%99[^\n]%*c",argument);// check if there is extrous argument
		vfile * new = malloc(sizeof(vfile));//create new file
		strcpy(new->fileName,arg);
		new->fileContentLenth=0;
		new->fileContent[0]='\0';
		if (strcmp(argument," -r")==0)//check if extrous argument = -r
			new->attribute=readonly;
		else
			new->attribute=readwrite;
		int i;
		for (i = 0;thisdir->filePoses[i] != -1; i++){//find the last filepos to append to
			vfile * tmp = malloc(sizeof(vfile));
			fseek ( vfs , thisdir->filePoses[i] , SEEK_SET );
			fread(tmp, sizeof(vfile), 1, vfs);
			if (strcmp(tmp->fileName,arg)==0){
				free(tmp);
				return false;
			}
			free(tmp);
		}
		int pos = getNewPos(false);
		fseek ( vfs , pos , SEEK_SET );//write the new file to disk
		fwrite(new,sizeof(vfile),1,vfs);
		thisdir->filePoses[i] =pos;//change the parent directory so that it know it has a new file
		thisdir->filePoses[i+1] = -1;
		fseek ( vfs , thisdir->pos , SEEK_SET );//write to the parent dir
		fwrite(thisdir,sizeof(vfile),1,vfs);
		free(new);
	}
	return true;
}