NAME		=	minishell

SRCS		=	src/main.c src/builtins.c  src/exec.c		\
				src/fill_node.c src/get_params.c 			\
				src/expand.c src/heredoc.c src/error.c src/env.c src/custom_cmd.c	\
				src/get_next_line.c src/get_next_line_utils.c src/prompt.c	\
				src/signal.c src/parse_args.c src/get_cmd.c	\
				src/liba/ft_bzero.c src/liba/ft_isalnum.c src/liba/ft_isalpha.c src/liba/ft_isascii.c src/liba/ft_isdigit.c \
				src/liba/ft_isprint.c src/liba/ft_memccpy.c src/liba/ft_memcpy.c src/liba/ft_memset.c src/liba/ft_strchr.c \
				src/liba/ft_strlen.c src/liba/ft_strrchr.c src/liba/ft_tolower.c src/liba/ft_toupper.c src/liba/ft_strncmp.c	\
				src/liba/ft_memmove.c src/liba/ft_memchr.c src/liba/ft_memcmp.c src/liba/ft_strlcpy.c src/liba/ft_strlcat.c	\
				src/liba/ft_strnstr.c src/liba/ft_atoi.c src/liba/ft_calloc.c src/liba/ft_strdup.c src/liba/ft_putchar_fd.c 	\
				src/liba/ft_putstr_fd.c src/liba/ft_putnbr_fd.c src/liba/ft_putendl_fd.c src/liba/ft_substr.c src/liba/ft_strjoin.c	\
				src/liba/ft_strtrim.c src/liba/ft_strmapi.c src/liba/ft_itoa.c src/liba/ft_split.c src/liba/ft_dup_matrix.c	\
				src/liba/ft_putmatrix_fd.c src/liba/ft_strchr_i.c src/liba/ft_matrixlen.c src/liba/ft_extend_matrix.c	\
				src/liba/ft_isspace.c src/liba/ft_lstadd_back.c src/liba/ft_lstlast.c src/liba/ft_lstnew.c src/liba/ft_matrix_replace_in.c src/liba/ft_strchars_i.c\
				src/liba/ft_lstsize.c src/liba/ft_lstclear.c src/liba/ft_strtrim_all.c src/liba/ft_cmdtrim.c src/liba/ft_cmdsubsplit.c


OBJS		= 	$(patsubst %.c,%.o,$(SRCS))

CC			= 	@gcc

CFLAGS		= 	-Wall -Wextra -Werror -I $(INCLUDES)

INCLUDES	= 	./inc/

RM			= 	rm -rf

all: 			$(NAME)

$(OBJS):		$(INCLUDES)

$(NAME): 		$(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline
				@echo "\033[30;42m      Program completed      "

clean:
				@${RM} $(OBJS)
				@echo "\033[30;43m        files deleted        "

fclean:			
				@${RM} $(OBJS) $(NAME)
				@echo "\033[30;43m        files deleted        "

re:				fclean all

.PHONY:			all clean fclean re