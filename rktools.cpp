/*************************************************************************
	> File Name: rktools.cpp
	> Author: jkand.huang
	> Mail: jkand.huang@rock-chips.com
	> Created Time: Mon 23 Jan 2017 02:36:42 PM CST
 ************************************************************************/

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "sdboot.h"
#include "rktools.h"
using namespace std;
char* check_media_package(const char *path){
    char *reallyPath;
    SDBoot mountDevice;

    if(strncmp(path, "/mnt/external_sd", 16) == 0){
        mountDevice.ensure_sd_mounted();
    }else if(strncmp(path, "/mnt/usb_storage", 16) == 0){
        mountDevice.ensure_usb_mounted();
    }

    if(strncmp(path, "/mnt/media_rw", 13) == 0){
        printf("start to find package in /mnt/usb_storage/ .\n");
        reallyPath = (char*)malloc(PATH_LEN);
        mountDevice.ensure_usb_mounted();
        memset(reallyPath, 0, PATH_LEN);
        strcpy(reallyPath, usb_path);

        char *filename = strstr(path, "update.zip");
        if(filename == NULL)
            filename = strstr(path, "update.img");
        if(filename == NULL){
            printf("check_media_package: filename is null\n");
            free(reallyPath);
            reallyPath = NULL;
            return NULL;
        }

        strcat(reallyPath, filename); 
        if((access(reallyPath, F_OK))==0)
        {
            printf("check_media_package: find package ok is %s.\n", reallyPath);
            return reallyPath;
        }
        
        mountDevice.ensure_sd_mounted();
        memset(reallyPath, 0, PATH_LEN);
        strcpy(reallyPath, sd_path);
        strcat(reallyPath, filename);
        if((access(reallyPath, F_OK))==0)
        {
            printf("check_media_package: find package ok is %s.\n", reallyPath);
            return reallyPath;
        }
        free(reallyPath);
        reallyPath = NULL;
    }

    return NULL;
}
