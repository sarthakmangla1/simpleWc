extern "C" {
  #include "../fileStats.h"
  }
  #include <gtest/gtest.h>
  #include <cstdio>
  #include <cerrno>
  #include <cstring>

  // helper
  static void write_file(const char *path, const char *text) {
      FILE *f = fopen(path, "wb");
      ASSERT_NE(f, nullptr);
      if (text) fwrite(text, 1, strlen(text), f);
      fclose(f);
  }

  TEST(FileStats, NullArgs) {
      fileStats s{};
      EXPECT_EQ(simplewc_file(nullptr, &s), -1);
      EXPECT_EQ(simplewc_file("anything.txt", nullptr), -1);
  }

  TEST(FileStats, NonexistentFile) {
      fileStats s{};
      errno = 0;
      EXPECT_EQ(simplewc_file("no_such_file_12345.txt", &s), -1);
      EXPECT_EQ(errno, ENOENT);
  }

  TEST(FileStats, EmptyFile) {
      const char *path = "/tmp/gtest_empty.txt";
      write_file(path, "");
      fileStats s{};
      EXPECT_EQ(simplewc_file(path, &s), 0);
      EXPECT_EQ(s.lines, 0); EXPECT_EQ(s.words, 0); EXPECT_EQ(s.bytes, 0);
      remove(path);
  }

  TEST(FileStats, Basic) {
      const char *path = "/tmp/gtest_basic.txt";
      write_file(path, "hello world\n");
      fileStats s{};
      EXPECT_EQ(simplewc_file(path, &s), 0);
      EXPECT_EQ(s.lines, 1); EXPECT_EQ(s.words, 2); EXPECT_EQ(s.bytes, 12);
      remove(path);
  }