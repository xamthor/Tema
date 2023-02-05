#ifndef __ARCHIVE_H__
#define __ARCHIVE_H__

#include "file.h"

#define ARCHIVE_FD 0x12345678

int fileListGetArchiveEntries(FileList *list, char *path);

int getArchivePathInfo(char *path, uint64_t *size, uint32_t *folders, uint32_t *files);

int extractArchivePath(char *src, char *dst, FileProcessParam *param);

int archiveFileGetstat(const char *file, SceIoStat *stat);

int archiveFileOpen(const char *file, int flags, SceMode mode);

int archiveFileRead(SceUID fd, void *data, SceSize size);

int archiveFileClose(SceUID fd);

int ReadArchiveFile(char *file, void *buf, int size);

int archiveClose();

int archiveOpen(char *file);

#endif
