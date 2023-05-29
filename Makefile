#----------------------------------------------

NOCOL = \e[0m
GREEN = \e[1;92m
RED = \e[1;31m
CYAN = \e[1;36m
TCOL = $(CYAN)
RMD = $(GREEN)successfully $(RED)removed$(NOCOL)
CMP = $(GREEN)successfully compiled$(NOCOL)

#----------------------------------------------

CC = cc

RM = /bin/rm -f

FLAGS = -Wall -Werror -Wextra -g

FLAGS_2 = -lreadline

NAME = minishell

LIBFT = libft.a

#paths-----------------------------------------

LBT_F = Libft/
SRC_F = source/

#files-----------------------------------------

SRC =	main.c \
		history.c \
		parsing_1.c \
		parsing_2.c \
		parsing_3.c \
		parsing_4.c \
		utils.c \
		utils_2.c \
		cdm_err_check.c \
		print_cmd_nodes.c

#----------------------------------------------

LIBFT := $(addprefix $(LBT_F),$(LIBFT))
SRC := $(addprefix $(SRC_F),$(SRC))

OBJ_S = $(SRC:.c=.o)

#rules-----------------------------------------

all: $(NAME)

$(NAME): libcomp $(OBJ_S)
	$(CC) $(FLAGS) $(OBJ_S) $(LIBFT) $(FLAGS_2) -o $(NAME)
	echo "$(TCOL)$(NAME) $(CMP)"

clean:	libclean
	$(RM) $(OBJ_S)

fclean:	clean libfclean
		if [ -f $(NAME) ]; then\
			rm -rf $(NAME);\
			echo "$(TCOL)$(NAME) $(RMD)";\
		fi

re: fclean all

bonus:

libcomp:
		@make -C Libft

libclean:
		@make clean -C Libft

libfclean:
		@make fclean -C Libft

.PHONY: all $(NAME) re clean fclean bonus

.SILENT:
