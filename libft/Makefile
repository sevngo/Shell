NAME = libft.a
CC = gcc
FLAGS = -Wall -Wextra -Werror

SRC_PATH = ./
INC_PATH = ./
OBJ_PATH = ./

SRC_FILES = ft_memset.c				\
		   	ft_bzero.c				\
		   	ft_memcpy.c				\
		   	ft_memccpy.c			\
		   	ft_memmove.c			\
		   	ft_memchr.c				\
		   	ft_memcmp.c				\
		   	ft_strlen.c				\
		   	ft_strdup.c				\
		   	ft_strcpy.c				\
		   	ft_strncpy.c			\
		   	ft_strcat.c				\
		   	ft_strncat.c			\
		   	ft_strlcat.c			\
		   	ft_strchr.c				\
		   	ft_strrchr.c			\
		   	ft_strstr.c				\
		   	ft_strnstr.c			\
		   	ft_strcmp.c				\
		   	ft_strncmp.c			\
		   	ft_atoi.c				\
		   	ft_isalpha.c			\
		   	ft_isdigit.c			\
		   	ft_isalnum.c			\
		   	ft_isascii.c			\
		   	ft_isprint.c			\
		   	ft_toupper.c			\
		   	ft_tolower.c			\
		   	ft_memalloc.c			\
		   	ft_memdel.c				\
		   	ft_strnew.c				\
		   	ft_strdel.c				\
		   	ft_strclr.c				\
		   	ft_striter.c			\
		   	ft_striteri.c			\
		   	ft_strmap.c				\
		   	ft_strmapi.c			\
		   	ft_strequ.c				\
		   	ft_strnequ.c			\
		   	ft_strsub.c				\
		   	ft_strjoin.c			\
		   	ft_strjoin_separator.c	\
		   	ft_strtrim.c			\
		   	ft_strsplit.c			\
		   	ft_itoa.c				\
		   	ft_putchar.c			\
		   	ft_putstr.c				\
		   	ft_putendl.c			\
		   	ft_putnbr.c				\
		   	ft_putchar_fd.c			\
		   	ft_putstr_fd.c			\
		   	ft_putendl_fd.c			\
		   	ft_putnbr_fd.c			\
		   	ft_lstnew.c				\
		   	ft_lstdelone.c			\
		   	ft_lstdel.c				\
		   	ft_lstadd.c				\
		   	ft_lstiter.c			\
		   	ft_lstmap.c				\
		   	ft_nbofwords.c			\
		   	ft_intlen.c				\
		   	ft_check.c				\
		   	ft_free.c				\
		   	ft_putnbrnl.c			\
		   	ft_putcharnl.c			\
		   	ft_arrdup.c				\
		   	ft_arrlen.c				\
		   	ft_arrfree.c			\
		   	ft_arrrev.c				\
		   	ft_arrsort.c			\
		   	ft_countc.c				\
		   	ft_getch.c				\
		   	ft_putarr.c				\
		   	ft_putcolor.c			\
		   	ft_strjoin_free.c		\
		   	ft_strndup.c			\
		   	ft_strnjoin.c			\
		   	ft_strrcpy.c			\
		   	ft_strrdup.c			\
		   	ft_isspace.c			\
		   	ft_strisblank.c			\
		   	ft_arrndup.c			\
			ft_arrprint.c			\
			ft_strisdigit.c			\
			ft_strisalpha.c			\
			ft_strepart.c			\
			ft_putchar_nb_fd.c		\
			ft_wstrtoa.c			\
			ft_wchartoa.c			\
			ft_isescape.c			\
			ft_wstrlen.c			\
			ft_wcharlen.c			\
			ft_tabdel.c				\
			ft_ftoa.c				\
			ft_itoa_base.c			\
			ft_strlowcase.c			\
			ft_recursive_power.c	\
			ft_strcjoin.c			\
			ft_printf/buffering.c			\
			ft_printf/chars_to_str.c		\
			ft_printf/conv_to_buffer.c		\
			ft_printf/float_to_str.c		\
			ft_printf/ft_printf.c			\
			ft_printf/get_conv.c			\
			ft_printf/get_id.c				\
			ft_printf/goto_arg.c			\
			ft_printf/init.c				\
			ft_printf/nbr_to_str.c			\
			ft_printf/normal_to_buffer.c	\
			ft_printf/putconv_to_buffer.c	\
			ft_printf/set_apostrophe.c		\
			ft_printf/set_precision.c		\
			ft_printf/toolkit.c				\
			get_next_line.c

INC_FILES = libft.h
OBJ_FILES = $(SRC_FILES:.c=.o)

INCS = $(addprefix $(INC_PATH), $(INC_FILES))
OBJS = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INCS) Makefile
	@$(CC) $(FLAGS) -I $(INC_PATH) -o $@ -c $<

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
