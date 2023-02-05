#include "main.h"

void initSceAppUtil() {
    // Init SceAppUtil
    SceAppUtilInitParam init_param;
    SceAppUtilBootParam boot_param;
    memset(&init_param, 0, sizeof(SceAppUtilInitParam));
    memset(&boot_param, 0, sizeof(SceAppUtilBootParam));
    sceAppUtilInit(&init_param, &boot_param);
}

void finishSceAppUtil() {
    // Shutdown AppUtil
    sceAppUtilShutdown();
}
