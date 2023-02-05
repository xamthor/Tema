#ifndef __FILE_H__
#define __FILE_H__

#define MAX_PATH_LENGTH 1024
#define MAX_NAME_LENGTH 256
#define MAX_SHORT_NAME_LENGTH 64

#define TRANSFER_SIZE 64 * 1024

#define HOME_PATH "home"
#define DIR_UP ".."

enum FileTypes {
    FILE_TYPE_UNKNOWN,
    FILE_TYPE_VPK,
};

enum FileSortFlags {
    SORT_NONE,
    SORT_BY_NAME_AND_FOLDER,
};

enum FileMoveFlags {
    MOVE_INTEGRATE = 0x1, // Integrate directories
    MOVE_REPLACE = 0x2, // Replace files
};

typedef struct {
    uint64_t *value;
    uint64_t max;

    void (*SetProgress)(uint64_t value, uint64_t max);

    int (*cancelHandler)();
} FileProcessParam;

typedef struct FileListEntry {
    struct FileListEntry *next;
    struct FileListEntry *previous;
    char name[MAX_NAME_LENGTH];
    int name_length;
    int is_folder;
    int type;
    SceOff size;
    SceDateTime time;
    int reserved[16];
} FileListEntry;

typedef struct {
    FileListEntry *head;
    FileListEntry *tail;
    int length;
    char path[MAX_PATH_LENGTH];
    int files;
    int folders;
} FileList;

int allocateReadFile(char *file, void **buffer);

int ReadFile(char *file, void *buf, int size);

int WriteFile(char *file, void *buf, int size);

int getFileSize(char *pInputFileName);

int removePath(char *path, FileProcessParam *param);

int copyFile(char *src_path, char *dst_path, FileProcessParam *param);

int copyPath(char *src_path, char *dst_path, FileProcessParam *param);

int movePath(char *src_path, char *dst_path, int flags, FileProcessParam *param);

FileListEntry *fileListFindEntry(FileList *list, char *name);

FileListEntry *fileListGetNthEntry(FileList *list, int n);

int fileListGetNumberByName(FileList *list, char *name);

void fileListAddEntry(FileList *list, FileListEntry *entry, int sort);

int fileListRemoveEntry(FileList *list, FileListEntry *entry);

int fileListRemoveEntryByName(FileList *list, char *name);

void fileListEmpty(FileList *list);

#endif
