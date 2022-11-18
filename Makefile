#==============================================================================#
#                                   TARGETS                                    #
#==============================================================================#

NAME = minishell

#==============================================================================#
#                                   COMMANDS                                   #
#==============================================================================#

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
DFLAGS = -MMD
MKDIR = mkdir -p
RM = rm -f
MAKE_SILENT = make --no-print-directory
INC_LIBFT = -L libft -lft

#==============================================================================#
#                                    COLORS                                    #
#==============================================================================#

PURPLE = \033[35m
GREEN = \033[32m
YELLOW = \033[33m
END = \033[0m

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

SRC_DIR = src
HEADER_DIR = include
OBJ_DIR = obj

#==============================================================================#
#                                   SOURCES                                    #
#==============================================================================#

SRC = main.c initialize.c free_memory.c minishell.c lexer.c lexer_utils.c \
		lexer_initialize.c utils.c lexer_delimiter.c lexer_redi.c \
		lexer_command.c lexer_argument.c lexer_child.c temp.c parser_wildcard.c\
		parser.c parser_wildcard_utils.c parser_dir_utils.c parser_expand_utils.c\
		parser_expand.c ft_put_in_quotes.c parser_wildcard_algo.c parser_dir.c\
		parser__ft_wildcard.c ft_take_off_quotes.c parser__ft_expand.c builtins.c\
		parser_check_str.c builtins_export.c error.c parser_input_output.c parser_cmd_arg.c\

#==============================================================================#
#                                   HEADERS                                    #
#==============================================================================#

HEAD_NAME = $(HEADER_DIR)/minishell.h

#==============================================================================#
#                                   OBJECTS                                    #
#==============================================================================#

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

#==============================================================================#
#                                   MAKEFILE                                   #
#==============================================================================#

all : $(OBJ_DIR) $(NAME)

$(NAME) : $(OBJ)
	$(MAKE_SILENT) -C libft
	echo "$(YELLOW)Making Minishell$(END)"
	$(CC) $(OBJ) $(INC_LIBFT) -o $(NAME) -lreadline -g
	echo "$(GREEN)Done$(END)"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEAD_NAME)
	$(CC) $(DFLAGS) -c $< -o $@

$(OBJ_DIR) :
	$(MKDIR) $(OBJ_DIR)

clean :
	$(MAKE_SILENT) fclean -C libft
	echo "$(PURPLE)Cleaning Minishell's objects...$(END)"
	$(RM)r $(OBJ_DIR)
	echo "$(GREEN)Done$(END)"

fclean : clean
	echo "$(PURPLE)Cleaning Minishell...$(END)"
	$(RM) $(NAME)
	echo "$(GREEN)Done$(END)"

re : fclean
	$(MAKE_SILENT) all

.PHONY : all clean fclean re
.SILENT :
