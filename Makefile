NAME = 42sh
CC = gcc
LIB = -ltermcap
FLAGS = -Wall -Wextra -Werror

SRC_PATH = srcs/
INC_PATH = incs/
OBJ_PATH = objs/
LFT_PATH = libft/

SRC_FILES = ast_build.c			\
			ast_pipe.c			\
			ast_read.c			\
			ast_token_tools.c	\
			cmd_exec.c			\
			cmd_exec_pipe.c		\
			cmd_init.c			\
			cmd_redir.c			\
			cmd_redir_df.c		\
			cmd_redir_fct.c		\
			cmd_redir_fds.c		\
			complet.c			\
			complet_case.c		\
			complet_disp.c		\
			complet_list.c		\
			env_tools.c			\
			get_hist_path.c		\
			heredocs.c			\
			hist_subs.c			\
			hist_subs_fct.c		\
			hist_tools1.c		\
			hist_tools2.c		\
			input_catch.c		\
			input_disp.c		\
			input_read.c		\
			is_squoted.c		\
			kp_fct_1.c			\
			kp_fct_2.c			\
			kp_fct_3.c			\
			kp_fct_4.c			\
			kp_fct_5.c			\
			main.c				\
			main_tools.c		\
			move_cursor.c		\
			my_cd.c				\
			isdotdot.c			\
			simplify_path.c		\
			get_envpathentry.c	\
			my_echo.c			\
			my_env1.c			\
			my_env2.c			\
			my_env3.c			\
			my_exit.c			\
			my_history1.c		\
			my_history2.c		\
			my_history3.c		\
			my_setenv.c			\
			my_unsetenv.c		\
			rules1.c			\
			rules2.c			\
			rules3.c			\
			sh_tools.c			\
			signal_handler.c	\
			tc_putc.c			\
			term_mode.c			\
			token_expand.c		\
			token_fct_1.c		\
			token_fct_2.c		\
			token_merge.c		\
			token_rework.c		\
			token_tools.c		\
			token_tools2.c		\
			tokenizer.c

INC_FILES = minishell.h	\
			macros.h
OBJ_FILES = $(SRC_FILES:.c=.o)
LFT_FILES = libft.a

INCS = $(addprefix $(INC_PATH), $(INC_FILES))
OBJS = $(addprefix $(OBJ_PATH), $(OBJ_FILES))
LIBFT = $(addprefix $(LFT_PATH), $(LFT_FILES))

C_DBLUE = \033[38;5;074m
C_BRWN1 = \033[38;5;095m
C_GREEN = \033[38;5;114m
C_LBLUE = \033[38;5;117m
C_BRWN2 = \033[38;5;138m
C_PRED2 = \033[38;5;166m
C_PRED1 = \033[38;5;203m
C_RESET = \033[0m

DOT = \033[38;5;244m[*] \033[0m
CLS = \r\e[K

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(FLAGS) $(LIB) $(LIBFT) $(OBJS) -o $(NAME)
	@echo "$(DOT)$(C_LBLUE)./$(NAME)$(C_RESET)$(C_DBLUE) is now ready to use!$(C_RESET)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INCS)
	@if [ ! -d "$(OBJ_PATH)" ]; then echo "$(DOT)$(C_BRWN2)Object files directory has been created.$(C_RESET)"; fi
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(FLAGS) -I $(INC_PATH) -o $@ -c $<
	@echo "$(DOT)$(C_BRWN1)Compiling object file: $@$(C_RESET)"

$(LIBFT): $(LFT_PATH)
	@echo "$(DOT)$(C_GREEN)Building libft...$(C_RESET)"
	@$(MAKE) -sC $(LFT_PATH) fclean && $(MAKE) -sC $(LFT_PATH)

clean:
	@rm -rf $(OBJ_PATH)
	@echo "$(DOT)$(C_PRED1)Object files directory has been deleted.$(C_RESET)"
	@$(MAKE) -sC $(LFT_PATH) clean
	@echo "$(DOT)$(C_PRED2)Cleaned libft: removed object files.$(C_RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(DOT)$(C_PRED1)./$(NAME) has been deleted.$(C_RESET)"
	@$(MAKE) -sC $(LFT_PATH) fclean
	@echo "$(DOT)$(C_PRED2)Cleaned libft: removed $(LIBFT).$(C_RESET)"

re: fclean all
