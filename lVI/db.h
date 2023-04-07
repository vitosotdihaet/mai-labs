#ifndef DB_H
#define DB_H

typedef struct Database {
    unsigned long long size;
    char **name;
    char **initials;
    short *gender;
    short *school;
    short *medal;
    short *points;
    short *essay;
} Database;

void database_init(Database *db, unsigned long long size);
void database_dump(Database db, FILE *f);
void database_read(Database *db, FILE *f);
void database_print(Database db);
void database_add
(
    Database *db,
    char const *name[], char const *initials[],
    short gender, short school, short medal, short points, short essay
);
void database_add_stdin(Database *db);

#endif