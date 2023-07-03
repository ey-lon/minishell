# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abettini <abettini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/07 14:36:43 by abettini          #+#    #+#              #
#    Updated: 2023/07/03 16:19:36 by abettini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#----------------------------------------------

NOCOL = \e[0m
GREEN = \e[1;92m
RED = \e[1;31m
CYAN = \e[1;36m
BLUE = \e[1;34m
YELL = \e[0;33m
TCOL = $(CYAN)
RMD = $(GREEN)successfully $(RED)removed$(NOCOL)
CMP = $(GREEN)successfully compiled$(NOCOL)
ALC = $(YELL)already compiled$(NOCOL)

#----------------------------------------------

CC = cc

RM = /bin/rm -f

CFLAG = -Wall -Werror -Wextra -g

NAME = libft.a

#paths-----------------------------------------

LP1F = libft_part_1/
LP2F = libft_part_2/
LP3F = libft_lists/
PTFF = ft_printf/
DPTFF = ft_dprintf/
GNLF = get_next_line/

#LIBFT-----------------------------------------

PT1 :=	ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_tolower.c \
	ft_toupper.c

PT2 :=	ft_itoa.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strmapi.c \
	ft_strtrim.c \
	ft_substr.c

BNS :=	ft_lstadd_back.c \
	ft_lstadd_front.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstlast.c \
	ft_lstmap.c \
	ft_lstnew.c \
	ft_lstsize.c

#FT_PRINTF------------------------------------

PTF :=	ft_printf.c \
	ft_ptf_chr.c \
	ft_ptf_str.c \
	ft_ptf_dec.c \
	ft_ptf_uns.c \
	ft_ptf_hex.c \
	ft_ptf_ptr.c \
	ft_ptf_unknown.c \
	ft_ptf_flags.c \
	ft_ptf_flags_set.c \
	ft_ptf_flags_utils.c \
	ft_ptf_utils.c

#FT_DPRINTF-----------------------------------

DPTF := ft_dprintf.c \
	ft_dptf_chr.c \
	ft_dptf_str.c \
	ft_dptf_dec.c \
	ft_dptf_uns.c \
	ft_dptf_hex.c \
	ft_dptf_ptr.c \
	ft_dptf_unknown.c \
	ft_dptf_flags.c \
	ft_dptf_flags_set.c \
	ft_dptf_flags_utils.c \
	ft_dptf_utils.c

#GET_NEXT_LINE---------------------------------

GNL :=	get_next_line.c


#add_folder_name-------------------------------

PT1 := $(addprefix $(LP1F),$(PT1))
PT2 := $(addprefix $(LP2F),$(PT2))
BNS := $(addprefix $(LP3F),$(BNS))
PTF := $(addprefix $(PTFF),$(PTF))
DPTF := $(addprefix $(DPTFF),$(DPTF))
GNL := $(addprefix $(GNLF),$(GNL))

#object_files----------------------------------

OBJ_S = $(PT1:.c=.o) \
	$(PT2:.c=.o) \
	$(BNS:.c=.o) \
	$(PTF:.c=.o) \
	$(DPTF:.c=.o) \
	$(GNL:.c=.o)

%.o:%.c
	$(CC) -c $(CFLAG) -I. $< -o $@

#rules-----------------------------------------

all: $(NAME)

$(NAME): $(OBJ_S)
	ar -rcs $@ $^
	echo "$(CYAN)make [$(NAME)]$(NOCOL)"

clean:
	$(RM) $(OBJ_S);\
	echo "$(CYAN)make clean [$(NAME)]$(NOCOL)"

fclean: clean
	$(RM) $(NAME)
	echo "$(CYAN)make fclean [$(NAME)]$(NOCOL)"

re: fclean all

#---------------------------------------------

.PHONY: $(NAME) all clean fclean re

.SILENT:
