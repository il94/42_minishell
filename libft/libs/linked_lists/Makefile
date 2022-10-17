#==============================================================================#
#                                   TARGETS                                    #
#==============================================================================#

NAME = lists.a

#==============================================================================#
#                                   COMMANDS                                   #
#==============================================================================#

CC = gcc
CFLAGS = -Wall -Wextra -Werror
DFLAGS = -MMD
AR = ar -rc
MKDIR = mkdir -p
RM = rm -f
MAKE_SILENT = make --no-print-directory

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

SRC = ft_lstnew_cmd.c ft_lstadd_back_cmd.c ft_lstclear_cmd.c \
		ft_lstnew_lex.c ft_lstadd_back_lex.c ft_lstclear_lex.c \
		ft_lstsplit_charset_lex.c ft_lstsize_lex.c ft_lstis_correct_lex.c \
		ft_lstprint_lex.c ft_lstdelone_lex.c ft_lstnew_fd.c ft_lstadd_back_fd.c\

SRC_UNUSED =  ft_lstadd_front.c  ft_lstlast.c \
			  ft_lstiter.c \
				ft_lstmap.c \

#==============================================================================#
#                                   HEADERS                                    #
#==============================================================================#

HEAD_NAME = $(HEADER_DIR)/linked_lists.h

#==============================================================================#
#                                   OBJECTS                                    #
#==============================================================================#

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

#==============================================================================#
#                                   MAKEFILE                                   #
#==============================================================================#

all : $(OBJ_DIR) $(NAME)

$(NAME) : $(OBJ)
	echo "$(YELLOW)Making Lists$(END)"
	$(AR) $(NAME) $^
	echo "$(GREEN)Done$(END)"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEAD_NAME)
	$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@

$(OBJ_DIR) :
	$(MKDIR) $(OBJ_DIR)

clean :
	echo "$(PURPLE)Cleaning Lists's objects...$(END)"
	$(RM)r $(OBJ_DIR)
	echo "$(GREEN)Done$(END)"

fclean : clean
	echo "$(PURPLE)Cleaning Lists...$(END)"
	$(RM) $(NAME)
	echo "$(GREEN)Done$(END)"

re : fclean
	$(MAKE_SILENT) all

.PHONY : all clean fclean re
.SILENT :
