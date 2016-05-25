	//
	//  removeLeaf.c
	//  Virtual File System
	//
	//  Created by ئ‍ارسلان ئابلىكىم on 4/6/16.
	//  Copyright © 2016 BUPT. All rights reserved.
	//

#include "removeLeaf.h"
_bool removeLeaf(dir * thisdir,char * arg){
	if (arg[strlen(arg)-1] == '/'){//check if this string represents a dir by checking if it has '/' at the end
		dir * tmp = malloc(sizeof(dir));
		if (thisdir->childDirPos == -1){//no child directory nothing to remove!
			return _false;
		}else {
			fseek ( vfs , thisdir->childDirPos , SEEK_SET );
			fread(tmp,sizeof(dir),1,vfs);
			if (strcmp(tmp->dirName,arg)==0){//check if child dir is the dir needed to remove
				if (tmp->nextDirPos==-1) {
					thisdir->childDirPos=-1;
				}else{
					dir * tmp2 = malloc(sizeof(dir));
					fseek ( vfs , tmp->nextDirPos , SEEK_SET );
					fread(tmp2,sizeof(dir),1,vfs);
					thisdir->childDirPos=tmp2->pos;
					free(tmp2);
				}
				fseek ( vfs , thisdir->pos , SEEK_SET );
				fwrite(thisdir,sizeof(vfile),1,vfs);
				free(tmp);
				return _true;
			}else{
				while(tmp->nextDirPos != -1){//find the dir needed to remove in nextdir list
					dir * tmp2 = malloc(sizeof(dir));
					fseek ( vfs , tmp->nextDirPos , SEEK_SET );
					fread(tmp2,sizeof(dir),1,vfs);
					if (strcmp(tmp2->dirName,arg)==0){
						if (tmp2->nextDirPos==-1) {
							tmp->nextDirPos=-1;
							free(tmp);free(tmp2);
						}else{
							dir * tmp3 = malloc(sizeof(dir));
							fseek ( vfs , tmp2->nextDirPos , SEEK_SET );
							fread(tmp3,sizeof(dir),1,vfs);
							tmp->nextDirPos=tmp3->pos;
							fseek ( vfs , tmp->pos , SEEK_SET );
							fwrite(tmp,sizeof(dir),1,vfs);
							free(tmp);free(tmp2);free(tmp3);
						}
						return _true;
					}
					else{
						fseek ( vfs , tmp->nextDirPos , SEEK_SET );
						fread(tmp,sizeof(dir),1,vfs);
						free(tmp2);
					}
				}
				return _false;
			}
		}
	}else {
		if (thisdir->filePoses[0]==-1){
			return _false;
		}else {
			for (int i = 0; thisdir->filePoses[i]!=-1;i++){
				vfile *tmp = malloc(sizeof(vfile));
				fseek(vfs, thisdir->filePoses[i], SEEK_SET);
				fread(tmp, sizeof(vfile), 1, vfs);
				if(strcmp(tmp->fileName,arg)==0){
					if (tmp->attribute==readonly && superuser == 0) {
						return _false;
					}
					for(int j=i; thisdir->filePoses[j]!=-1;j++){
						thisdir->filePoses[j]=thisdir->filePoses[j+1];
					}
					fseek ( vfs , thisdir->pos , SEEK_SET );
					fwrite(thisdir,sizeof(vfile),1,vfs);
					free(tmp);
					return _true;
				}else{
					free(tmp);
				}
			}
		}
	}
	return _false;
}