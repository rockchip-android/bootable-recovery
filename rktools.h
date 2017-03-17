/*************************************************************************
	> File Name: rktools.h
	> Author: jkand.huang
	> Mail: jkand.huang@rock-chips.com
	> Created Time: Mon 23 Jan 2017 03:05:58 PM CST
 ************************************************************************/

#ifndef _RKTOOLS_H
#define _RKTOOLS_H
#define PATH_LEN 50
#define usb_path "/mnt/usb_storage/"
#define sd_path "/mnt/external_sd/"
#define BASEPARAMER_PARTITION_NAME "/baseparamer"
#define BASEPARAMER_PARTITION_SIZE 1024
char* check_media_package(const char *path);
char* getSerial();
int erase_baseparamer();
#endif
