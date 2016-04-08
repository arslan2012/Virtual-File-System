//
//  removeLeaf.c
//  Virtual File System
//
//  Created by ئ‍ارسلان ئابلىكىم on 4/6/16.
//  Copyright © 2016 BUPT. All rights reserved.
//

#include "removeLeaf.h"
#include "ifdir.h"
bool removeLeaf(dir * thisdir,char * arg){
    if (ifdir(arg)){
        dir * tmp = malloc(sizeof(dir));
        if (thisdir->childDirPos == -1){
            return false;
        }else {
            fseek ( vfs , thisdir->childDirPos , SEEK_SET );
            fread(tmp,sizeof(dir),1,vfs);
            if (strcmp(tmp->dirName,arg)==0){
                dir * tmp2 = malloc(sizeof(dir));
                fseek ( vfs , tmp->nextDirPos , SEEK_SET );
                fread(tmp2,sizeof(dir),1,vfs);
                thisdir->childDirPos=tmp2->pos;
                fseek ( vfs , thisdir->pos , SEEK_SET );
                fwrite(thisdir,sizeof(vfile),1,vfs);
                free(tmp);
                return true;
            }else{
                while(tmp->nextDirPos != -1){
                    
                    dir * tmp2 = malloc(sizeof(dir));
                    fseek ( vfs , tmp->nextDirPos , SEEK_SET );
                    fread(tmp2,sizeof(dir),1,vfs);
                    if (strcmp(tmp2->dirName,arg)==0){
                        dir * tmp3 = malloc(sizeof(dir));
                        fseek ( vfs , tmp2->nextDirPos , SEEK_SET );
                        fread(tmp3,sizeof(dir),1,vfs);
                        tmp->nextDirPos=tmp3->pos;
                        fseek ( vfs , tmp->pos , SEEK_SET );
                        fwrite(tmp,sizeof(dir),1,vfs);
                        free(tmp);free(tmp2);free(tmp3);
                        return true;
                    }
                    else{
                        fseek ( vfs , tmp->nextDirPos , SEEK_SET );
                        fread(tmp,sizeof(dir),1,vfs);
                        free(tmp2);
                    }
                }
            }
        }
    }else {
        if (thisdir->filePoses[0]==-1){
            return false;
        }else {
            for (int i = 0; thisdir->filePoses[i]!=-1;i++){
                vfile *tmp = malloc(sizeof(vfile));
                fseek(vfs, thisdir->filePoses[i], SEEK_SET);
                fread(tmp, sizeof(vfile), 1, vfs);
                if(strcmp(tmp->fileName,arg)==0){
                    for(int j=i; thisdir->filePoses[j]!=-1;j++){
                        thisdir->filePoses[j]=thisdir->filePoses[j+1];
                    }
                    fseek ( vfs , thisdir->pos , SEEK_SET );
                    fwrite(thisdir,sizeof(vfile),1,vfs);
                    free(tmp);
                    return true;
                }else{
                    free(tmp);
                }
            }
        }
    }
    return false;
}