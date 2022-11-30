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

SRC =	main.c minishell/minishell.c \
		\
		minishell/utils/initialize.c minishell/utils/free_memory.c \
		minishell/utils/utils.c minishell/utils/error.c \
		minishell/utils/temp.c minishell/utils/is_there.c\
		\
		minishell/lexer/lexer.c minishell/lexer/lexer_utils.c minishell/lexer/lexer_initialize.c \
		minishell/lexer/lexer_delimiter.c minishell/lexer/lexer_redi.c minishell/lexer/lexer_command.c \
		minishell/lexer/lexer_argument.c minishell/lexer/lexer_child.c minishell/lexer/lexer_initialize_utils.c\
		\
		minishell/parser/parser_wildcard.c minishell/parser/parser.c minishell/parser/parser_wildcard_utils.c \
		minishell/parser/parser_dir_utils.c minishell/parser/parser_expand_utils.c \
		minishell/parser/parser_expand.c minishell/parser/parser_wildcard_algo.c minishell/parser/parser_dir.c \
		minishell/parser/parser_ft_wildcard.c minishell/parser/parser_ft_expand.c \
		minishell/parser/parser_check_str.c minishell/parser/parser_cmd_arg.c \
		minishell/parser/parser_input_output.c minishell/parser/parser_get_paths.c \
		minishell/parser/parser_ft_put_in_quotes.c minishell/parser/parser_ft_take_off_quotes.c \
		minishell/parser/parser_open_files.c minishell/parser/parser_here_doc.c \
		minishell/parser/parser_pipe.c\
		\
		minishell/exec/exec.c minishell/exec/exec_redir.c minishell/exec/exec_wait.c minishell/exec/exec_launch_command.c\
		minishell/exec/exec_builtins.c minishell/exec/exec_launch_command_utils.c\
		minishell/builtins/builtins.c minishell/builtins/builtins_env.c \
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