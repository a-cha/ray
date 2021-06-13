# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sadolph <sadolph@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/10 19:47:23 by sadolph           #+#    #+#              #
#    Updated: 2020/10/31 22:01:58 by sadolph          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compile
CC := gcc
CFLAGS := -Wall -Wextra -Werror
LINK_FLAGS := -lft -lmlx -O2 #-g -fsanitize=address

# Directories
SRC_DIR := ./src/
SRC_SUBDIRS := figures/ math/ parse/ process/
SRC_ALL_DIRS := $(addsuffix :, $(addprefix $(SRC_DIR), $(SRC_SUBDIRS)))
OBJ_DIR := ./obj/
INCS_DIR := ./includes/ ./libft/includes/ ./libft/src/gnl/ ./libft/src/libasm/includes/
LIB_DIRS := ./libft/ ./mlx/
LIBFT_DIR := ./libft/
MLX_DIR := ./mlx/
LINK_INC_DIRS := $(addprefix -I, $(INCS_DIR))
LINK_LIB_DIRS := $(addprefix -L, $(LIB_DIRS))

# Files
NAME := miniRT
PROJ_LIB := librt.a
SRCS :=				\
cylinder.c			\
plane.c				\
sphere.c			\
square.c			\
triangle.c			\
\
colour1.c			\
colour2.c			\
vectors1.c			\
vectors2.c			\
vectors3.c			\
\
parse.c				\
parse_camera.c		\
parse_cylinder.c	\
parse_light.c		\
parse_plane.c		\
parse_sphere.c		\
parse_square.c		\
parse_triangle.c	\
parse_utils.c		\
\
create_bmp.c		\
exit.c				\
hooks_actions.c		\
process_utils.c		\
ray_trace.c			\
\
minirt.c

OBJS := ${SRCS:.c=.o}
O_WITH_DIR := $(addprefix $(OBJ_DIR), $(OBJS))


all: make_libs $(NAME)

# Add printf's object files to the libftprintf.a
# Now, it's complete collection of all necessary functions into libftprintf.a
$(NAME): $(PROJ_LIB) #$(SRC_DIR)minirt.c
	$(CC) $(CFLAGS) -o $(NAME) $(LINK_LIB_DIRS) $(LINK_INC_DIRS) $(SRC_DIR)process/minirt.c $(PROJ_LIB) $(LINK_FLAGS)
	@echo "\033[32m$(NAME) successfully created\033[0m" ✅

# Make library from project's obj files
$(PROJ_LIB): $(O_WITH_DIR)
	ar rc $(PROJ_LIB) $^
	ranlib $(PROJ_LIB)

# This is all source's subdirectories
VPATH = $(SRC_ALL_DIRS)

# Dependencies that allow recompile obj files only from changed source files
$(OBJ_DIR)%.o: %.c ./includes/minirt.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(LINK_INC_DIRS) -c $< -o $@

# Building libft.a by lib's own Makefile.
make_libs:
	$(MAKE) -C $(MLX_DIR)
	#cp $(MLX_DIR)libmlx.dylib ./
	$(MAKE) -C $(LIBFT_DIR)

# Standard rules separated for miniRT & libft:
clean_here:
	rm -rf $(OBJ_DIR)
	rm -f $(PROJ_LIB)
fclean_here: clean_here
	rm -f $(NAME)
re_here: fclean_here all
clean_lib:
	$(MAKE) -C $(MLX_DIR)/ clean
	$(MAKE) -C $(LIBFT_DIR)/ clean
fclean_lib:
	$(MAKE) -C $(MLX_DIR)/ clean
	$(MAKE) -C $(LIBFT_DIR)/ fclean
re_lib:
	$(MAKE) -C $(MLX_DIR)/ re
	$(MAKE) -C $(LIBFT_DIR)/ re

# Standard rules for the whole project:
clean: clean_here clean_lib
fclean: fclean_here fclean_lib
re: re_lib re_here

.PHONY: all make_libft clean_here clean_lib clean fclean_here \
fclean_lib fclean re_here re_lib re bonus
