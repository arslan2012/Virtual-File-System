//
//  checkCommand.c
//  Virtual File System
//
//  Created by 胡嘉杰 on 16/5/17.
//  Copyright © 2016年 BUPT. All rights reserved.
//

#include "checkCommand.h"
#include <string.h>
int checkCommand(char * command){
    char * a[] = {"man", "exit","su", "create", "mount", "ls","cd","touch","rm","mv","open","unmount"};
    for (int i = 0; i<11; i++) {
        if(strcmp(command,a[i])==0) return i;
    }
    return -1;
}