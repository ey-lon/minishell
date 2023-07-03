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
		cdm_err_check_1.c \
		cdm_err_check_2.c \
		env_clone.c \
		print_cmd_nodes.c \
		history.c \
		parsing_1.c \
		parsing_2.c \
		parsing_3.c \
		parsing_4.c \
		parsing_5.c \
		variables_1.c \
		variables_2.c \
		bi_echo.c \
		bi_env.c \
		bi_export.c \
		bi_unset.c \
		bi_exit.c \
		bi_pwd.c \
		bi_cd_1.c \
		bi_cd_2.c \
		exec_1_pipes.c \
		exec_2_redirection.c \
		exec_3_file_redir.c \
		exec_4_commands.c \
		exec_5_trypath.c \
		heredoc.c

#----------------------------------------------

LIBFT := $(addprefix $(LBT_F),$(LIBFT))

OBJ_S = $(SRC:.c=.o)
OBJ_S := $(addprefix $(OBJ_F),$(OBJ_S))

$(OBJ_F)%.o : $(SRC_F)%.c
	mkdir -p $(OBJ_F)
	$(CC) $(FLAGS) -c $< -o $@

#rules-----------------------------------------

all: $(NAME)

$(NAME): libcomp $(OBJ_S)
	$(CC) $(FLAGS) $(OBJ_S) $(LIBFT) $(FLAGS_2) -o $(NAME)
	echo "$(CYAN)make [$(NAME)]$(NOCOL)"

clean:	libclean
	$(RM) $(OBJ_S)
	$(RM) $(OBJ_F)
	echo "$(CYAN)make clean [$(NAME)]$(NOCOL)"

fclean:	clean libfclean
		$(RM) $(NAME)
		echo "$(CYAN)make fclean [$(NAME)]$(NOCOL)"

re: fclean all

bonus: $(NAME)

libcomp:
		@make -C $(LBT_F)

libclean:
		@make clean -C $(LBT_F)

libfclean:
		@make fclean -C $(LBT_F)

.PHONY: all $(NAME) re clean fclean bonus libcomp libclean libfclean

.SILENT:
