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

RM = /bin/rm -rf

FLAGS = -Wall -Werror -Wextra -g

FLAGS_2 = -lreadline

NAME = minishell

LIBFT = libft.a

#paths-----------------------------------------

LBT_F = libft/
SRC_F = source/
OBJ_F = obj/

#files-----------------------------------------

SRC =	main.c \
		utils.c \
		utils_2.c \
		free_struct.c \
		cdm_err_check.c \
		env_clone.c \
		print_cmd_nodes.c \
		history.c \
		parsing_1.c \
		parsing_2.c \
		parsing_3.c \
		parsing_4.c \
		variables.c \
		bi_echo.c \
		bi_env.c \
		bi_export.c \
		bi_unset.c \
		bi_exit.c \
		bi_pwd.c \
		bi_cd_1.c \
		bi_cd_2.c \
		exec_1_pipes.c \
		exec_2_redirects.c \
		exec_3_commands.c

#----------------------------------------------

LIBFT := $(addprefix $(LBT_F),$(LIBFT))

OBJ_S = $(SRC:.c=.o)
OBJ_S := $(addprefix $(OBJ_F),$(OBJ_S))

$(OBJ_F)%.o : $(SRC_F)%.c
	$(CC) $(FLAGS) -c $< -o $@

#rules-----------------------------------------

all: $(NAME)

objects:
	mkdir $(OBJ_F)

$(NAME): libcomp objects $(OBJ_S)
	$(CC) $(FLAGS) $(OBJ_S) $(LIBFT) $(FLAGS_2) -o $(NAME)
	echo "$(TCOL)$(NAME) $(CMP)"

clean:	libclean
	$(RM) $(OBJ_S)
	$(RM) $(OBJ_F)

fclean:	clean libfclean
		if [ -f $(NAME) ]; then\
			$(RM) $(NAME);\
			echo "$(TCOL)$(NAME) $(RMD)";\
		fi

re: fclean all

bonus:

libcomp:
		@make -C $(LBT_F)

libclean:
		@make clean -C $(LBT_F)

libfclean:
		@make fclean -C $(LBT_F)

.PHONY: all $(NAME) re clean fclean bonus

.SILENT:
