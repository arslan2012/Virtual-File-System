//
//  ifdir.c
//  Virtual File System
//
//  Created by ئ‍ارسلان ئابلىكىم on 4/6/16.
//  Copyright © 2016 BUPT. All rights reserved.
//

#include "ifdir.h"
bool ifdir(char * arg){
    int i = 0;
    while (arg[i]!='\0') i++;
    if (arg[i-1]=='/') return true;
    else return false;
}