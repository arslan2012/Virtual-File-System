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
#include "getDirectoryByString.h"
#include "showDirectoryTree.h"
#include "setCurrentDirectory.h"
#include "printdir.h"
#include "ifdir.h"
#include "getNewPos.h"
#include "addLeaf.h"
#include "removeLeaf.h"
#include "mv.h"
#include "openVirtualFile.h"
#define COMLENTH 10
#define ARGLENTH 50

FILE *vfs;

int main(int argc, const char * argv[]) {
    dir * currentDirectory = malloc(sizeof(dir));
    while (1) {
        char *command=malloc(sizeof(char)*COMLENTH);
        printdir(currentDirectory);
        printf(">");
        scanf("%s",command);
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
            char *argument=malloc(sizeof(char)*ARGLENTH);
            scanf("%s",argument);
            if( (vfs = fopen(argument, "w+b")) == NULL ) {
                perror("Fatal Error");
                break;
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
                currentDirectory = MFT;
            }else{
                perror("Fatal Error");
            }
        }else if (strcmp(command, "mount")==0){
            char *argument=malloc(sizeof(char)*ARGLENTH);
            scanf("%s",argument);
            dir * MFT = malloc(sizeof(dir));
            if( (vfs = fopen(argument, "r+b")) == NULL ) {
                perror("Fatal Error");
                break;
            }
            fseek ( vfs, sizeof(int), SEEK_SET);
            if (fread(MFT,sizeof(dir),1,vfs)==1){
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
            char *argument=malloc(sizeof(char)*ARGLENTH);
            scanf("%99[^\n]%*c",argument);
            if (strcmp(argument,"")==0) {
                showDirectoryTree(currentDirectory);
            }else{
                dir * pointedDir = getDirectoryByString(argument+1);
                if (pointedDir != NULL)
                    showDirectoryTree(pointedDir);
                else printf("The directory you pointed doesn't exist\n");
            }
        }else if (strcmp(command, "cd")==0){
            char *argument=malloc(sizeof(char)*ARGLENTH);
            scanf("%s",argument);
            if (!setCurrentDirectory(&currentDirectory,argument))
                printf("ERROR:directory doesn't exist\n");
        }else if (strcmp(command, "touch")==0){
            char *argument=malloc(sizeof(char)*ARGLENTH);
            scanf("%s",argument);
            if (!addLeaf(currentDirectory,argument))
                printf("ERROR:cannot create\n");
        }else if (strcmp(command, "open")==0){
            char *argument=malloc(sizeof(char)*ARGLENTH);
            scanf("%s",argument);
            if (!openVirtualFile(currentDirectory,argument))
                printf("ERROR:open failed\n");
        }else if (strcmp(command, "rm")==0){
            char *argument=malloc(sizeof(char)*ARGLENTH);
            scanf("%s",argument);
            if (!removeLeaf(currentDirectory,argument))
                printf("ERROR:cannot remove\n");
        }else if (strcmp(command, "mv")==0){
            char *argument=malloc(sizeof(char)*ARGLENTH);
            scanf("%s",argument);
            char *argument2=malloc(sizeof(char)*ARGLENTH);
            scanf("%s",argument2);
            if (!mv(argument,argument2))
            printf("ERROR: There is a file with same name\n");
        }else {
            printf("%s",command);
            printf(":Unknown command!\n");
        }
    }
    return 0;
}