# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 16:20:40 by aschenk           #+#    #+#              #
#    Updated: 2024/11/18 17:14:11 by nholbroo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME :=			miniRT

SRCS_DIR :=		src
SRCS :=			$(SRCS_DIR)/main.c \
				$(SRCS_DIR)/parsing/check_file.c \
				$(SRCS_DIR)/parsing/parse_ambience.c \
				$(SRCS_DIR)/parsing/parse_camera.c \
				$(SRCS_DIR)/parsing/parse_light.c \
				$(SRCS_DIR)/parsing/errors.c \
				$(SRCS_DIR)/parsing/ft_atof.c \
				$(SRCS_DIR)/parsing/init.c \
				$(SRCS_DIR)/parsing/init_unique_elements.c \
				$(SRCS_DIR)/parsing/parsing.c \
				$(SRCS_DIR)/free/free_array.c \
				$(SRCS_DIR)/free/free_parsing.c \
				$(SRCS_DIR)/utils/array_length.c \
				$(SRCS_DIR)/utils/only_numbers.c \
				$(SRCS_DIR)/utils/ft_strchr_index.c

OBJS_DIR :=		obj
OBJS :=			$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

HDRS_DIR :=		include
HDRS := 		$(HDRS_DIR)/main.h

# LIBFT
LIBFT_DIR :=	lib/libft
LIBFT_FLAGS :=	-L$(LIBFT_DIR) -lft		# -L: path to library; -l: library name
LIBFT :=		$(LIBFT_DIR)/libft.a

# MiniLibX
MLX_DIR :=		lib/mlx
MLX_FLAGS :=	-L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm	# -L: path to library; -l: library name -lm: math library
LIBMLX :=		$(MLX_DIR)/libmlx.a

LIB_FLAGS :=	$(LIBFT_FLAGS) $(MLX_FLAGS)

