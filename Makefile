NAME = libasm.a

SRCS = ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s
OBJS = ${SRCS:.s=.o}

C_FLAGS = -Werror -Wextra -Wall
CC	= clang

AS = nasm
AS_FLAGS = -felf64 -gdwarf

INCLUDES = -I.

LIB = -lc

all:		${NAME}

$(NAME):	${OBJS}	
	${AR} -rcs ${NAME} ${OBJS}

clean:
	${RM} -f main.o test.o
	${RM} -f ${OBJS}

fclean: clean
	${RM} -f ${NAME}

re:		fclean all

test : ${NAME}
	${CC} -Wextra -Wall -g test.c -c -o test.o
	${CC} -Wextra -Wall -g main.c -c -o main.o
	${CC} -Wextra -Wall -g test.o main.o ${NAME} && ./a.out

.s.o:
	${AS} ${AS_FLAGS} $<

.PHONY:	all clean fclean re test
