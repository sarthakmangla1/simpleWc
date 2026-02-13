#include "fileStats.c"
#include "tests/wcStrUnits.c"
#include "tests/wcFileUnits.c"

int main(int argc, char** argv){
    
    test_invalid_params();
    test_empty_string();
    test_simple_text();
    test_whitespace_variants();
    test_only_whitespace();
    test_accumulation_behavior();
    test_punctuation_counts_as_word_chars();

    // test_null_args();
    // test_nonexistent_file();
    // test_empty_file();
    // test_basic();
    // test_whitespace_heavy();
    // test_no_trailing_newline();
    // test_accumulates_into_existing_stats();
    // test_two_files_like_real_wc();

    printf("All tests passed.\n");
    return 0;
    
};
