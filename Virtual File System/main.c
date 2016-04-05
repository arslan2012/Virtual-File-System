//
//  main.c
//  Virtual File System
//
//  Created by ئ‍ارسلان ئابلىكىم on 3/17/16.
//  Copyright © 2016 BUPT. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#define COMLENTH 10
#define ARGLENTH 50

FILE *vfs;

int main(int argc, const char * argv[]) {
    struct dir * currentDirectory = malloc(sizeof(struct dir));
    while (1) {
        char *command=malloc(sizeof(char)*COMLENTH);
        char *argument=malloc(sizeof(char)*ARGLENTH);
        printdir(currentDirectory);
        printf(">");
        for (int i = 0;command[i-1]!=' ';i++) {
            command[i]=getchar();
            if (command[i]==' '){
                for (int j = 0;argument[j-1]!='\n';j++) {
                    argument[j]=getchar();
                    if (argument[j]=='\n') {
                        argument[j]='\0';
                        break;
                    }
                }
                command[i]='\0';
                break;
            }else if (command[i]=='\n'){
                command[i]='\0';
                break;
            }
        }
        if (strcmp(command, "man")==0) {
            printf("create <filename> \t create a new virtual file system\n");
            printf("mount <filename> \t mount an existing virtual file system\n");
            printf("ls <dirname> \t show directory structure\n");
            printf("cd <dirname> \t get in the directory\n");
            printf("touch <filename> \t create a new virtual file\n");
            printf("rm <filename> \t delete a virtual file\n");
            printf("mv <filename> <filename> \t rename/move a virtual file\n");
            printf("exit \t exit this program\n");
        }else if (strcmp(command, "exit")==0){
            fclose(vfs);
            break;
        }else if (strcmp(command, "create")==0){
            if( (vfs = fopen(argument, "w+b")) == NULL ) {
                perror("Fatal Error");
                break;
            }
            struct dir * MFT = malloc(sizeof(struct dir));
            strcpy(MFT->dirName,"/");
            MFT->pos = 0;
            MFT->parentDirPos = -1;
            MFT->childDirPos = -1;
            MFT->nextDirPos = -1;
            MFT->filePoses[0] = -1;
            fseek ( vfs , 0 , SEEK_SET );
            if(fwrite(MFT,sizeof(struct dir),1,vfs)==1){
                currentDirectory = MFT;
            }else{
                perror("Fatal Error");
            }
        }else if (strcmp(command, "mount")==0){
            struct dir * MFT = malloc(sizeof(struct dir));
            if( (vfs = fopen(argument, "r+b")) == NULL ) {
                perror("Fatal Error");
                break;
            }
            fseek ( vfs, 0, SEEK_SET);
            if (fread(MFT,sizeof(struct dir),1,vfs)==1){
                if (strcmp(MFT->dirName, "/")==0)
                    currentDirectory = MFT;
                else{
                    printf("ERROR:mount failed,dirty file system\n");
                    fclose(vfs);
                }
            }else{
                perror("Fatal Error");
                fclose(vfs);
            }
        }else if (strcmp(command, "ls")==0){
            if (strcmp(argument,"")==0) {
                showDirectoryTree(currentDirectory);
            }else{
                struct dir * pointedDir = getDirectoryByString(argument);
                if (pointedDir != NULL)
                    showDirectoryTree(pointedDir);
                else printf("The directory you pointed doesn't exist");
            }
        }else if (strcmp(command, "cd")==0){
            if (!setCurrentDirectory(&currentDirectory,argument))
                printf("ERROR:directory doesn't exist\n");
        }else if (strcmp(command, "touch")==0){
            if (!addLeaf(currentDirectory,argument))
                printf("ERROR:cannot create");
        }else if (strcmp(command, "rm")==0){
            if (!removeLeaf(currentDirectory,argument))
                printf("ERROR:cannot remove");
        }else if (strcmp(command, "mv")==0){
            char *argument2=(char *)malloc(sizeof(char)*ARGLENTH/2);
            int i = 0;
            while (argument[i]!=' ') {
                i++;
            }
            argument[i]='\0';
            i++;
            int j = 0;
            while (argument[i]!='\0') {
                argument2[j]=argument[i];
                argument[i]='\0';
                j++;i++;
            }
            argument2[j]='\0';
            if (j<=1)
                printf("ERROR: no second argument");
            else
                if (!mv(argument,argument2))
                    printf("ERROR: There is a file with same name");
        }else {
            printf("%s",command);
            printf(":Unknown command!\n");
        }
    }
    return 0;
}

