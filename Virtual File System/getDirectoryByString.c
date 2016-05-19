	//
	//  getDirectoryByString.c
	//  Virtual File System
	//
	//  Created by ئ‍ارسلان ئابلىكىم on 4/6/16.
	//  Copyright © 2016 BUPT. All rights reserved.
	//

#include "getDirectoryByString.h"

dir * getDirectoryByString(char * arg){
	bool isDirString= (arg[strlen(arg)-1] == '/')?true:false;//check if this string represents a dir by checking if it has '/' at the end
	char *nexttok= strtok (arg,"/");//cut the arg by the symbol '/'
	char *tok = malloc(sizeof(char)*10);
	dir * tmp = malloc(sizeof(dir));
	fseek ( vfs , sizeof(int) , SEEK_SET );
	fread(tmp,sizeof(dir),1,vfs);
	while (nexttok != NULL) {
		tok = nexttok;
		nexttok = strtok (NULL, "/");
		if (nexttok == NULL && !isDirString) break;//we dont need to find the last token's dir, because it's a file
		size_t len = strlen(tok);
		char *str = malloc(len + 2); /* one for extra char, one for trailing zero */
		strcpy(str, tok);
		str[len] = '/';
		str[len + 1] = '\0';
		if (strcmp(str,"")!=0 && tmp->childDirPos != -1){//find every dir represented in the string
			fseek ( vfs , tmp->childDirPos , SEEK_SET );
			fread(tmp,sizeof(dir),1,vfs);
			do{
				if (strcmp(tmp->dirName,str)==0){
					break;
				}
				else if (tmp->nextDirPos != -1){
					fseek ( vfs , tmp->nextDirPos , SEEK_SET );
					fread(tmp,sizeof(dir),1,vfs);
				}else if ((nexttok = strtok (NULL, "/"))==NULL){
					return tmp;
				}else return NULL;
			}while (1);
		}
	}
	return tmp;//just return the last dir we found
}
vfile * getFileByString(char * arg){
	bool isDirString= (arg[strlen(arg)-1] == '/')?true:false;//check if this string represents a dir by checking if it has '/' at the end
	if (isDirString) return NULL;//if this is a dir return null
	char *nexttok= strtok (arg,"/");//cut the arg by the symbol '/'
	char *tok = malloc(sizeof(char)*10);
	dir * tmp = malloc(sizeof(dir));
	fseek ( vfs , sizeof(int) , SEEK_SET );
	fread(tmp,sizeof(dir),1,vfs);
	while (nexttok != NULL) {
		tok = nexttok;
		nexttok = strtok (NULL, "/");
		if (nexttok == NULL && !isDirString) break;//we dont need to find the last token's dir, because it's a file
		size_t len = strlen(tok);
		char *str = malloc(len + 2); /* one for extra char, one for trailing zero */
		strcpy(str, tok);
		str[len] = '/';
		str[len + 1] = '\0';
		if (strcmp(str,"")!=0 && tmp->childDirPos != -1){//find every dir represented in the string
			fseek ( vfs , tmp->childDirPos , SEEK_SET );
			fread(tmp,sizeof(dir),1,vfs);
			do{
				if (strcmp(tmp->dirName,str)==0){
					break;
				}
				else if (tmp->nextDirPos != -1){
					fseek ( vfs , tmp->nextDirPos , SEEK_SET );
					fread(tmp,sizeof(dir),1,vfs);
				}else if ((nexttok = strtok (NULL, "/"))==NULL){
					break;
				}else return NULL;
			}while (1);
		}
	}
	if (strcmp(tok,"")!=0 && tmp->filePoses[0] != -1){//find the file in the last dir
		for (int i = 0; tmp->filePoses[i]!=-1; i++) {
			vfile * tmpfile = malloc(sizeof(vfile));
			fseek ( vfs , tmp->filePoses[i] , SEEK_SET );
			fread(tmpfile,sizeof(dir),1,vfs);
			if (strcmp(tok, tmpfile->fileName)==0) {
				return tmpfile;
			}else free(tmpfile);
		}
	}
	return NULL;
}
char * getSuffixByFullPath(char * arg){
	char *nexttok= strtok (arg,"/");
	char *tok = malloc(sizeof(char)*10);
	while (nexttok != NULL) {
		tok = nexttok;
		nexttok = strtok (NULL, "/");
	}
	return tok;
}