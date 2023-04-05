#include "db.h"

#define DEFAULT_STRING "         _"

void database_init(Database *db) {
    for (int i = 0; i < DB_SIZE; ++i) {
        db->name[i] = DEFAULT_STRING;
        db->initials[i] = DEFAULT_STRING;
        db->gender[i] = -1;
        db->school[i] = -1;
        db->medal[i] = -1;
        db->points[i] = -1;
        db->essay[i] = -1;
    }
}

void database_print(Database db) {
    printf(
            "Name       |"
            "Initials   |"
            "Gender     |"
            "School     |"
            "Medal      |"
            "Points     |"
            "Essay      |"
            "\n"
        );

    for (int i = 0; i < DB_SIZE; ++i) {
        printf("%11s|" , db.name[i]);
        printf("%11s|" , db.initials[i]);
        printf("%11hd|", db.gender[i]);
        printf("%11hd|", db.school[i]);
        printf("%11hd|", db.medal[i]);
        printf("%11d|" , db.points[i]);
        printf("%11hd|", db.essay[i]);
        printf("\n");
    }
}

void database_add(Database *db) {
    for (int i = 0; i < DB_SIZE; ++i) {
        if (db->essay[i] != -1) continue;
        printf("Input info:\n");

        printf("Input name: ");
        scanf("%s", &db->name[i]);

        printf("Input initial: ");
        scanf("%s", &db->initials[i]);

        printf("Input gender (0 - male, 1 - female): ");
        scanf("%hd", &db->gender[i]);

        printf("Input school number: ");
        scanf("%hd", &db->school[i]);

        printf("Input medal (0 - doesn't have medal, 1 - has medal): ");
        scanf("%hd", &db->medal[i]);

        printf("Input points: ");
        scanf("%d", &db->points[i]);

        printf("Input essay (0 - doesn't have essay, 1 - has essay): ");
        scanf("%hd", &db->essay[i]);
        return;
    }
    printf("No space left!\n");
}
