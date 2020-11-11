#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include "test.h"

size_t	ft_strlen(const char* s);
char 	*ft_strcpy(char *dest, const char *src);
int		ft_strcmp(const char *s1, const char *s2);
ssize_t	ft_write(int fd, const void *s, size_t n);

int		main() {
	int fail = 0;
	int i;
	int test_number = 1000;
	int max_length = 50;
	char dest_std[51];
	char *ret, *ret_std;
	size_t ret_sizet, ret_std_d;
	int ret_int, ret_std_int;
	initialize();
	char** srcs = test_strings(test_number, max_length, ALPHA | NUMBER); 
	char** dests = test_strings(test_number, max_length, ALPHA | NUMBER); 

	// strlen
	printf(">>> ft_strlen:\n");
	i = 0;
	while (i < test_number)
	{
		printf("src : \"%s\"\n", srcs[i]);
		ret_sizet = ft_strlen(srcs[i]);
		ret_std_d = strlen(srcs[i]);
		if (ret_sizet != ret_std_d)
		{
			printf("return : %ld should be %ld\n", ret_sizet, ret_std_d);
			fail = 1;
			break ;
		}
		i++;
	}
	if (fail)
	{
		printf("KO\n");
		exit(EXIT_FAILURE);
	}
	printf("OK");
	printf("\n<<<\n");

	// strcpy
	printf(">>> ft_strcpy:\n");

	i = 0;
	while (i < test_number)
	{
		strcpy(dest_std, dests[i]);
		printf("src : \"%s\"\n", srcs[i]);
		printf("initial dest : \"%s\"\n", dests[i]);
		ret = ft_strcpy(dests[i], srcs[i]);
		strcpy(dest_std, srcs[i]);
		if (dests[i] != ret || strcmp(dest_std, dests[i]))
		{
			printf("return : %p should be %p\n", ret, dests[i]);
			printf("final dest : \"%s\" should be \"%s\"\n", dests[i], dest_std);
			fail = 1;
			break ;
		}
		i++;
	}
	if (fail)
	{
		printf("KO\n");
		exit(EXIT_FAILURE);
	}
	printf("OK");
	printf("\n<<<\n");

	// strcmp
	printf(">>> strcmp:\n");

	i = 0;
	while (i < test_number)
	{
		printf("src : \"%s\"\n", srcs[i]);
		printf("initial dest : \"%s\"\n", dests[i]);
		ret_std_int = strcmp(dests[i], srcs[i]);
		ret_int = ft_strcmp(dests[i], srcs[i]);
		if (ret_int != ret_std_int)
		{
			printf("return : %d should be %d\n", ret_int, ret_std_int);
			fail = 1;
			break ;
		}
		i++;
	}
	if (fail)
	{
		printf("KO\n");
		exit(EXIT_FAILURE);
	}
	printf("OK");
	printf("\n<<<\n");

	/*errno = 0;*/
	/*printf("result write: %zd\n", write(1, "hello\n", 400));*/
	/*perror("write");*/
	/*errno = 0;*/
	/*printf("result ft_write: %zd\n", ft_write(1, "hello\n", 400));*/
	/*perror("ft_write");*/
	return 0;
}
