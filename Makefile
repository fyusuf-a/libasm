NAME = libasm.a

SRCS = ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s
OBJS = ${SRCS:.s=.o}

SRCS_BONUS = ft_check_base_bonus.s ft_elem_bonus.s ft_atoi_base_bonus.s ft_create_elem_bonus.s ft_list_push_front_bonus.s ft_list_size_bonus.s ft_list_sort_bonus.s ft_list_remove_if_bonus.s
OBJS_BONUS = ${SRCS_BONUS:.s=.o}

SRCS_TEST = main.c test.c
OBJS_TEST = ${SRCS_TEST:.c=.o}

C_FLAGS = -Werror -Wextra -Wall -fPIC
CC	= clang

AS = nasm
AS_FLAGS = -felf64 -gdwarf

INCLUDES = -I.

LIB = -lc

all:		${NAME}

$(NAME):	${OBJS}	
	${AR} -rcs ${NAME} ${OBJS}

bonus: all ${OBJS_BONUS}
	${AR} r ${NAME} ${OBJS_BONUS}

clean:
	${RM} -f main.o test.o
	${RM} -f ${OBJS} ${OBJS_BONUS}

fclean: clean
	${RM} -f ${NAME}

re:		fclean all

test : bonus ${OBJS_TEST}
	${CC} -Wextra -Wall -g ${OBJS_TEST} ${NAME} && ./a.out

.c.o:
	${CC} -Wextra -Wall -g -c $< -o ${<:.c=.o}

.s.o:
	${AS} ${AS_FLAGS} $<

.PHONY:	all clean fclean re test
