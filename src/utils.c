#include "main.h"
#include "file.h"
#include "utils.h"

static int lock_power = 0;

int power_tick_thread(SceSize args, void *argp) {
    while (1) {
        if (lock_power > 0) {
            sceKernelPowerTick(SCE_KERNEL_POWER_TICK_DISABLE_AUTO_SUSPEND);
        }

        sceKernelDelayThread(10 * 1000 * 1000);
    }

    return 0;
}

void initPowerTickThread() {
    SceUID thid = sceKernelCreateThread("power_tick_thread", power_tick_thread, 0x10000100, 0x40000, 0, 0, NULL);
    if (thid >= 0)
        sceKernelStartThread(thid, 0, NULL);
}

void powerLock() {
    lock_power++;
}

void powerUnlock() {
    lock_power--;
    if (lock_power < 0) lock_power = 0;
}

int hasEndSlash(char *path) {
    return path[strlen(path) - 1] == '/';
}

int removeEndSlash(char *path) {
    int len = strlen(path);

    if (path[len - 1] == '/') {
        path[len - 1] = '\0';
        return 1;
    }

    return 0;
}

int addEndSlash(char *path) {
    int len = strlen(path);
    if (len < MAX_PATH_LENGTH - 2) {
        if (path[len - 1] != '/') {
            strcat(path, "/");
            return 1;
        }
    }

    return 0;
}
