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

void database_print_header();
void database_print_row(Database db, unsigned long long i);
void database_print(Database db);
void database_print_all_min(Database db, char *field, short min);
void database_print_all_max(Database db, char *field, short max);

void database_add
(
    Database *db,
    char *name, char *initials,
    short gender, short school, short medal, short points, short essay
);
void database_add_stdin(Database *db);


#endif