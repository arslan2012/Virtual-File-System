	//
	//  initSystemFile.c
	//  Virtual File System
	//
	//  Created by ئ‍ارسلان ئابلىكىم on 5/19/16.
	//  Copyright © 2016 BUPT. All rights reserved.
	//

#include "initSystemFile.h"
#include "ConsoleColour.h"
_bool initSystemFile(){
	dir * MFT = malloc(sizeof(dir));
	if( (vfs = fopen("System.vfs", "r+b")) == NULL ) {//try to open
		if( (vfs = fopen("System.vfs", "w+b")) == NULL ) {//if opening failed,try to create a new one
			perror(ConsoleForeLightRed"Fatal Error"ConsoleForeDefault);
			return _false;
		}
		dir * MFT = malloc(sizeof(dir));//create new master file tree.
		strcpy(MFT->dirName,"/");
		MFT->pos = sizeof(int);
		MFT->parentDirPos = -1;
		MFT->childDirPos = -1;
		MFT->nextDirPos = -1;
		MFT->filePoses[0] = -1;
		int lastpos=sizeof(dir)+sizeof(int);
		fseek ( vfs , 0, SEEK_SET );
		fwrite(&lastpos,sizeof(int),1,vfs);
		fseek ( vfs , sizeof(int) , SEEK_SET );
		if(fwrite(MFT,sizeof(dir),1,vfs)==1){
			strcpy(fileName, "System.vfs");
			if (vfs != NULL) fclose(vfs);
			return _true;
		}else{
			perror(ConsoleForeLightRed"Fatal Error"ConsoleForeDefault);
			if (vfs != NULL) fclose(vfs);
			return _false;
		}
	}else {//if opening succeeded,check if MFT is healthy
		fseek ( vfs, sizeof(int), SEEK_SET);
		if (fread(MFT,sizeof(dir),1,vfs)==1){
			if (strcmp(MFT->dirName, "/")==0){
				strcpy(fileName, "System.vfs");
				if (vfs != NULL) fclose(vfs);
				return _true;
			}
			else{
				printf(ConsoleForeLightRed"ERROR:mount failed,dirty file system\n"ConsoleForeDefault);
				if (vfs != NULL) fclose(vfs);
				return _false;
			}
		}else{
			perror("Fatal Error"ConsoleForeDefault);
			if (vfs != NULL) fclose(vfs);
			return _false;
		}
	}
}