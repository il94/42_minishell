# Compilation flags
ifeq ($(DMEM),1)
MEM 		= -fsanitize=address
endif

ifeq ($(DTHREAD),1)
MEM 		= -fsanitize=thread
endif

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

SRC_DIR = src/
HEADER_DIR = include/
OBJ_DIR = obj/

#==============================================================================#
#                                   SOURCES                                    #
#==============================================================================#

SRC =	main.c initialize.c free_memory.c minishell.c utils.c error.c \
		temp.c \
		\
		lexer/lexer.c lexer/lexer_utils.c lexer/lexer_initialize.c \
		lexer/lexer_delimiter.c lexer/lexer_redi.c lexer/lexer_command.c \
		lexer/lexer_argument.c lexer/lexer_child.c \
		\
		parser/parser_wildcard.c parser/parser.c parser/parser_wildcard_utils.c \
		parser/parser_dir_utils.c parser/parser_expand_utils.c \
		parser/parser_expand.c parser/parser_wildcard_algo.c parser/parser_dir.c \
		parser/parser_ft_wildcard.c parser/parser_ft_expand.c \
		parser/parser_check_str.c parser/parser_cmd_arg.c \
		parser/parser_input_output.c parser/parser_get_paths.c \
		parser/parser_ft_put_in_quotes.c parser/parser_ft_take_off_quotes.c \
		parser/parser_open_files.c parser/parser_here_doc.c \
		parser/parser_pipe.c\
		exec/exec.c\
		builtins/builtins.c builtins/builtins_env.c \
		\

#==============================================================================#
#                                   HEADERS                                    #
#==============================================================================#

HEAD_NAME = $(HEADER_DIR)/minishell.h
INC = -I./$(HEADER_DIR)

#==============================================================================#
#                                   OBJECTS                                    #
#==============================================================================#

OBJ = $(addprefix ${OBJ_DIR}, ${SRC:.c=.o})

#==============================================================================#
#                                   MAKEFILE                                   #
#==============================================================================#

all : $(NAME)


$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEAD_NAME)
	mkdir -p ${@D}
	$(CC) $(DFLAGS) $(MEM) $(INC) -c $< -o $@

$(NAME) : $(OBJ)
	$(MAKE_SILENT) -C libft
	echo "$(YELLOW)Making Minishell$(END)"
	$(CC) $(OBJ) $(INC_LIBFT) $(INC) $(MEM) -o $(NAME) -lreadline -g
	echo "$(GREEN)Done$(END)"

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