#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "db.h"

void database_init(Database *db, unsigned long long size) {
    db->size = size;
    db->name = (char**) calloc(size, sizeof(char**));
    db->initials = (char*) calloc(size, sizeof(char*));
    db->gender = (short*) calloc(size, sizeof(short*));
    db->school = (short*) calloc(size, sizeof(short*));
    db->medal = (short*) calloc(size, sizeof(short*));
    db->points = (short*) calloc(size, sizeof(short*));
    db->essay = (short*) calloc(size, sizeof(short*));

    for (unsigned long long i = 0; i < size; ++i) {
        db->name[i] = (char*) calloc(15, sizeof(char*));
        db->initials[i] = (char*) calloc(10, sizeof(char*));
        db->gender[i] = -1;
        db->school[i] = -1;
        db->medal[i] = -1;
        db->points[i] = -1;
        db->essay[i] = -1;
    }
}

void database_dump(Database db, FILE *f) {
    fwrite(&db.size, sizeof(unsigned long long), 1, f);
    for (unsigned long long i = 0; i < db.size; ++i) {
        if (db.essay == -1) break;
        fwrite("\n", sizeof(char), 1, f);

        int for_name = strlen(db.name[i]);
        for (int _ = for_name; _ < 15; ++_) {
            fwrite(" ", sizeof(char), 1, f);
        }
        fwrite(db.name[i], for_name, 1, f);

        int for_initials = strlen(db.initials[i]);
        for (int _ = for_initials; _ < 10; ++_) {
            fwrite(" ", sizeof(char), 1, f);
        }
        fwrite(db.initials[i], for_initials, 1, f);

        fwrite(&db.gender[i], sizeof(short), 1, f);
        fwrite(&db.school[i], sizeof(short), 1, f);
        fwrite(&db.medal[i],  sizeof(short), 1, f);
        fwrite(&db.points[i], sizeof(short), 1, f);
        fwrite(&db.essay[i],  sizeof(short), 1, f);
    }
}

void database_read(Database *db, FILE *f) {
    fread(&db->size, sizeof(unsigned long long), 1, f);
    database_init(db, db->size);

    char *buf = (char*) calloc(1, sizeof(char));
    for (unsigned long long i = 0; i < db->size; ++i) {
        fread(buf, sizeof(char), 1, f);

        fread(db->name[i], sizeof(char), 15, f);

        fread(db->initials[i], sizeof(char), 10, f);

        fread(&db->gender[i], sizeof(short), 1, f);
        fread(&db->school[i], sizeof(short), 1, f);
        fread(&db->medal[i],  sizeof(short), 1, f);
        fread(&db->points[i], sizeof(short), 1, f);
        fread(&db->essay[i],  sizeof(short), 1, f);
    }
}

void database_print(Database db) {
    printf(
            "Name            |"
            "Initials   |"
            "Gender     |"
            "School     |"
            "Medal      |"
            "Points     |"
            "Essay      |"
            "\n"
        );

    for (unsigned long long i = 0; i < db.size; ++i) {
        printf("%16s|" , db.name[i]);
        printf("%11s|" , db.initials[i]);
        printf("%11hd|", db.gender[i]);
        printf("%11hd|", db.school[i]);
        printf("%11hd|", db.medal[i]);
        printf("%11hd|" , db.points[i]);
        printf("%11hd|", db.essay[i]);
        printf("\n");
    }
}

void database_add
(
    Database *db,
    char const *name[], char const *initials[],
    short gender, short school, short medal, short points, short essay
) {
    unsigned long long i;
    for (i = 0; i < db->size; ++i) {
        if (db->essay[i] == -1) break;
    }

    if (i == db->size - 1) {
        printf("No space left!\n");
        return;
    }

    db->name[i] = name;
    db->initials[i] = initials;
    db->gender[i] = gender;
    db->school[i] = school;
    db->medal[i] = medal;
    db->points[i] = points;
    db->essay[i] = essay;
}

void database_add_stdin(Database *db) {
    unsigned long long i;
    for (i = 0; i < db->size; ++i) {
        if (db->essay[i] == -1) break;
    }

    if (i == db->size - 1) {
        printf("No space left!\n");
        return;
    }

    printf("Adding to database...\n");

    printf("Input name: ");
    scanf("%s", db->name[i]);

    printf("Input initials: ");
    scanf("%s", db->initials[i]);

    printf("Input gender (0 - male, 1 - female): ");
    scanf("%hd", &db->gender[i]);

    printf("Input school number: ");
    scanf("%hd", &db->school[i]);

    printf("Input medal (0 - no medal, 1 - has medal): ");
    scanf("%hd", &db->medal[i]);

    printf("Input points: ");
    scanf("%hd", &db->points[i]);

    printf("Input essay (0 - no essay, 1 - has essay): ");
    scanf("%hd", &db->essay[i]);
}
