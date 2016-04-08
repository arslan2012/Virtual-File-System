//
//  addLeaf.c
//  Virtual File System
//
//  Created by ئ‍ارسلان ئابلىكىم on 4/6/16.
//  Copyright © 2016 BUPT. All rights reserved.
//

#include "addLeaf.h"
#include "ifdir.h"
#include "getNewPos.h"
bool addLeaf(dir * thisdir,char * arg){
    if (ifdir(arg)){
        dir * new = malloc(sizeof(dir));
        strcpy(new->dirName,arg);
        new->childDirPos = -1;
        new->parentDirPos = thisdir->pos;
        new->nextDirPos = -1;
        new->filePoses[0] = -1;
        int pos = getNewPos(true);
        new->pos = pos;
        fseek ( vfs , new->pos , SEEK_SET );
        fwrite(new,sizeof(dir),1,vfs);
        if (thisdir->childDirPos == -1){
            thisdir->childDirPos=pos;
            fseek ( vfs , thisdir->pos , SEEK_SET );
            fwrite(thisdir,sizeof(dir),1,vfs);
        }else {
            dir * tmp = malloc(sizeof(dir));;
            fseek ( vfs , thisdir->childDirPos , SEEK_SET );
            fread(tmp,sizeof(dir),1,vfs);
            while(tmp->nextDirPos != -1){
                fseek ( vfs , tmp->nextDirPos , SEEK_SET );
                fread(tmp,sizeof(dir),1,vfs);
            }
            tmp->nextDirPos=pos;
            fseek ( vfs , tmp->pos , SEEK_SET );
            fwrite(tmp,sizeof(dir),1,vfs);
        }
        free(new);
    }else {
        vfile * new = malloc(sizeof(vfile));
        strcpy(new->fileName,arg);
        new->fileContentLenth=0;
        new->fileContent[0]='\0';
        int i;
        for (i = 0;thisdir->filePoses[i] != -1; i++);
        int pos = getNewPos(false);
        fseek ( vfs , pos , SEEK_SET );
        fwrite(new,sizeof(vfile),1,vfs);
        thisdir->filePoses[i] =pos;
        thisdir->filePoses[i+1] = -1;
        fseek ( vfs , thisdir->pos , SEEK_SET );
        fwrite(thisdir,sizeof(vfile),1,vfs);
        free(new);
    }
    return true;
}