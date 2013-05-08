#include <check.h>
#include <stdio.h>
#include <fcntl.h>
#include "art.h"

START_TEST(test_art_init_and_destroy)
{
    art_tree t;
    int res = init_art_tree(&t);
    fail_unless(res == 0);

    fail_unless(art_size(&t) == 0);

    res = destroy_art_tree(&t);
    fail_unless(res == 0);
}
END_TEST

START_TEST(test_art_insert)
{
    art_tree t;
    int res = init_art_tree(&t);
    fail_unless(res == 0);

    int len;
    char buf[512];
    FILE *f = fopen("tests/words.txt", "r");

    int line = 1;
    while (fgets(buf, sizeof buf, f)) {
        len = strlen(buf);
        buf[len-1] = '\0';
        fail_unless(NULL == art_insert(&t, buf, len, (void*)(uintptr_t)line));
        fail_unless(art_size(&t) == line);
        line++;
    }

    res = destroy_art_tree(&t);
    fail_unless(res == 0);
}
END_TEST

START_TEST(test_art_insert_search)
{
    art_tree t;
    int res = init_art_tree(&t);
    fail_unless(res == 0);

    int len;
    char buf[512];
    FILE *f = fopen("tests/words.txt", "r");

    int line = 1;
    while (fgets(buf, sizeof buf, f)) {
        len = strlen(buf);
        buf[len-1] = '\0';
        fail_unless(NULL ==
            art_insert(&t, buf, len, (void*)(uintptr_t)line));
        line++;
    }

    // Seek back to the start
    fseek(f, 0, SEEK_SET);

    // Search for each line
    line = 1;
    while (fgets(buf, sizeof buf, f)) {
        len = strlen(buf);
        buf[len-1] = '\0';

        void *val = art_search(&t, buf, len);
        if (line != (uintptr_t)val) {
            printf("Line: %d Val: %d Str: %s\n", line, (int)(uintptr_t)val, buf);
        }
        fail_unless(line == (uintptr_t)val);
        line++;
    }

    // Check the minimum
    art_leaf *l = art_minimum(&t);
    fail_unless(l && strcmp((char*)l->key, "A") == 0);

    // Check the maximum
    l = art_maximum(&t);
    fail_unless(l && strcmp((char*)l->key, "zythum") == 0);

    res = destroy_art_tree(&t);
    fail_unless(res == 0);
}
END_TEST

START_TEST(test_art_insert_delete)
{
    art_tree t;
    int res = init_art_tree(&t);
    fail_unless(res == 0);

    int len;
    char buf[512];
    FILE *f = fopen("tests/words.txt", "r");

    int line = 1;
    while (fgets(buf, sizeof buf, f)) {
        len = strlen(buf);
        buf[len-1] = '\0';
        fail_unless(NULL ==
            art_insert(&t, buf, len, (void*)(uintptr_t)line));
        line++;
    }

    // Seek back to the start
    fseek(f, 0, SEEK_SET);

    // Search for each line
    line = 1;
    while (fgets(buf, sizeof buf, f)) {
        len = strlen(buf);
        buf[len-1] = '\0';

        // Search first, ensure all entries still
        // visible
        void *val = art_search(&t, buf, len);
        if (line != (uintptr_t)val) {
            printf("Line: %d Val: %d Str: %s\n", line, (int)(uintptr_t)val, buf);
        }
        fail_unless(line == (uintptr_t)val);

        // Delete, should get lineno back
        val = art_delete(&t, buf, len);
        if (line != (uintptr_t)val) {
            printf("Line: %d Val: %d Str: %s\n", line, (int)(uintptr_t)val, buf);
        }
        fail_unless(line == (uintptr_t)val);

        // Check the size
        fail_unless(art_size(&t) == 235886 - line);
        line++;
    }

    // Check the minimum and maximum
    fail_unless(!art_minimum(&t));
    fail_unless(!art_maximum(&t));

    res = destroy_art_tree(&t);
    fail_unless(res == 0);
}
END_TEST

