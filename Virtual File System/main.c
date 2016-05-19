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
#include "checkCommand.h"
#include "ConsoleColour.h"
#define COMLENTH 10
#define ARGLENTH 50

char fileName[10]="\0";
FILE * vfs;
int superuser = 0;

int main(int argc, const char * argv[]) {
    dir * currentDirectory = malloc(sizeof(dir));
    const char *invalid_characters = "\\*";
    const char *root_password = "root";
    while (1) {
        char *command=malloc(sizeof(char)*COMLENTH);
		if(strcmp(fileName,"\0")!=0 && currentDirectory != NULL && currentDirectory->dirName[0] != '\0'){
			vfs = fopen(fileName, "r+b");
			fseek ( vfs , currentDirectory->pos , SEEK_SET );
			fread(currentDirectory,sizeof(dir),1,vfs);
		}
        printdir(currentDirectory);
		fclose(vfs);
        scanf("%s",command);
        int comNum = checkCommand(command);
        
        switch (comNum) {
            case 0://man
                printf(ConsoleForeLightBlue"create <filename> \t create a new virtual file system\n"ConsoleForeDefault);
                printf(ConsoleForeLightBlue"mount <filename> \t mount an existing virtual file system\n"ConsoleForeDefault);
                printf(ConsoleForeLightBlue"ls <dirname> \t\t show directory structure\n"ConsoleForeDefault);
                printf(ConsoleForeLightBlue"cd <dirname> \t\t get in the directory\n"ConsoleForeDefault);
                printf(ConsoleForeLightBlue"touch <filename> \t create a new virtual file\n"ConsoleForeDefault);
                printf(ConsoleForeLightBlue"rm <filename> \t\t delete a virtual file\n"ConsoleForeDefault);
                printf(ConsoleForeLightBlue"mv <filename> <filename> rename/move a virtual file\n"ConsoleForeDefault);
                printf(ConsoleForeLightBlue"open <filename> \t open a virtual file\n"ConsoleForeDefault);
                printf(ConsoleForeLightBlue"exit \t\t\t exit this program\n"ConsoleForeDefault);
                break;
            case 1://exit
                fclose(vfs);
                return 0;
            case 2:{//su
                char *argument=malloc(sizeof(char)*ARGLENTH);
                scanf("%s",argument);
                if (strcmp(argument, "-s")==0) {
                    char *inputpass=malloc(sizeof(char)*COMLENTH);
                    printf("Please input your password:");
                    scanf("%s",inputpass);
                    if (strcmp(inputpass, root_password)==0) {
                        printf(ConsoleForeBlue"successfully gained root privilage\n"ConsoleForeDefault);
                        superuser = 1;
                    }else printf(ConsoleForeLightRed"Wrong password!"ConsoleForeDefault);
                }else if (strcmp(argument, "-")==0) {
                    printf(ConsoleForeBlue"successfully returned to normal user\n"ConsoleForeDefault);
                    superuser = 0;
                }else {
                    printf(ConsoleForeLightRed"sorry that user doesn't exist"ConsoleForeDefault);
                }
                break;
            }
            case 3:{//create
                char *argument=malloc(sizeof(char)*ARGLENTH);
                scanf("%s",argument);
                if( (vfs = fopen(argument, "w+b")) == NULL ) {
                    perror(ConsoleForeLightRed"Fatal Error"ConsoleForeDefault);
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
                    strcpy(fileName, argument);
                    fclose(vfs);
                }else{
                    perror(ConsoleForeLightRed"Fatal Error"ConsoleForeDefault);
                    fclose(vfs);
                }
                
                break;
            }
            case 4:{//mount
                char *argument=malloc(sizeof(char)*ARGLENTH);
                scanf("%s",argument);
                dir * MFT = malloc(sizeof(dir));
                if( (vfs = fopen(argument, "r+b")) == NULL ) {
                    perror(ConsoleForeLightRed"Fatal Error"ConsoleForeDefault);
                    break;
                }
                fseek ( vfs, sizeof(int), SEEK_SET);
                if (fread(MFT,sizeof(dir),1,vfs)==1){
                    if (strcmp(MFT->dirName, "/")==0){
                        currentDirectory = MFT;
                        strcpy(fileName, argument);
                        fclose(vfs);
                    }
                    else{
                        printf(ConsoleForeLightRed"ERROR:mount failed,dirty file system\n"ConsoleForeDefault);
                        fclose(vfs);
                    }
                }else{
                    perror("Fatal Error"ConsoleForeDefault);
                    fclose(vfs);
                    return 0;
                }
            }
                break;
            case 5://ls
                if(strcmp(fileName,"\0")!=0){
                    vfs = fopen(fileName, "r+b");
                    char *argument=malloc(sizeof(char)*ARGLENTH);
                    scanf("%99[^\n]%*c",argument);
                    if (strcmp(argument,"")==0) {
                        showDirectoryTree(currentDirectory);
                    }else{
                        dir * pointedDir = getDirectoryByString(argument+1);
                        if (pointedDir != NULL)
                            showDirectoryTree(pointedDir);
                        else printf(ConsoleForeLightRed"The directory you pointed doesn't exist\n"ConsoleForeDefault);
                    }
                }else printf(ConsoleForeLightRed"no file system mounted!\n"ConsoleForeDefault);
                fclose(vfs);
                break;
            case 6://cd
                if(strcmp(fileName,"\0")!=0){
                    vfs = fopen(fileName, "r+b");
                    char *argument=malloc(sizeof(char)*ARGLENTH);
                    scanf("%s",argument);
                    if (!setCurrentDirectory(&currentDirectory,argument))
                        printf(ConsoleForeLightRed"ERROR:directory doesn't exist\n"ConsoleForeDefault);
                }else printf(ConsoleForeLightRed"no file system mounted!\n"ConsoleForeDefault);
                fclose(vfs);
                break;
            case 7://touch
                if(strcmp(fileName,"\0")!=0){
                    vfs = fopen(fileName, "r+b");
                    char *argument=malloc(sizeof(char)*ARGLENTH);
                    scanf("%s",argument);
                    char *c = argument;
                    bool flag = true;
                    while (*c)
                    {
                        if (strchr(invalid_characters, *c))
                        {
                            printf(ConsoleForeLightRed"Invalid character in name"ConsoleForeDefault);
                            flag = false;
                            break;
                        }
                        
                        c++;
                    }
                    if (flag)
                        if (!addLeaf(currentDirectory,argument))
                            printf(ConsoleForeLightRed"ERROR:cannot create\n"ConsoleForeDefault);
                }else printf(ConsoleForeLightRed"no file system mounted!\n"ConsoleForeDefault);
                fclose(vfs);
                break;
            case 8://rm
                if(strcmp(fileName,"\0")!=0){
                    vfs = fopen(fileName, "r+b");
                    char *argument=malloc(sizeof(char)*ARGLENTH);
                    scanf("%s",argument);
                    if (!removeLeaf(currentDirectory,argument))
                        printf(ConsoleForeLightRed"ERROR:cannot remove\n"ConsoleForeDefault);
                }else printf(ConsoleForeLightRed"no file system mounted!\n"ConsoleForeDefault);
                fclose(vfs);
                break;
            case 9://mv
                if(strcmp(fileName,"\0")!=0){
                    vfs = fopen(fileName, "r+b");
                    char *argument=malloc(sizeof(char)*ARGLENTH);
                    scanf("%s",argument);
                    char *argument2=malloc(sizeof(char)*ARGLENTH);
                    scanf("%s",argument2);
                    if (!mv(argument,argument2))
                        printf(ConsoleForeLightRed"ERROR: There is a file with same name\n"ConsoleForeDefault);
                }else printf(ConsoleForeLightRed"no file system mounted!\n"ConsoleForeDefault);
                fclose(vfs);
                break;
            case 10://open
                if(strcmp(fileName,"\0")!=0){
                    vfs = fopen(fileName, "r+b");
                    char *argument=malloc(sizeof(char)*ARGLENTH);
                    scanf("%s",argument);
                    if (!openVirtualFile(currentDirectory,argument))
                        printf(ConsoleForeLightRed"ERROR:open failed\n"ConsoleForeDefault);
                }else printf(ConsoleForeLightRed"no file system mounted!\n"ConsoleForeDefault);
                fclose(vfs);
                break;
            case 11://unmount
                fclose(vfs);
                strcpy(fileName, "\0");
                break;
            default:
                printf(ConsoleForeLightRed"%s:Unknown command!\n",command);
                break;
        }
    }
    return 0;
}