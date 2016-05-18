	//
	//  initSystemFile.c
	//  Virtual File System
	//
	//  Created by ئ‍ارسلان ئابلىكىم on 5/19/16.
	//  Copyright © 2016 BUPT. All rights reserved.
	//

#include "initSystemFile.h"
#include "ConsoleColour.h"
bool initSystemFile(){
	dir * MFT = malloc(sizeof(dir));
	if( (vfs = fopen("System.vfs", "r+b")) == NULL ) {
		if( (vfs = fopen("System.vfs", "w+b")) == NULL ) {
			perror(ConsoleForeLightRed"Fatal Error"ConsoleForeDefault);
			return false;
		}
		dir * MFT = malloc(sizeof(dir));
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
			fclose(vfs);
			return true;
		}else{
			perror(ConsoleForeLightRed"Fatal Error"ConsoleForeDefault);
			fclose(vfs);
			return false;
		}
	}else {
		fseek ( vfs, sizeof(int), SEEK_SET);
		if (fread(MFT,sizeof(dir),1,vfs)==1){
			if (strcmp(MFT->dirName, "/")==0){
				fclose(vfs);
				return true;
			}
			else{
				printf(ConsoleForeLightRed"ERROR:mount failed,dirty file system\n"ConsoleForeDefault);
				fclose(vfs);
				return false;
			}
		}else{
			perror("Fatal Error"ConsoleForeDefault);
			fclose(vfs);
			return false;
		}
	}
}