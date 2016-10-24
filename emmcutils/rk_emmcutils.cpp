/*
 * emmcutils.c
 *
 *  Created on: 2013-7-30
 *      Author: mmk@rock-chips.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <fs_mgr.h>
#include "rk_emmcutils.h"
#include "cutils/properties.h"

typedef struct fstab_rec Volume;

int getEmmcState() {
    char bootmode[256];
    int result = 0;

    property_get("ro.bootmode", bootmode, "unknown");
    printf("bootmode = %s \n", bootmode);
    if(!strcmp(bootmode, "emmc")) {
        result = 1;
    }else {
        result = 0;
    }

    return result;
}

int transformPath(const char *in, char *out) {
    int i;
    struct fstab *fstab = NULL;
    char *name_fstab = "/fstab.rk30board";

    if(in == NULL || out == NULL) {
        printf("transformPath argument can't be NULL\n");
        return -1;
    }
    printf("transformPath in: %s\n", in);
    if(fstab == NULL) {
        fstab = fs_mgr_read_fstab(name_fstab);
        if (!fstab) {
            printf("failed to read android.fstab\n");
            return -1;
        }
    }
    printf("android filesystem table\n");
    for (i = 0; i < fstab->num_entries; ++i) {
        Volume* v = &fstab->recs[i];
        printf("  %d %s %s %s %lld\n", i, v->mount_point, v->fs_type, v->blk_device, v->length);
        if(strcmp(v->mount_point, "/system") == 0){
            int len = strlen(v->blk_device);
            strncpy(out, v->blk_device, len-6);
            *(out + len - 6) = '\0';
        }
    }

    printf("\n");

    fs_mgr_free_fstab(fstab);
    strcat(out, in);
    printf("transformPath out: %s\n", out);

    return 0;
}




