	//
	//  showDirectoryTree.c
	//  Virtual File System
	//
	//  Created by ئ‍ارسلان ئابلىكىم on 4/6/16.
	//  Copyright © 2016 BUPT. All rights reserved.
	//

#include "showDirectoryTree.h"
#include "ConsoleColour.h"
void showDirectoryTree(dir * thisdir){
	dir * tmp = malloc(sizeof(dir));
	if (thisdir->childDirPos != -1) {
		fseek ( vfs , thisdir->childDirPos , SEEK_SET );
		fread(tmp,sizeof(dir),1,vfs);
		do{
			printf("%s ",tmp->dirName);
			if (tmp->nextDirPos == -1) break;
			fseek ( vfs , tmp->nextDirPos , SEEK_SET );
			fread(tmp,sizeof(dir),1,vfs);
		}while (1);
		free(tmp);
	}
	for (int i = 0;thisdir->filePoses[i] != -1 ; i++) {
		fseek ( vfs , thisdir->filePoses[i] , SEEK_SET );
		vfile * tmp2 = malloc(sizeof(vfile));
		fread(tmp2,sizeof(vfile),1,vfs);
		if (tmp2->attribute==readonly) {
			printf(ConsoleForeMagenta"%s "ConsoleForeDefault,tmp2->fileName);
		}
		else printf("%s ",tmp2->fileName);
		free(tmp2);
	}
	printf("\n");
}