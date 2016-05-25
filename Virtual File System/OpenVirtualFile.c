	//
	//  OpenVirtualFile.c
	//  Virtual File System
	//
	//  Created by ئ‍ارسلان ئابلىكىم on 4/8/16.
	//  Copyright © 2016 BUPT. All rights reserved.
	//

#include "OpenVirtualFile.h"
#if defined(_WIN32) || defined(_WIN64)
_bool openVirtualFile(dir * thisdir,char * arg){
	if (thisdir->filePoses[0]==-1){
		return _false;
	}else {
		for (int i = 0; thisdir->filePoses[i]!=-1;i++){
			vfile *tmp = malloc(sizeof(vfile));
			fseek(vfs, thisdir->filePoses[i], SEEK_SET);
			fread(tmp, sizeof(vfile), 1, vfs);
			if(strcmp(tmp->fileName,arg)==0){
					//open
				if(tmp->attribute == readwrite || superuser == 1){
					system("cls");
					printf("%s",tmp->fileContent);
					char input;
					fflush(stdin);
					while ((input=getch())!=27) {
						if (input == 8) {
							if (tmp->fileContentLenth>0) {
								tmp->fileContent[tmp->fileContentLenth-1]='\0';
								tmp->fileContentLenth -= 1;
								system("cls");
									//for (int i = 0; i < tmp->fileContentLenth; i++) putchar(tmp->fileContent[tmp->fileContentLenth - 1]);
								printf("%s", tmp->fileContent);
								fflush(stdout);
							}
						}else if (input == '\r') {
							tmp->fileContent[tmp->fileContentLenth] = '\n';
							tmp->fileContentLenth += 1;
							tmp->fileContent[tmp->fileContentLenth] = '\0';
							system("cls");
								//for (int i = 0; i < tmp->fileContentLenth; i++) putchar(tmp->fileContent[tmp->fileContentLenth - 1]);
							printf("%s", tmp->fileContent);
							fflush(stdout);
						}
						else {
							tmp->fileContent[tmp->fileContentLenth]=input;
							tmp->fileContentLenth += 1;
							tmp->fileContent[tmp->fileContentLenth]='\0';
							system("cls");
								//for (int i = 0; i < tmp->fileContentLenth; i++) putchar(tmp->fileContent[tmp->fileContentLenth - 1]);
							printf("%s", tmp->fileContent);
							fflush(stdout);
						}
					}
					system("cls");
					fseek ( vfs , thisdir->filePoses[i] , SEEK_SET );
					fwrite(tmp,sizeof(vfile),1,vfs);
					free(tmp);
				}else{
					printf("%s",tmp->fileContent);
				}
				return _true;
			}else{
				free(tmp);
			}
		}
	}
	return _false;
}


#else

_bool openVirtualFile(dir * thisdir,char * arg){
	if (thisdir->filePoses[0]==-1){
		return _false;
	}else {
		for (int i = 0; thisdir->filePoses[i]!=-1;i++){
			vfile *tmp = malloc(sizeof(vfile));
			fseek(vfs, thisdir->filePoses[i], SEEK_SET);
			fread(tmp, sizeof(vfile), 1, vfs);
			if(strcmp(tmp->fileName,arg)==0){
					//open
				if(tmp->attribute == readwrite || superuser == 1){
					printf("%s",tmp->fileContent);
					char input;
					fflush(stdin);
					while ((input=getchar())!=27) {
						if (input == '\\') {
							if (tmp->fileContentLenth>0) {
								tmp->fileContent[tmp->fileContentLenth-1]='\0';
								tmp->fileContentLenth -= 1;
							}
						}else {
							tmp->fileContent[tmp->fileContentLenth]=input;
							tmp->fileContentLenth += 1;
							tmp->fileContent[tmp->fileContentLenth]='\0';
						}
					}
					fseek ( vfs , thisdir->filePoses[i] , SEEK_SET );
					fwrite(tmp,sizeof(vfile),1,vfs);
					free(tmp);
				}else{
					printf("%s",tmp->fileContent);
				}
				return _true;
			}else{
				free(tmp);
			}
		}
	}
	return _false;
}
#endif