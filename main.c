#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include "test.h"
#include "libasm.h"

#define TEST_NUMBER 0
#define MAX_LENGTH 50


INIT_REDIRECT

int		compare_lists(t_list* list1, t_list* list2)
{
	if (!list1)
	{
		if (!list2)
			return (1);
		return (0);
	}
	if (!list2)
		return (0);
	return (compare_lists(list1->next, list2->next));
}

void	no_op(void* c)
{
	(void)c;
	return ;
}

int 	cmp(char *c1, char *c2)
{
	return (*c1 - *c2);
}

void	test_list_size(t_list* list, int size)
{
	if (ft_list_size(list) != size)
	{
		printf("ft_list_size failed on a list of size %d\n", size);
		printf("KO\n");
		exit(1);
	}
}

void 	print_char_list(t_list *list)
{
	if (!list)
	{
		printf("|");
		return ;
	}
	printf("%c -> ", *((char*)list->data));
	print_char_list(list->next);
}

void	test_write(const void *buf, size_t count) // Testing write with standard output
{
	unsigned long min = strlen(buf) + 1 < count ? strlen(buf) + 1 : count;
	printf("Of the following, %zu bytes has to be written: \"%s\"\n", min, buf);
	REDIRECT(LIBC_FILE);
	int ret_std = write(1, buf, min);
	STOP_REDIRECT

	int errno_std = errno;
	
	REDIRECT(TEST_FILE);
	int ret_mine = write(1, buf, min);
	STOP_REDIRECT

	int errno_mine = errno;

	int diff = analyse_differences(TEST_FILE, LIBC_FILE); 
	if (diff == -1)
	{
		printf("There has been an error, please re-run\n");
		exit(1);
	}
	else if (diff == 1)
	{
		printf("KO\n");
		system("diff "TEST_FILE" "LIBC_FILE);
		exit(1);
	}
	if (ret_std != ret_mine)
	{
		printf("KO\n");
		printf("return of write : %d\n", ret_std);
		printf("return of ft_write : %d\n", ret_mine);
		exit(1);
	}
	if (errno_mine != errno_std)
	{
		printf("KO\n");
		printf("errno for write : %d\n", ret_std);
		printf("errno of ft_write : %d\n", ret_mine);
		exit(1);
	}
	unlink(TEST_FILE); unlink(LIBC_FILE);
}

void	test_read(char* src, size_t count) // Testing read with a file in current directory containing src
{
	char *buf_std = NULL;
	char *buf_mine = NULL;

	int fd_std;
	int fd_mine;

	if ((fd_std = open(LIBC_FILE, O_RDWR | O_CREAT, 0664)) < 0)
	{
		printf("Opening \"%s\"...\n", LIBC_FILE);
		perror("open:");
		exit(1);
	}
	if ((fd_mine = open(TEST_FILE, O_RDWR | O_CREAT, 0664)) < 0)
	{
		printf("Opening \"%s\"...\n", TEST_FILE);
		perror("open:");
		close(fd_std);
		exit(1);
	}
	if (write(fd_std, src, strlen(src)) < 0)
	{
		printf("Writing \"%s\" to %s...\n", src, LIBC_FILE);
		perror("write:");
		close(fd_std); close(fd_mine);
		exit(1);
	}
	if (write(fd_mine, src, strlen(src)) < 0)
	{
		printf("Writing \"%s\" to %s...\n", src, TEST_FILE);
		perror("write:");
		close(fd_std); close(fd_mine);
		exit(1);
	}

	printf("Attempting to read %zu characters of string \"%s\" from buffers...\n", count, src);

	REDIRECT(LIBC_FILE);
	int ret_std = read(fd_std, buf_std, count);
	STOP_REDIRECT

	int errno_std = errno;
	
	REDIRECT(TEST_FILE);
	int ret_mine = ft_read(fd_mine, buf_std, count);
	STOP_REDIRECT

	int errno_mine = errno;

	if (ret_std != ret_mine)
	{
		printf("KO\n");
		printf("return of write : %d\n", ret_std);
		printf("return of ft_write : %d\n", ret_mine);
		close(fd_std); close(fd_mine);
		exit(1);
	}
	if (strncmp(buf_std, buf_mine, ret_std > ret_mine ? ret_std : ret_mine) != 0)
	{
		printf("KO\n");
		printf("buffer at the end of read: \"");
		for (int i = 0; i < ret_std; i++)
			printf("%c", buf_mine[i]);
		printf("\"\n");
		printf("buffer at the end ft_read: \"");
		for (int i = 0; i < ret_mine; i++)
			printf("%c", buf_std[i]);
		printf("\"\n");
		close(fd_std); close(fd_mine);
		exit(1);
	}
	if (errno_mine != errno_std)
	{
		printf("KO\n");
		printf("errno for write : %d\n", ret_std);
		printf("errno of ft_write : %d\n", ret_mine);
		close(fd_std); close(fd_mine);
		exit(1);
	}
	close(fd_std); close(fd_mine);
	unlink(LIBC_FILE) ; unlink(TEST_FILE);
}

void test_strdup(char *str)
{
	char *res = NULL;
	printf("Using ft_strdup on string \"%s\"...\n", str);
	res = ft_strdup(str);
	if (strcmp(res, str) != 0)
	{
		printf("KO\n");
		printf("The destination string \"%s\" is not equal to the source string \"%s\"\n", res, str);
		free(res);
		exit(1);
	}
	free(res);
}

int		main() {
	int fail = 0;
	int i;
	char *ret;
	size_t ret_sizet, ret_std_d;
	int ret_int, ret_std_int;
	initialize();
	char** srcs = test_strings(TEST_NUMBER, MAX_LENGTH, ALPHA | NUMBER); 
	char** dests = test_strings(TEST_NUMBER, MAX_LENGTH, ALPHA | NUMBER); 
	int* ints = test_ints_from_to(TEST_NUMBER, 0, 150, UNSIGNED);
	char dest_std[MAX_LENGTH + 1];

	// strlen
	printf(">>> ft_strlen: ");
	i = 0;
	while (i < TEST_NUMBER)
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
	printf(">>> ft_strcpy: ");

	i = 0;
	while (i < TEST_NUMBER)
	{
		strcpy(dest_std, dests[i]);
		printf("src : \"%s\" of length %zu\n", srcs[i], strlen(srcs[i]));
		printf("initial dest : \"%s\" of length %zu\n", dests[i], strlen(dests[i]));
		strcpy(dest_std, srcs[i]);
		ret = strcpy(dests[i], srcs[i]);
		if (dests[i] != ret)
		{
			printf("return : %p should be %p\n", ret, dests[i]);
			fail = 1;
			break ;
		}
		if (strcmp(dest_std, dests[i]) != 0)
		{
			printf("final dest : \"%s\" should be \"%s\"\n", dests[i], dest_std);
			fail = 1;
			break;
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
	printf(">>> ft_strcmp: ");

	i = 0;
	while (i < TEST_NUMBER)
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

	//ft_write
	printf(">>> ft_write: ");

	i = 0;
	while (i < TEST_NUMBER)
	{
		test_write(srcs[i],  ints[i]); // Testing write with standard output
		i++;
	}
	printf("OK");
	printf("\n<<<\n");

	//ft_write
	printf(">>> ft_read: ");
	i = 0;
	while (i < TEST_NUMBER)
	{
		test_read(srcs[i],  ints[i]); // Testing write with standard output
		i++;
	}
	printf("OK");
	printf("\n<<<\n");

	printf(">>> ft_strdup: ");

	i = 0;
	while (i < TEST_NUMBER)
	{
		test_strdup(srcs[i]); // Testing write with standard output
		i++;
	}
	printf("OK");
	printf("\n<<<\n");

	// Cleaning up
	for (int i = 0; i < TEST_NUMBER; i++)
	{
		free(srcs[i]);
		free(dests[i]);
	}
	free(srcs);
	free(dests);

	printf(">>> ft_atoi_base: ");
	char *oct = "01234567";
	char *num1 = "---+-+123ab567";
	char *num2 = "\r   \n\t -+-+--+-+467325ab567";
	char *num3 = "01111011ureio";
	if ((i = ft_atoi_base(num1, oct)) != 83)
	{
		printf("KO\n\"%s\" written in octal should be %d and not %d\n", num1, 83, i);
		exit(1);
	}
	if ((i = ft_atoi_base(num2, oct)) != -159445)
	{
		printf("KO\n\"%s\" written in octal should be %d and not %d\n", num2, -159445, i);
		exit(1);
	}
	if ((i = ft_atoi_base(num3, "01")) != 123)
	{
		printf("KO\n\"%s\" written in binary should be %d and not %d\n", num3, 123, i);
		exit(1);
	}
	printf("OK\n<<<\n");

	printf(">>> ft_create_elem:\n");
	t_list *list1 = ft_create_elem(&"u");
	t_list *list2 = ft_create_elem(&"k");

	printf("A list with a link with value 'u': ");
	print_char_list(list1);
	printf("\nA list with a link with value 'k': ");
	print_char_list(list2);
	printf("\n<<<\n");

	printf(">>> ft_list_push_front:\n");
	ft_list_push_front(&list1, &"t");
	printf("A list with a link with value 't' then 'u': ");
	print_char_list(list1);
	ft_list_push_front(&list1, &"a");
	printf("\nA list with a link with value 'a', then 't', then 'u': ");
	print_char_list(list1);
	printf("\n<<<\n");

	printf(">>> ft_list_size: ");
	test_list_size(NULL, 0);
	test_list_size(list2, 1);
	test_list_size(list1, 3);
	printf("OK\n<<<\n");

	printf(">>> ft_list_sort:\n");

	t_list *list3 = ft_create_elem(&"b");
	ft_list_push_front(&list3, &"a");
	ft_list_push_front(&list3, &"u");
	ft_list_push_front(&list3, &"t");
	printf("Sorting this list: ");
	print_char_list(list3);
	printf("...\n");
	t_list *list4 = ft_create_elem(&"u");
	ft_list_push_front(&list4, &"t");
	ft_list_push_front(&list4, &"b");
	ft_list_push_front(&list4, &"a");
	ft_list_sort(&list3, cmp);
	if (!compare_lists(list3, list4))
	{
		printf("Sorting the preceding list, you should have: "); print_char_list(list4);
		printf("not "); print_char_list(list3);
		printf("KO");
		exit(1);
	}
	t_list *list5 = ft_create_elem(&"u");
	ft_list_push_front(&list5, &"t");
	ft_list_push_front(&list5, &"z");
	ft_list_push_front(&list5, &"a");
	printf("Sorting this list: ");
	print_char_list(list5);
	printf("...\n");
	ft_list_sort(&list5, cmp);
	t_list *list6 = ft_create_elem(&"z");
	ft_list_push_front(&list6, &"u");
	ft_list_push_front(&list6, &"t");
	ft_list_push_front(&list6, &"a");
	if (!compare_lists(list5, list6))
	{
		printf("Sorting the preceding list, you should have: "); print_char_list(list6);
		printf("not "); print_char_list(list5);
		printf("KO");
		exit(1);
	}
	printf("OK\n<<<\n");

	printf(">>> ft_list_remove_if_acc: ");
	t_list *list7 = ft_create_elem(&"u");
	ft_list_push_front(&list7, &"u");
	ft_list_push_front(&list7, &"k");
	ft_list_push_front(&list7, &"t");
	ft_list_push_front(&list7, &"a");
	t_list *list7_wo_t = ft_create_elem(&"u");
	ft_list_push_front(&list7_wo_t, &"u");
	ft_list_push_front(&list7_wo_t, &"k");
	ft_list_push_front(&list7_wo_t, &"a");
	t_list *list7_wo_tu = ft_create_elem(&"k");
	ft_list_push_front(&list7_wo_tu, &"a");
	char *te = malloc(1);
	*te = 't';
	char *u = malloc(1);
	*u = 'u';
	ft_list_remove_if(&list7, te, cmp, no_op);
	if (!compare_lists(list7, list7_wo_t))
	{
		printf("\nSorting the preceding list, you should have: "); print_char_list(list7_wo_t);
		printf("not "); print_char_list(list7);
		printf("KO");
		exit(1);
	}
	ft_list_remove_if(&list7, u, cmp, no_op);
	if (!compare_lists(list7, list7_wo_tu))
	{
		printf("\nSorting the preceding list, you should have: "); print_char_list(list7_wo_tu);
		printf("not "); print_char_list(list7);
		printf("KO");
		exit(1);
	}
	printf("OK\n<<<\n");


	return 0;
}
