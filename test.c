#ifndef TEST_H
# define TEST_H
# include <unistd.h>
# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include "test.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void			ft_putstr(char *str)
{
	unsigned char content;

	content = *str;
	while (content != '\0')
	{
		ft_putchar(*str);
		str++;
		content = *str;
	}
}

static unsigned char	convert(unsigned char c)
{
	if (0 <= c && c <= 9)
		return ('0' + c);
	else
		return ('a' + c - 10);
}


static void		print(unsigned char c)
{
	char printed1;
	char printed2;

	printed1 = convert(c / 16);
	printed2 = convert(c % 16);
	write(1, "\\", 1);
	write(1, &printed1, 1);
	write(1, &printed2, 1);
}

void	ft_putchar_non_printable(char c)
{
	if ((' ' <= c && c <= '~'))
		write(1, &c, 1);
	else
		print((unsigned char) c);
}

void	ft_putstr_non_printable(char *str)
{
	unsigned char content;

	content = *str;
	while (content != '\0')
	{
		ft_putchar(*str);
		str++;
	}
}

static void	ft_putnbr2(int nb)
{
	char c;

	if (nb >= 10)
		ft_putnbr2(nb / 10);
	c = '0' + nb % 10;
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
		write(1, "-2147483648", 11);
	else if (nb < 0)
	{
		write(1, "-", 1);
		ft_putnbr2(-nb);
	}
	else
		ft_putnbr2(nb);
}

void ft_putchar_array(char* array, int n)
{
	ft_putstr("[ ");
	if (n > 0)
	{
		int i;
		for (i = 0; i < n - 1; i++)
		{
			ft_putchar_non_printable(array[i]);
			ft_putstr(", ");
		}
		ft_putchar_non_printable(array[n - 1]);
	}
	ft_putstr(" ]");
}

void initialize()
{
	srand(time(NULL));
}

static unsigned char alea_char_between(unsigned char a, unsigned char b)
{
	return a + (rand() % (a - b + 1));
}

unsigned char alea_char(unsigned char flags)
{
	int dice = 0;
	if ((flags & PRINT) == PRINT)
		return alea_char_between(' ', '~');
	else if ((flags & (ALPHA | NUMBER)) == (ALPHA | NUMBER))
	{
		dice = rand() % 3;
		if (dice == 0)
			return alea_char_between('0', '9');
		else if (dice == 1)
			return alea_char_between('a', 'z');
		else if (dice == 2)
			return alea_char_between('A', 'Z');
	}
	else if ((flags & ALPHA) == ALPHA)
	{
		dice = rand() % 2;
		if (dice)
			return alea_char_between('a', 'z');
		else
			return alea_char_between('A', 'Z');
	}
	else if ((flags & NUMBER) == NUMBER)
		return alea_char_between('0', '9');
	else
		return alea_char_between(0, 255);
	return '\0';
}

char *alea_array(int size, unsigned int flags)
{
	char *string = NULL;
	if (size > 0)
	{
		string = malloc (size * sizeof(char));
		if (string == NULL)
			perror ("Could not allocate string\n");
		for (int i = 0; i < size; i++)
			string[i] = alea_char(flags);
		if (flags & STRING)
		{
			size = rand() % size;
			string[size] = '\0';
		}
	}
  return string;
}

void rand_free_and_put(char** array, int number, int min_index, char* src)
{
		int dice = min_index + rand() % (number - min_index);
		free(array[dice]);

		array[dice] = (char*)malloc(strlen(src)+1);
		strcpy(array[dice], src);
}

char **test_arrays(int number, int size, unsigned int flags)
{
	int i;
	int min_index = 0;
	char **alea = NULL;
	if (flags & STRING)
	{
		if (number < 10)
			number = 10;
	}
	alea = (char**)malloc (number * sizeof(char*));
	if (alea == NULL)
		perror("Could not allocate strings\n");
	for (i = 0; i < number; i++)
		alea[i] = alea_array(size, flags);
	if ((flags & STRING) == STRING)
	{
		strcpy(alea[min_index++],"");
		strcpy(alea[min_index++],"a");
		rand_free_and_put(alea, number, min_index, "");
		rand_free_and_put(alea, number, min_index, "a");
		rand_free_and_put(alea, number, min_index, "");
		rand_free_and_put(alea, number, min_index, "a");
	}
	return alea;
}

char **test_strings(int number, int max_length, unsigned int flags)
{
	return test_arrays(number, max_length + 1, flags | STRING);
}

static void put_int_if_possible(int* array, int stuff, int index, int min, int max, unsigned int flags)
{
	int put = 0;
	if ((flags & UNSIGNED) == UNSIGNED)
	{
		if ((unsigned int)min <= (unsigned int)stuff && (unsigned int)stuff <= (unsigned int)max)
			put = 1;
	}
	else
	{
		if (min <= stuff && stuff <= max)
			put = 1;
	}
	if (put)
		array[index] = stuff;
}

int *test_ints(number)
{
	return test_ints_from_to(number,INT_MIN,INT_MAX, SIGNED | ALLRANGE);
}

int alea_int_from_to(int min, int max, unsigned int flags)
{
	int dice;
	int range;

	if ((flags & SIGNED) == SIGNED)
	{
		if ((flags & ALLRANGE) == ALLRANGE)
		{
			dice = rand() % 2;
			if (dice)
				return rand();
			else
				return -rand();
		}
		else
			return rand() % (max - min + 1) + min;
	}
	else
	{
		if ((flags & ALLRANGE) == ALLRANGE)
		{
			range = (int)((unsigned int)max - (unsigned int)min);
			return (unsigned int)min + (unsigned int)(rand() % (range + 1));
		}
		else
			return rand();
	}
}

int *test_ints_from_to(int number, int min, int max, unsigned int flags)
{
	if (number < 10)
		number = 10;
	int *alea = malloc (number * sizeof(int));
	for (int i = 0; i < number ; i++)
	{
		alea[i] = alea_int_from_to(min, max, flags);
	}
	int dice;
	for (int i = 0; i < 10; i++)
	{
		dice = rand() % number;
		switch(i)
		{
			case 0:
				put_int_if_possible(alea, 0, dice, min, max, flags);
				break;
			case 1:;
				put_int_if_possible(alea, 0, dice, min, max, flags);
				break;
			case 2:
				put_int_if_possible(alea, 1, dice, min, max, flags);
				break;
			case 3:
				put_int_if_possible(alea, 1, dice, min, max, flags);
				break;
			case 4:
				put_int_if_possible(alea, -1, dice, min, max, flags);
				break;
			case 5:
				put_int_if_possible(alea, -1, dice, min, max, flags);
				break;
			case 6:
				put_int_if_possible(alea, min, dice, min, max, flags);
				break;
			case 7:
				put_int_if_possible(alea, min, dice, min, max, flags);
				break;
			case 8:
				put_int_if_possible(alea, max, dice, min, max, flags);
				break;
			case 9:
				put_int_if_possible(alea, max, dice, min, max, flags);
				break;
		}
	}
	return alea;
}

int *test_unsigned_ints_from_to(int number, int min, int max)
{
	return test_ints_from_to(number, min, max, UNSIGNED);
}

#endif
