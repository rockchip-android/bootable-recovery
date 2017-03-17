/*************************************************************************
	> File Name: rktools.cpp
	> Author: jkand.huang
	> Mail: jkand.huang@rock-chips.com
	> Created Time: Mon 23 Jan 2017 02:36:42 PM CST
 ************************************************************************/

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "sdboot.h"
#include "rktools.h"
#include <fs_mgr.h>
#include "roots.h"
#include "common.h"

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
/**
 * 从/proc/cmdline 获取串口的节点
 *
*/
char *getSerial(){
    char *ans = (char*)malloc(20);
    char param[1024];
    int fd, ret;
    char *s = NULL;
    fd = open("/proc/cmdline", O_RDONLY);
    ret = read(fd, (char*)param, 1024);
    printf("cmdline=%s\n",param);
    s = strstr(param,"console");
    if(s == NULL){
        printf("no found console in cmdline\n");
        free(ans);
        ans = NULL;
        return ans;
    }else{
        s = strstr(s, "=");
        if(s == NULL){
            free(ans);
            ans = NULL;
            return ans;
        }

        strcpy(ans, "/dev/");
        char *str = ans + 5;
        s++;
        while(*s != ' '){
            *str = *s;
            str++;
            s++;
        }
        *str = '\0';
        printf("read console from cmdline is %s\n", ans);
    }

    return ans;
}

/**
 * reset hdmi after restore factory.
*/
int erase_baseparamer() {
    Volume* v = volume_for_path(BASEPARAMER_PARTITION_NAME);
    if (v == NULL) {
        printf("unknown volume baseparamer, not erase baseparamer\n");
        return -1;
    }

    int file;
    file = open(v->blk_device, O_RDWR);
    if (file < 0){
        printf("baseparamer file can not be opened");
        return -1;
    }
    lseek(file, 0L, SEEK_SET);

    //size of baseparamer.
    char buf[BASEPARAMER_PARTITION_SIZE];
    memset(buf, 0, BASEPARAMER_PARTITION_SIZE);

    write(file, (char*)(&buf), BASEPARAMER_PARTITION_SIZE);
    close(file);
    sync();

    return 0;
}
