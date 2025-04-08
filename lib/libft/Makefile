SRCS = \
ft_strlen.c ft_strlcat.c ft_strlcpy.c ft_bzero.c ft_memchr.c \
ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c \
ft_isalpha.c ft_atoi.c ft_isalnum.c ft_isascii.c ft_isdigit.c \
ft_isprint.c ft_memcmp.c ft_toupper.c ft_tolower.c ft_strncmp.c \
ft_strrchr.c ft_strnstr.c ft_calloc.c ft_putchar_fd.c ft_putstr_fd.c \
ft_putendl_fd.c ft_putnbr_fd.c ft_strjoin.c ft_substr.c ft_strtrim.c \
ft_strmapi.c ft_striteri.c ft_itoa.c ft_split.c ft_strcmp.c ft_strcat.c ft_strcpy.c

SRCSB = \
ft_lstnew.c ft_lstsize.c ft_lstlast.c ft_lstadd_front.c ft_lstadd_back.c \
ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

SRCS_PRINTF = \
ft_printf/ft_print_format.c ft_printf/ft_print_ptr.c ft_printf/ft_printf.c

SRCS_GNL = \
get_next_line/get_next_line_utils.c get_next_line/get_next_line.c

SRCSB_GNL = \
get_next_line/get_next_line_utils_bonus.c get_next_line/get_next_line_bonus.c

NAME = libft.a
OBJS = $(SRCS:.c=.o)
OBJSB = $(SRCSB:.c=.o)
OBJS_PRINTF = $(SRCS_PRINTF:.c=.o)
OBJS_GNL = $(SRCS_GNL:.c=.o)
OBJSB_GNL = $(SRCSB_GNL:.c=.o)

LIBC = ar rcs
FLAGS = -Wall -Wextra -Werror
CC = gcc
RM = rm -f

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME)	: $(OBJS) $(OBJS_PRINTF) $(OBJS_GNL) $(OBJSB_GNL)
	$(LIBC) $(NAME) $(OBJS) $(OBJS_PRINTF) $(OBJS_GNL)

all:	$(NAME)

bonus: $(NAME) $(OBJSB) $(OBJSB_GNL)
	$(LIBC) $(NAME) $(OBJSB) $(OBJSB_GNL)

clean:
	$(RM) $(OBJS) $(OBJSB) $(OBJS_PRINTF) $(OBJS_GNL) $(OBJSB_GNL)

fclean: clean
	$(RM) $(NAME) $(bonus)

re:	fclean all

.PHONY : all bonus clean fclean re