struct dir * getDirectoryByString(char * arg){
    char *tok = arg, *end = arg;
    struct dir * tmp = malloc(sizeof(struct dir));
    fseek ( vfs , 0 , SEEK_SET );
    fread(tmp,sizeof(struct dir),1,vfs);
    while (tok != NULL) {
        strsep(&end, "/");
        if (strcmp(end,"")==0) return tmp;
        fseek ( vfs , tmp->childDirPos , SEEK_SET );
        fread(tmp,sizeof(struct dir),1,vfs);
        do{
            if (strcmp(tmp->dirName,end)==0){
                break;
            }
            else if (tmp->nextDirPos != -1){
                fseek ( vfs , tmp->nextDirPos , SEEK_SET );
                fread(tmp,sizeof(struct dir),1,vfs);
            }else{
                return NULL;
            }
        }while (1);
        tok = end;
    }
    return tmp;
}
void prepend(char* s, const char* t)
{
    size_t len = strlen(t);
    size_t i;
    
    memmove(s + len, s, strlen(s) + 1);
    
    for (i = 0; i < len; ++i)
    {
        s[i] = t[i];
    }
}
void printdir(struct dir * thisdir){
    if (thisdir == NULL) return;
    if (thisdir->dirName[0] == '\0') return;
    char* s = malloc(sizeof(char)*100);
    strcpy(s, thisdir->dirName);
    if (thisdir->parentDirPos == -1){
        printf("%s",s);
        return;
    }
    fseek ( vfs , thisdir->parentDirPos , SEEK_SET );
    struct dir * tmp = malloc(sizeof(struct dir));
    fread(tmp,sizeof(struct dir),1,vfs);
    do{
        prepend(s, tmp->dirName);
        fseek ( vfs , thisdir->parentDirPos , SEEK_SET );
        fread(tmp,sizeof(struct dir),1,vfs);
    }while (tmp->parentDirPos != -1);
    printf("%s",s);
    free(s);
}
void showDirectoryTree(struct dir * thisdir){
    struct dir * tmp = malloc(sizeof(struct dir));
    if (thisdir->childDirPos != -1) {
        fseek ( vfs , thisdir->childDirPos , SEEK_SET );
        fread(tmp,sizeof(struct dir),1,vfs);
        do{
            printf("%s ",tmp->dirName);
            if (tmp->nextDirPos == -1) break;
            fseek ( vfs , tmp->nextDirPos , SEEK_SET );
            fread(tmp,sizeof(struct dir),1,vfs);
        }while (1);
        free(tmp);
    }
    for (int i = 0;thisdir->filePoses[i] != -1 ; i++) {
        fseek ( vfs , thisdir->filePoses[i] , SEEK_SET );
        struct vfile * tmp2 = malloc(sizeof(struct vfile));
        fread(tmp2,sizeof(struct vfile),1,vfs);
        printf("%s ",tmp2->fileName);
        free(tmp2);
    }
    printf("\n");
}
enum boolean setCurrentDirectory(struct dir ** currentDirectory,char * arg){
    if (strcmp(arg, "..")==0){
        if((*(currentDirectory))->parentDirPos != -1){
            fseek ( vfs , (*(currentDirectory))->parentDirPos , SEEK_SET );
            fread(*currentDirectory,sizeof(struct dir),1,vfs);
            return true;
        }else return false;
        
    }
    if((*(currentDirectory))->childDirPos != -1){
        struct dir * tmp = malloc(sizeof(struct dir));
        fseek ( vfs , (*(currentDirectory))->childDirPos , SEEK_SET );
        fread(tmp,sizeof(struct dir),1,vfs);
        do{
            if (strcmp(tmp->dirName,arg)==0){
                *currentDirectory = tmp;
                return true;
            }
            fseek ( vfs , tmp->nextDirPos , SEEK_SET );
            fread(tmp,sizeof(struct dir),1,vfs);
        }while (tmp->childDirPos != -1);
        free(tmp);
    }
    return false;
}
enum boolean ifdir(char * arg){
    int i = 0;
    while (arg[i]!='\0') i++;
    if (arg[i-1]=='/') return true;
    else return false;
}
int getNewPos(enum boolean iffile){
    static int lastpos = sizeof(struct dir);
    if (iffile){
        lastpos += sizeof(struct vfile);
        return lastpos - sizeof(struct vfile);
    }else{
        lastpos += sizeof(struct dir);
        return lastpos - sizeof(struct dir);
    }
}
enum boolean addLeaf(struct dir * thisdir,char * arg){
    if (ifdir(arg)){
        struct dir * new = malloc(sizeof(struct dir));
        strcpy(new->dirName,arg);
        new->childDirPos = -1;
        new->parentDirPos = thisdir->pos;
        new->nextDirPos = -1;
        new->filePoses[0] = -1;
        int pos = getNewPos(false);
        new->pos = pos;
        fseek ( vfs , new->pos , SEEK_SET );
        fwrite(new,sizeof(struct dir),1,vfs);
        if (thisdir->childDirPos == -1){
            thisdir->childDirPos=pos;
            fseek ( vfs , thisdir->pos , SEEK_SET );
            fwrite(thisdir,sizeof(struct dir),1,vfs);
        }else {
            struct dir * tmp = malloc(sizeof(struct dir));;
            fseek ( vfs , thisdir->childDirPos , SEEK_SET );
            fread(tmp,sizeof(struct dir),1,vfs);
            while(tmp->nextDirPos != -1){
                fseek ( vfs , tmp->nextDirPos , SEEK_SET );
                fread(tmp,sizeof(struct dir),1,vfs);
            }
            tmp->nextDirPos=pos;
            fseek ( vfs , tmp->pos , SEEK_SET );
            fwrite(tmp,sizeof(struct dir),1,vfs);
        }
        free(new);
    }else {
        struct vfile * new = malloc(sizeof(struct vfile));
        strcpy(new->fileName,arg);
        int i;
        for (i = 0;thisdir->filePoses[i] != -1; i++);
        int pos = getNewPos(true);
        fseek ( vfs , pos , SEEK_SET );
        fwrite(new,sizeof(struct vfile),1,vfs);
        thisdir->filePoses[i] =pos;
        thisdir->filePoses[i+1] = -1;
        fseek ( vfs , thisdir->pos , SEEK_SET );
        fwrite(thisdir,sizeof(struct vfile),1,vfs);
        free(new);
    }
    return true;
}
enum boolean removeLeaf(struct dir * thisdir,char * arg){
    if (ifdir(arg)){
        struct dir * tmp = malloc(sizeof(struct dir));
        if (thisdir->childDirPos == -1){
            return false;
        }else {
            fseek ( vfs , thisdir->childDirPos , SEEK_SET );
            fread(tmp,sizeof(struct dir),1,vfs);
            if (strcmp(tmp->dirName,arg)==0){
                struct dir * tmp2 = malloc(sizeof(struct dir));
                fseek ( vfs , tmp->nextDirPos , SEEK_SET );
                fread(tmp2,sizeof(struct dir),1,vfs);
                thisdir->childDirPos=tmp2->pos;
                fseek ( vfs , thisdir->pos , SEEK_SET );
                fwrite(thisdir,sizeof(struct vfile),1,vfs);
                free(tmp);
                return true;
            }else{
                while(tmp->nextDirPos != -1){
                    
                    struct dir * tmp2 = malloc(sizeof(struct dir));
                    fseek ( vfs , tmp->nextDirPos , SEEK_SET );
                    fread(tmp2,sizeof(struct dir),1,vfs);
                    if (strcmp(tmp2->dirName,arg)==0){
                        struct dir * tmp3 = malloc(sizeof(struct dir));
                        fseek ( vfs , tmp2->nextDirPos , SEEK_SET );
                        fread(tmp3,sizeof(struct dir),1,vfs);
                        tmp->nextDirPos=tmp3->pos;
                        fseek ( vfs , tmp->pos , SEEK_SET );
                        fwrite(tmp,sizeof(struct dir),1,vfs);
                        free(tmp);free(tmp2);free(tmp3);
                        return true;
                    }
                    else{
                        fseek ( vfs , tmp->nextDirPos , SEEK_SET );
                        fread(tmp,sizeof(struct dir),1,vfs);
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
                struct vfile *tmp = malloc(sizeof(struct vfile));
                fseek(vfs, thisdir->filePoses[i], SEEK_SET);
                fread(tmp, sizeof(struct vfile), 1, vfs);
                if(strcmp(tmp->fileName,arg)==0){
                    for(int j=i; thisdir->filePoses[j]!=-1;j++){
                        thisdir->filePoses[j]=thisdir->filePoses[j+1];
                    }
                    fseek ( vfs , thisdir->pos , SEEK_SET );
                    fwrite(thisdir,sizeof(struct vfile),1,vfs);
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
enum boolean mv(char *arg1,char * arg2){
    return true;
}