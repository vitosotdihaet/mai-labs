#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#include "db.h"

void database_init(Database *db, unsigned long long size) {
    db->size = size;
    db->name = (char**) calloc(size, sizeof(char*));
    db->initials = (char**) calloc(size, sizeof(char*));
    db->gender = (short*) calloc(size, sizeof(short));
    db->school = (short*) calloc(size, sizeof(short));
    db->medal = (short*) calloc(size, sizeof(short));
    db->points = (short*) calloc(size, sizeof(short));
    db->essay = (short*) calloc(size, sizeof(short));

    for (unsigned long long i = 0; i < size; ++i) {
        db->name[i] = (char*) calloc(15, sizeof(char));
        db->initials[i] = (char*) calloc(10, sizeof(char));
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
        if (db.essay[i] == -1) break;
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


void database_print_header() {
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
}

void database_print_row(Database db, unsigned long long i) {
    printf("%16s|" , db.name[i]);
    printf("%11s|" , db.initials[i]);
    printf("%11hd|", db.gender[i]);
    printf("%11hd|", db.school[i]);
    printf("%11hd|", db.medal[i]);
    printf("%11hd|" , db.points[i]);
    printf("%11hd|", db.essay[i]);
    printf("\n");
}

void database_print(Database db) {
    database_print_header();

    for (unsigned long long i = 0; i < db.size; ++i) {
        database_print_row(db, i);
    }
}

void database_print_all_min(Database db, char *field, short min) {
    short g = 0, s = 0, m = 0, p = 0, e = 0; // every single field

    switch (tolower(field[0])) {
        case 'g': g = 1; break;
        case 's': s = 1; break;
        case 'm': m = 1; break;
        case 'p': p = 1; break;
        case 'e': e = 1; break; 
    }

    if (g == s && s == m && m == p && p == e) { // can't be all 1 because of switch case
        printf("No field with such name!\n");
        return;
    }

    database_print_header();

    for (unsigned long long i = 0; i < db.size; ++i) {
        if (db.essay[i] != -1 &&
            (
                (g && db.gender[i] >= min) || (s && db.school[i] >= min) ||
                (m && db.medal[i] >= min)  || (p && db.points[i] >= min) ||
                (e && db.essay[i] >= min)
            )
        ) database_print_row(db, i);
    }
}

void database_print_all_max(Database db, char *field, short max) {
    short g = 0, s = 0, m = 0, p = 0, e = 0; // every single field

    switch (tolower(field[0])) {
        case 'g': g = 1; break;
        case 's': s = 1; break;
        case 'm': m = 1; break;
        case 'p': p = 1; break;
        case 'e': e = 1; break; 
    }

    if (g == s && s == m && m == p && p == e) { // can't be all 1 because of switch case
        printf("No field with such name!\n");
        return;
    }

    database_print_header();

    for (unsigned long long i = 0; i < db.size; ++i) {
        if (db.essay[i] != -1 &&
            (
                (g && db.gender[i] < max) || (s && db.school[i] < max) ||
                (m && db.medal[i] < max)  || (p && db.points[i] < max) ||
                (e && db.essay[i] < max)
            )
        ) database_print_row(db, i);
    }
}


void database_add
(
    Database *db,
    char *name, char *initials,
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
