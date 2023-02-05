#ifndef __PACKAGE_INSTALLER_H__
#define __PACKAGE_INSTALLER_H__

#define ntohl __builtin_bswap32

#define PACKAGE_PARENT "ux0:customtheme/c/common_theme"
#define PACKAGE_DIR PACKAGE_PARENT "/theme"
#define installdircommontheme "ux0:customtheme/c/common_theme"
#define HEAD_BIN PACKAGE_DIR "/sce_sys/package/head.bin"

typedef struct {
    char *file;
} InstallArguments;

int promote(char *path);

int makeHeadBin();

int installPackage(char *file);

#endif
