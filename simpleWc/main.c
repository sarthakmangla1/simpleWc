#include "fileStats.c"
#include "unit_tests.c"

int main(int argc, char** argv){
    
    test_invalid_params();
    test_empty_string();
    test_simple_text();
    test_whitespace_variants();
    test_only_whitespace();
    test_accumulation_behavior();
    test_punctuation_counts_as_word_chars();

    printf("All tests passed.\n");
    return 0;
    
};
