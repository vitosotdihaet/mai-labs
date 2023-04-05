#ifndef DB_H

#define DB_H


#include <stdio.h>

#ifndef DB_SIZE

#define DB_SIZE 5

#endif

typedef struct Database {
    char *name[DB_SIZE];
    char *initials[DB_SIZE];
    short gender[DB_SIZE];
    short school[DB_SIZE];
    short medal[DB_SIZE];
    int points[DB_SIZE];
    short essay[DB_SIZE];
} Database;


void database_init(Database *db);
void database_print(Database db);
void database_add(Database *db);


#endif