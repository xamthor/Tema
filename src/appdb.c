#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "appdb.h"

#define APP_DB "ur0:shell/db/app.db"

static int get_applist_callback(void *data, int argc, char **argv, char **cols) {
    applist *list = (applist *) data;
    appinfo *info = malloc(sizeof(appinfo));
    memset(info, 0, sizeof(appinfo));
    if (list->count == 0) {
        list->items = info;
    } else {
        appinfo *tmp = list->items;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = info;
        info->prev = tmp;
    }
    list->count += 1;
    strcpy(info->title_id, argv[0]);
    strcpy(info->real_id, argv[1]);
    strcpy(info->title, argv[2]);
    strcpy(info->eboot, argv[3]);
    strcpy(info->dev, argv[4]);
    for (int i = 0; i < 256; i++) {
        if (info->title[i] == '\n') {
            info->title[i] = ' ';
        }
    }
    return 0;
}

int get_applist(applist *list) {
    char *query = "select id as col1, '2' as col2, '3' as col3, '4 as col4',"
                  "       '5' as col5"
                  "  FROM tbl_theme";
    //"  WHERE id NOT IN ('ux0:customtheme/c/common_theme')";

    sqlite3 *db;
    int ret = sqlite3_open(APP_DB, &db);
    if (ret) {
        return -1;
    }
    char *errMsg;
    ret = sqlite3_exec(db, query, get_applist_callback, (void *) list, &errMsg);
    if (ret != SQLITE_OK) {
        sqlite3_close(db);
        return -2;
    }
    sqlite3_close(db);

    if (list->count <= 0) {
        return -3;
    }
    return 0;
}
