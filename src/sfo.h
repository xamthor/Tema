#ifndef __SFO_H__
#define __SFO_H__

#define SFO_MAGIC 0x46535000

#define PSF_TYPE_BIN 0
#define PSF_TYPE_STR 2
#define PSF_TYPE_VAL 4

typedef struct SfoHeader {
    uint32_t magic;
    uint32_t version;
    uint32_t keyofs;
    uint32_t valofs;
    uint32_t count;
} __attribute__((packed)) SfoHeader;

typedef struct SfoEntry {
    uint16_t nameofs;
    uint8_t alignment;
    uint8_t type;
    uint32_t valsize;
    uint32_t totalsize;
    uint32_t dataofs;
} __attribute__((packed)) SfoEntry;

int getSfoValue(void *buffer, char *name, uint32_t *value);

int getSfoString(void *buffer, char *name, char *string, int length);

int setSfoValue(void *buffer, char *name, uint32_t value);

int setSfoString(void *buffer, char *name, char *string);

#endif