CC :=			cc
CFLAGS :=		-Wall -Wextra -Werror
CFLAGS +=		-Wpedantic
CFLAGS +=		-I$(HDRS_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
CFLAGS +=		-g

# For compilation progress bar
TOTAL_SRCS :=	$(words $(SRCS))
SRC_NUM :=		0

# Colors and styles
RESET :=		\033[0m
BOLD :=			\033[1m
RED :=			\033[91m
GREEN :=		\033[32m
YELLOW :=		\033[33m

#############################
# 'ALL' RULE WITH DEPENCIES #
#############################

# Building dependencies MiniLibX, libft, and the program when 'make' is called.
all:	$(LIBMLX) $(LIBFT) $(NAME)

# Compiling MiniLibX. Clones from official repo if not present.
# Output of cloning / compiliation supressed via redirecting '>/dev/null 2>&1'.
$(LIBMLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning MiniLibX repository..."; \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR) >/dev/null 2>&1; \
	fi
	@echo "Compiling MiniLibX..."
	@make -s -C $(MLX_DIR) >/dev/null 2>&1;
	@echo "$(BOLD)MiniLibX compiled.$(RESET)"

# Build libft library by calling 'make' in LIBFT_DIR.
# This target will be executed if libft.a is missing or
# if any of the listed .c or .h files in LIBFT_DIR are modified.
# make -s: silent mode, -C: change directory
$(LIBFT):	$(LIBFT_DIR)/libft.h \
			$(LIBFT_DIR)/ft_isalpha.c \
			$(LIBFT_DIR)/ft_isdigit.c \
			$(LIBFT_DIR)/ft_isalnum.c \
			$(LIBFT_DIR)/ft_isascii.c \
			$(LIBFT_DIR)/ft_isprint.c \
			$(LIBFT_DIR)/ft_strlen.c \
			$(LIBFT_DIR)/ft_toupper.c \
			$(LIBFT_DIR)/ft_tolower.c \
			$(LIBFT_DIR)/ft_strncmp.c \
			$(LIBFT_DIR)/ft_strlcpy.c \
			$(LIBFT_DIR)/ft_strlcat.c \
			$(LIBFT_DIR)/ft_strchr.c \
			$(LIBFT_DIR)/ft_strrchr.c \
			$(LIBFT_DIR)/ft_strnstr.c \
			$(LIBFT_DIR)/ft_memset.c \
			$(LIBFT_DIR)/ft_memchr.c \
			$(LIBFT_DIR)/ft_memcpy.c \
			$(LIBFT_DIR)/ft_memcmp.c \
			$(LIBFT_DIR)/ft_memmove.c \
			$(LIBFT_DIR)/ft_bzero.c \
			$(LIBFT_DIR)/ft_atoi.c \
			$(LIBFT_DIR)/ft_strdup.c \
			$(LIBFT_DIR)/ft_calloc.c \
			$(LIBFT_DIR)/ft_substr.c \
			$(LIBFT_DIR)/ft_strjoin.c \
			$(LIBFT_DIR)/ft_strtrim.c \
			$(LIBFT_DIR)/ft_split.c \
			$(LIBFT_DIR)/ft_itoa.c \
			$(LIBFT_DIR)/ft_strmapi.c \
			$(LIBFT_DIR)/ft_striteri.c \
			$(LIBFT_DIR)/ft_putchar_fd.c \
			$(LIBFT_DIR)/ft_putstr_fd.c \
			$(LIBFT_DIR)/ft_putendl_fd.c \
			$(LIBFT_DIR)/ft_putnbr_fd.c \
			$(LIBFT_DIR)/ft_lstnew.c \
			$(LIBFT_DIR)/ft_lstadd_front.c \
			$(LIBFT_DIR)/ft_lstsize.c \
			$(LIBFT_DIR)/ft_lstlast.c \
			$(LIBFT_DIR)/ft_lstadd_back.c \
			$(LIBFT_DIR)/ft_lstdelone.c \
			$(LIBFT_DIR)/ft_lstclear.c \
			$(LIBFT_DIR)/ft_lstiter.c \
			$(LIBFT_DIR)/ft_lstmap.c \
			$(LIBFT_DIR)/ft_strcmp.c \
			$(LIBFT_DIR)/ft_isbinary.c \
			$(LIBFT_DIR)/get_next_line_bonus.c \
			$(LIBFT_DIR)/ft_printf_utils.c \
			$(LIBFT_DIR)/ft_printf.c \
			$(LIBFT_DIR)/ft_atoi_base.c
	@make -s -C $(LIBFT_DIR)
	@echo ""

# Compilation of program depends on $(OBJS) and library files.
$(NAME):	$(OBJS) $(LIBFT) $(LIBMLX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB_FLAGS) -o $(NAME)
	@echo "$(BOLD)$(YELLOW)\n$(NAME) successfully compiled.$(RESET)"

# Logo and usage message
	@echo -n "$(BOLD)$(GREEN)"

	@echo "       _      _ ___ _____ "
	@echo " _ __ (_)_ _ (_) _ \_   _|"
	@echo "| '  \| | ' \| |   / | | "
	@echo "|_|_|_|_|_||_|_|_|_\ |_|  "

	@echo "$(RESET)"

	@echo "by Natalie Holbrook & Alex Schenk @42Berlin, December 2024"
	@echo "\n$(BOLD)$(YELLOW)Usage: './$(NAME) <scene.rt>'$(RESET)"

############################
# COMPILATION PROGRESS BAR #
############################

# Rule to define how to generate object files (%.o) from corresponding
# source files (%.c). Each .o file depends on the associated .c file and the
# project header file.
# -c:		Generates o. files without linking.
# -o $@:	Output file name;  '$@' is replaced with target name (the o. file).
# -$<:		Represents the first prerequisite (the c. file).
$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c $(HDRS)
	@mkdir -p $(@D)
	@$(eval SRC_NUM := $(shell expr $(SRC_NUM) + 1))
	@$(eval PERCENT := $(shell printf "%.0f" $(shell echo "scale=4; $(SRC_NUM) / $(TOTAL_SRCS) * 100" | bc)))
	@printf "$(BOLD)\rCompiling $(NAME): ["
	@$(eval PROGRESS := $(shell expr $(PERCENT) / 5))
	@printf "$(GREEN)%0.s#$(RESET)$(BOLD)" $(shell seq 1 $(PROGRESS))
	@if [ $(PERCENT) -lt 100 ]; then printf "%0.s-" $(shell seq 1 $(shell expr 20 - $(PROGRESS))); fi
	@printf "] "
	@if [ $(PERCENT) -eq 100 ]; then printf "$(GREEN)"; fi
	@printf "%d/%d - " $(SRC_NUM) $(TOTAL_SRCS)
	@printf "%d%% $(RESET)" $(PERCENT)
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER_SIZE) -D FD_SIZE=$(FD_SIZE) -c $< -o $@

##########
# RULES #
#########

# Target to remove all generated files BUT the program executable and compiled libraries.
clean:
	@rm -rf $(OBJS_DIR)
	@make -s -C $(LIBFT_DIR) clean  >/dev/null 2>&1
	@rm -rf $(MLX_DIR)/obj
	@echo "$(BOLD)$(RED)Object files removed.$(RESET)"

# Target to remove all generated files and the program executable (NOT the compiled libraries).
fclean:	clean
	@rm -f $(NAME)
	@echo "$(BOLD)$(RED)$(NAME) removed.$(RESET)"

# Target to remove all generated files and the program executable (NOT the compiled libraries).
fclean_all:	fclean
	@make -s -C $(LIBFT_DIR) fclean  >/dev/null 2>&1
	@rm -rf $(MLX_DIR)
	@echo "$(BOLD)$(RED)Library files removed.$(RESET)"

# Target to remove all object files, the program executable,
# and then rebuild the program.
re:	fclean
	@echo ""
	@$(MAKE) -s all

# Target to remove all object files, the program executable, and the compiled libraries,
# and then rebuild the program.
re_all:	fclean_all
	@echo ""
	@$(MAKE) -s all

.PHONY:	all clean fclean re
