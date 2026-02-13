#include "fileStats.h"
/* ---------------- Unit tests ---------------- */

static void test_invalid_params(void) {
    fileStats s = {0, 0, 0};
    assert(simplewc_str(NULL, &s) == -1);
    assert(simplewc_str("abc", NULL) == -1);
}

static void test_empty_string(void) {
    fileStats s = {0, 0, 0};
    assert(simplewc_str("", &s) == 0);
    assert(s.lines == 0);
    assert(s.words == 0);
    assert(s.bytes == 0);
}

static void test_simple_text(void) {
    fileStats s = {0, 0, 0};
    assert(simplewc_str("Hello World", &s) == 0);
    assert(s.lines == 0);
    assert(s.words == 2);
    assert(s.bytes == 11); // "Hello"(5) + space(1) + "World"(5)
}

static void test_whitespace_variants(void) {
    fileStats s = {0, 0, 0};
    assert(simplewc_str("  \tHello \nWorld  \n", &s) == 0);
    // Count '\n': there are 2 newline characters
    assert(s.lines == 2);
    // Words: Hello, World => 2
    assert(s.words == 2);
    // Bytes: count characters exactly
    assert(s.bytes == (long)strlen("  \tHello \nWorld  \n"));
}

static void test_only_whitespace(void) {
    fileStats s = {0, 0, 0};
    assert(simplewc_str(" \t\n\n  ", &s) == 0);
    assert(s.lines == 2);
    assert(s.words == 0);
    assert(s.bytes == (long)strlen(" \t\n\n  "));
}

static void test_accumulation_behavior(void) {
    fileStats s = {0, 0, 0};

    assert(simplewc_str("a b", &s) == 0);
    assert(s.words == 2);
    assert(s.lines == 0);
    assert(s.bytes == 3);

    assert(simplewc_str("\nccc", &s) == 0);
    // Second string: lines += 1, words += 1 ("ccc"), bytes += 4
    assert(s.lines == 1);
    assert(s.words == 3);
    assert(s.bytes == 7);
}

static void test_punctuation_counts_as_word_chars(void) {
    fileStats s = {0, 0, 0};
    assert(simplewc_str("hi,there!!  ok", &s) == 0);
    // Commas/exclamations are not whitespace => still part of words
    // "hi,there!!" and "ok" => 2 words
    assert(s.words == 2);
    assert(s.lines == 0);
    assert(s.bytes == (long)strlen("hi,there!!  ok"));
}