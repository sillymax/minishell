# Makefile for minishell

# Program name
NAME := minishell
BONUS_NAME := minishell_bonus

# Directory paths
SYS_HEADERS_PATH := ../
READLINE_PATH := ../readline/
LIBFT_PATH := ../libft/
OBJS_PATH := ./objs/
BUILTINS_PATH := ./builtins/
HEREDOCS_PATH := ./heredocs/
BONUS_PATH := ./bonus/

# Source files
SRCS := global.c \
		signal.c \
		character_check_1.c \
		character_check_2.c \
		character_check_3.c \
		character_check_4.c \
		character_check_5.c \
		character_check_6.c \
		operator_check_1.c \
		operator_check_2.c \
		double_array_utils.c \
		clone_envp_with_special.c \
		quote_handling.c \
		get_next_token_utils.c \
		get_next_token.c \
		get_next_subtoken_utils.c \
		get_next_subtoken.c \
		custom_strtok.c \
		env_check.c \
		get_next_env.c \
		string_utils.c \
		read_inputline_utils_1.c \
		read_inputline_utils_2.c \
		read_inputline_utils_3.c \
		read_inputline_utils_4.c \
		read_inputline_utils_5.c \
		read_inputline_utils_6.c \
		read_inputline_utils_7.c \
		read_inputline_utils_8.c \
		read_inputline_utils_9.c \
		read_inputline_helper.c \
		read_inputline.c \
		expand_env_utils_1.c \
		expand_env_utils_2.c \
		expand_env.c \
		get_next_line_utils.c \
		get_next_line.c \
		expand_tilde_utils_1.c \
		expand_tilde_utils_2.c \
		expand_tilde_helper.c \
		expand_tilde.c \
		expand_glob_utils.c \
		expand_glob.c \
		expand_escaped_utils.c \
		expand_escaped.c \
		expand_quotes_utils.c \
		expand_quotes.c \
		subtoken_list_utils_1.c \
		subtoken_list_utils_2.c \
		token_list_utils.c \
		get_token_list_utils.c \
		get_token_list.c \
		build_tree_utils_1.c \
		build_tree_utils_2.c \
		build_tree.c \
		evaluate_heredocs_utils_1.c \
		evaluate_heredocs_utils_2.c \
		evaluate_heredocs.c \
		evaluate_tree_utils_1.c \
		evaluate_tree_utils_2.c \
		evaluate_tree_utils_3.c \
		evaluate_tree_utils_4.c \
		evaluate_tree_utils_5.c \
		evaluate_tree_utils_6.c \
		evaluate_tree_utils_7.c \
		evaluate_tree_utils_8.c \
		evaluate_tree_utils_9.c \
		evaluate_tree.c \
		free_list.c \
		minishell.c

BUILTINS_SRCS := blt_echo_utils.c \
				 blt_echo.c \
				 blt_cd_utils_1.c \
				 blt_cd_utils_2.c \
				 blt_cd.c \
				 blt_pwd.c \
				 blt_export_utils_1.c \
				 blt_export_utils_2.c \
				 blt_export_utils_3.c \
				 blt_export_utils_4.c \
				 blt_export.c \
				 blt_unset.c \
				 blt_env.c \
				 blt_exit_utils.c \
				 blt_exit.c

# Object files
SRCS_OBJS := $(addprefix $(OBJS_PATH), $(SRCS:.c=.o))
BUILTINS_OBJS := $(addprefix $(OBJS_PATH), $(BUILTINS_SRCS:.c=.o))
OBJS := $(SRCS_OBJS) $(BUILTINS_OBJS)

# Heredocs files
TMPS_TXT := $(wildcard $(HEREDOCS_PATH)*.txt);

# Run the make tool in another directory
LIBFT_MAKE := $(MAKE) -C$(LIBFT_PATH)
BONUS_MAKE := $(MAKE) -C$(BONUS_PATH)

# Compiler and flags
CC := cc
CFLAGS := -Wall -Werror -Wextra $(if $(FSANITIZE), -fsanitize=$(FSANITIZE))

# Include flags, for the compiler to find additional header files
INCLUDE_SYS_HEADERS := -I$(SYS_HEADERS_PATH)
INCLUDE_READLINE := -I$(READLINE_PATH)
INCLUDE_LIBFT := -I$(LIBFT_PATH)includes/

# Locate, and Link flags, for the compiler to find and link the static library
LDFLAGS := -L$(READLINE_PATH) -L$(LIBFT_PATH)
LDLIBS := -lreadline -lncurses -lhistory -lft

# Remove command and flags
RM := rm
RMFLAGS := -rf

# Default target
all: $(NAME)

# Rule to build program
$(NAME): $(OBJS)
	@$(LIBFT_MAKE) re
	@$(RM) $(RMFLAGS) $(BONUS_NAME)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

# Pattern rule to compile .c files into .o files
$(OBJS_PATH)%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE_SYS_HEADERS) $(INCLUDE_READLINE) $(INCLUDE_LIBFT) -c $< -o $@

$(OBJS_PATH)%.o: $(BUILTINS_PATH)%.c
	@$(CC) $(CFLAGS) $(INCLUDE_SYS_HEADERS) $(INCLUDE_READLINE) $(INCLUDE_LIBFT) -c $< -o $@

# Bonus target
bonus: fclean
	@$(BONUS_MAKE)
	@mv $(BONUS_PATH)$(BONUS_NAME) ./
	@$(BONUS_MAKE) fclean

# Remove all object files
clean:
	@$(LIBFT_MAKE) clean
	@$(RM) $(RMFLAGS) $(OBJS) $(TMPS_TXT)

# Remove all generated files
fclean: clean
	@$(LIBFT_MAKE) fclean
	@$(RM) $(RMFLAGS) $(NAME) $(BONUS_NAME)

# Rebuild the program
re: fclean all

# Phony targets
.PHONY: all clean fclean re
