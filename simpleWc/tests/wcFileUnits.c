/*
 * wcFileUnits.c
 *
 * Unit tests exercising simplewc_file() from fileStats.c.  These tests
 * create temporary files on disk to verify that the implementation
 * correctly handles various scenarios.  To run all tests call
 * run_wcFileTests().
 */

#include "../fileStats.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

/* ---------- helper functions ---------- */
static void stats_zero(fileStats *s) {
    s->lines = 0;
    s->words = 0;
    s->bytes = 0;
}

static void write_text_file(const char *filename, const char *text) {
    FILE *f = fopen(filename, "wb");
    assert(f != NULL);
    if (text != NULL) {
        size_t n = fwrite(text, 1, strlen(text), f);
        assert(n == strlen(text));
    }
    assert(fclose(f) == 0);
}

static const char *make_name(int i, char *buf, size_t bufsz) {
    snprintf(buf, bufsz, "test_simplewc_%d.txt", i);
    return buf;
}

/* ---------- test functions ---------- */
static void test_null_args(void) {
    fileStats s;
    stats_zero(&s);
    errno = 0;
    assert(simplewc_file(NULL, &s) == -1);
    errno = 0;
    assert(simplewc_file("anything.txt", NULL) == -1);
}

static void test_nonexistent_file(void) {
    fileStats s;
    stats_zero(&s);
    errno = 0;
    /* Use a file name that should not exist */
    assert(simplewc_file("this_file_should_not_exist_12345.txt", &s) == -1);
    assert(errno == ENOENT);
}

static void test_empty_file(void) {
    char name[64];
    make_name(1, name, sizeof(name));
    write_text_file(name, "");
    fileStats s;
    stats_zero(&s);
    assert(simplewc_file(name, &s) == 0);
    assert(s.lines == 0);
    assert(s.words == 0);
    assert(s.bytes == 0);
    remove(name);
}

static void test_basic(void) {
    /* "hello world\n"
     * bytes = 12 (5+1+5+1), lines=1, words=2
     */
    char name[64];
    make_name(2, name, sizeof(name));
    write_text_file(name, "hello world\n");
    fileStats s;
    stats_zero(&s);
    assert(simplewc_file(name, &s) == 0);
    assert(s.lines == 1);
    assert(s.words == 2);
    assert(s.bytes == 12);
    remove(name);
}

static void test_whitespace_heavy(void) {
    /*
     * "a  b\n\tc\n\n"
     * bytes: 'a'(1)+"  "(2)+'b'(1)+'\n'(1)+ '\t'(1)+'c'(1)+'\n'(1)+'\n'(1) = 9
     * lines: 3
     * words: a,b,c => 3
     */
    char name[64];
    make_name(3, name, sizeof(name));
    write_text_file(name, "a  b\n\tc\n\n");
    fileStats s;
    stats_zero(&s);
    assert(simplewc_file(name, &s) == 0);
    assert(s.lines == 3);
    assert(s.words == 3);
    assert(s.bytes == 9);
    remove(name);
}

static void test_no_trailing_newline(void) {
    /* "one two" -> bytes=7, lines=0, words=2 */
    char name[64];
    make_name(4, name, sizeof(name));
    write_text_file(name, "one two");
    fileStats s;
    stats_zero(&s);
    assert(simplewc_file(name, &s) == 0);
    assert(s.lines == 0);
    assert(s.words == 2);
    assert(s.bytes == 7);
    remove(name);
}

static void test_accumulates_into_existing_stats(void) {
    /* If stats already has values, simplewc_file should add to them */
    char name[64];
    make_name(5, name, sizeof(name));
    write_text_file(name, "x y\n"); /* bytes=4, lines=1, words=2 */
    fileStats s;
    s.lines = 10;
    s.words = 20;
    s.bytes = 30;
    assert(simplewc_file(name, &s) == 0);
    assert(s.lines == 11);
    assert(s.words == 22);
    assert(s.bytes == 34);
    remove(name);
}

static void test_two_files_like_real_wc(void) {
    /* simulate calling simplewc_file twice like a multi‑file wc */
    char n1[64], n2[64];
    make_name(6, n1, sizeof(n1));
    make_name(7, n2, sizeof(n2));
    write_text_file(n1, "a b\n");     /* bytes=4 lines=1 words=2 */
    write_text_file(n2, "c\nd e\n");  /* bytes=6 lines=2 words=3 */
    fileStats s;
    stats_zero(&s);
    assert(simplewc_file(n1, &s) == 0);
    assert(simplewc_file(n2, &s) == 0);
    assert(s.lines == 3);
    assert(s.words == 5);
    assert(s.bytes == 10);
    remove(n1);
    remove(n2);
}

/*
 * run_wcFileTests
 *
 * Execute all file‑based unit tests.  If all assertions hold, a
 * confirmation message is printed.
 */
void run_wcFileTests(void) {
    test_null_args();
    test_nonexistent_file();
    test_empty_file();
    test_basic();
    test_whitespace_heavy();
    test_no_trailing_newline();
    test_accumulates_into_existing_stats();
    test_two_files_like_real_wc();
    printf("All file tests passed.\n");
}
