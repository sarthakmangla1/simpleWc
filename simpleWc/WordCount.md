# simplewc

The objective of this exercise is to implement `simplewc`, a simplified version of the UNIX command `wc`.
`wc` is a command line tool that processes one or multiple filenames as input and prints for each file:
- Number of new lines L
- Number of words     W
- Number of bytes     B
​

When supplied with multiple filenames, the total (sum of each of the L's, W's, and B's) is also printed.
​

For more information on UNIX's `wc`, type the following command in a Linux terminal
`$ man wc`
and try the command using one as well as multiple files.
​
1. Start by defining a C structure `fileStats` with a field for each of the 3 properties (line count, word count, and byte count).
​
2.
	1. Write a function
	`int simplewc_str(const char* str, fileStats* stats);`
	that processes the string `str` and updates the fields of the `stats` structure (by accumulating the values of L, W, and B found in `str`).
​
	2. Write multiple unit tests that exercise this function with valid and invalid parameters.
​
3.
   1. Write a function
   `int simplewc_file(const char* filename, fileStatistics* stats);`
   that reads its input from the file `filename` and uses `simplewc_str` (from the previous step) to update `stats`. This function also prints the file statistics.
​
	2. Write multiple unit tests that exercise this function with valid and invalid parameters.
​
4. Write the main loop of the program
`int simplewc(const char** fileNames, int filesCount);`
that loops over the input files, prints the statistics, and updates a `stats` structure for the total.
​
5. Write the main function of the program
`int main(int argc, char** argv);`
​
6. Update your main to print a help/usage menu when `simplewc` is called with wrong parameters or with the -h option.
​
7. Optional: Write a Shell script or a Python program that
   1. Functionally tests your `simplewc` program with various parameters.
   2. Fuzzes your `simplewc` program (runs it with unexpected parameters and tries to exercise edge cases).
​
8. Provide a Makefile or use CMake to simplify the building of your code.
​
9. Optional/advanced: Use a framework like GoogleTest to simplify the writing and running of your unit tests.
##
Installed Google Tests via Brew