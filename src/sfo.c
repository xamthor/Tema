#include "main.h"
#include "archive.h"
#include "file.h"
#include "utils.h"
#include "sfo.h"

int getSfoValue(void *buffer, char *name, uint32_t *value) {
    SfoHeader *header = (SfoHeader *) buffer;
    SfoEntry *entries = (SfoEntry *) ((uint32_t) buffer + sizeof(SfoHeader));

    if (header->magic != SFO_MAGIC)
        return -1;

    int i;
    for (i = 0; i < header->count; i++) {
        if (strcmp(buffer + header->keyofs + entries[i].nameofs, name) == 0) {
            *value = *(uint32_t * )(buffer + header->valofs + entries[i].dataofs);
            return 0;
        }
    }

    return -2;
}

int getSfoString(void *buffer, char *name, char *string, int length) {
    SfoHeader *header = (SfoHeader *) buffer;
    SfoEntry *entries = (SfoEntry *) ((uint32_t) buffer + sizeof(SfoHeader));

    if (header->magic != SFO_MAGIC)
        return -1;

    int i;
    for (i = 0; i < header->count; i++) {
        if (strcmp(buffer + header->keyofs + entries[i].nameofs, name) == 0) {
            memset(string, 0, length);
            strncpy(string, buffer + header->valofs + entries[i].dataofs, length);
            string[length - 1] = '\0';
            return 0;
        }
    }

    return -2;
}

int setSfoValue(void *buffer, char *name, uint32_t value) {
    SfoHeader *header = (SfoHeader *) buffer;
    SfoEntry *entries = (SfoEntry *) ((uint32_t) buffer + sizeof(SfoHeader));

    if (header->magic != SFO_MAGIC)
        return -1;

    int i;
    for (i = 0; i < header->count; i++) {
        if (strcmp(buffer + header->keyofs + entries[i].nameofs, name) == 0) {
            *(uint32_t * )(buffer + header->valofs + entries[i].dataofs) = value;
            return 0;
        }
    }

    return -2;
}

int setSfoString(void *buffer, char *name, char *string) {
    SfoHeader *header = (SfoHeader *) buffer;
    SfoEntry *entries = (SfoEntry *) ((uint32_t) buffer + sizeof(SfoHeader));

    if (header->magic != SFO_MAGIC)
        return -1;

    int i;
    for (i = 0; i < header->count; i++) {
        if (strcmp(buffer + header->keyofs + entries[i].nameofs, name) == 0) {
            strcpy(buffer + header->valofs + entries[i].dataofs, string);
            return 0;
        }
    }

    return -2;
}
