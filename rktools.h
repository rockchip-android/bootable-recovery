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

#define NET_FILE_PATH          "./sys/class/net_cmcc_gpio/net_cmcc_led"
#define NET_FILE_PATH_NEW      "/sys/class/leds/net-green/brightness"
#define KETGRUND_FILE_PATH     "./sys/class/ir_cmcc_gpio/ir_cmcc_led"
#define POWER_FILE_PATH        "./sys/class/suspend_cmcc_gpio/suspend_cmcc_led"

#define OFF_VALUE 0
#define ON_VALUE 1

#define EMMC_POINT_NAME "emmc_point_name"
#define EMMC_POINT_0 "/dev/block/mmcblk0"
#define EMMC_POINT_1 "/dev/block/mmcblk1"
#define SD_POINT_0 "/dev/block/mmcblk0"
#define SD_POINT_1 "/dev/block/mmcblk1"

char* check_media_package(const char *path);
char* getSerial();
int erase_baseparamer();
void startLed();
void stopLed(int state);
void setFlashPoint();
#endif
