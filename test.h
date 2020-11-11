#ifndef TESTS_PISCINE
#define TESTS_PISCINE

// Flags for arrays of chars
#define NOFLAG 	0
#define ALPHA 	(1 << 0)
#define NUMBER	(1 << 1)
#define PRINT 	(1 << 2)
#define STRING 	(1 << 3)

// Flags for ints
#define SIGNED		0
#define UNSIGNED 	(1 << 0)
#define ALLRANGE 	(1 << 1)

// Nice macro to change test number (piscinator used in correction vs for us)
//#define TEST_NUMBER 100
//#define MAX_LENGTH 20

// Generate int or unsigned int ?

// Print char
void ft_putchar(char c);

// Print str
void ft_putstr(char* str);

// Print hexa of char if non printable
void ft_putchar_non_printable(char c);

// Print hexa of char if non printable
void ft_putstr_non_printable(char* str);

// Print n
void ft_putnbr(int n);

// Pretty print array
void ft_chararray(char* array, int n);

// Initialize random number generator
void initialize();

unsigned char alea_char(unsigned char flags);

// Generate byte array (use with STRING)
char *alea_array(int size, unsigned int flags);

// Makes array of more than number arrays of chars (including about 10 test cases). Only last element is NULL. 
char **test_arrays(int number, int size, unsigned int flags);

// Makes array of more than number strings of chars (including about 10 test cases). Only last element is NULL. 
char **test_strings(int number, int max_length, unsigned int flags);

// Makes array of number integers (including 0, 1, -1, INT_MIN and INT_MAX)
int *test_ints(int number);

// Makes array of number unsigned integers (including 0, 1,and UINT_MAX if within limits min and max
int *test_unsigned_ints_from_to(int number, int min, int max);

// Makes array of number integers (including 0, 1, -1, INT_MIN and INT_MAX) if within limits min and max
int *test_ints_from_to(int number, int min, int max, unsigned int flags);

#endif
