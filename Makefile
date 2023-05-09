# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 16:19:21 by dkhatri           #+#    #+#              #
#    Updated: 2023/05/09 16:19:40 by dkhatri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = ft_nm

MAIN = nm.c
MEM_FUNC = mem_func.c
PRINT_FUNC = ft_print_func.c ft_print_nbr.c
PARSE_HELPER = ft_parse_endian.c ft_parse_words.c ft_strcmp_nm.c
PARSER = ft_parse_elf_header.c ft_parse_section_header.c ft_parse_sym.c \
		 ft_process_sym_helper.c ft_process_sym.c ft_sort_syms.c
FILE_FUNC = ft_process_file.c

SRC = $(MAIN) $(MEM_FUNC) $(PRINT_FUNC) \
	  $(PARSER) $(PARSE_HELPER) $(FILE_FUNC)
OBJ = $(SRC:.c=.o)

INC = ft_nm.h
INCLUDES = -I include/

SRC_PATH = src/
INC_PATH = include/
OBJ_PATH = obj/

OBJS = $(addprefix $(OBJ_PATH), $(OBJ))
SRCS = $(addprefix $(SRC_PATH), $(SRC))
INCS = $(addprefix $(INC_PATH), $(INC))

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INCS)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(INCLUDES) $(CFLAGS) -o $@ -c $<
	@echo "\033[1m$(NAME)\033[0m \
		: Compiling $< to $@ \033[1;32m[OK]\033[0m"

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(INCLUDES) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[1m$(NAME)\033[0m \
		: Compiling $@ \033[1;32m[OK]\033[0m"

clean:
	@/bin/rm -f $(OBJS)
	@echo "\033[1m$(NAME)\033[0m \
		: Cleaned $(OBJ_PATH) \033[1;32m[OK]\033[0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -rf $(OBJ_PATH)
	@echo "\033[1m$(NAME)\033[0m \
		: binary deleted \033[1;32m[OK]\033[0m"

re: fclean all

.PHONY: all clean fclean re
