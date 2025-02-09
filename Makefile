# **************************************************************************** #
#                                  VARIABLES                                   #
# **************************************************************************** #

# Project
NAME        = philo

# Compiler and Flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -pthread -g

# Directories
MAKEFLAGS	+=	--no-print-directory

# srcs
SRCS_DIR	=	./srcs
UTILS_DIR	=	$(SRCS_DIR)/utils
INIT_DIR	=	$(SRCS_DIR)/init
SIM_DIR		=	$(SRCS_DIR)/simulation
UTILS_SRCS	=	$(wildcard $(UTILS_DIR)/*.c)
INIT_SRCS	=	$(wildcard $(INIT_DIR)/*.c)
SIM_SRCS	=	$(wildcard $(SIM_DIR)/*.c)
MAN_SRCS	=	$(SRCS_DIR)/free.c \
				$(SRCS_DIR)/main.c
SRCS		=	$(UTILS_SRCS) $(INIT_SRCS) $(SIM_SRCS) $(MAN_SRCS)

# object
OBJS_DIR	=	./objs
OBJS		=	$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Includes
INCLUDES    = -I ./includes

# Tools
RM          = rm -rf

# **************************************************************************** #
#                                   COLORS                                     #
# **************************************************************************** #
RESET       = \033[0m
BOLD        = \033[1m
LIGHT_BLUE  = \033[94m
YELLOW      = \033[93m

# **************************************************************************** #
#                                PROGRESS BAR                                  #
# **************************************************************************** #
# Simple progress approach: define a variable with total, increment on each .o.
TOTAL_FILES := $(words $(OBJS))
COMPILED    = 0

define progress
	@$(eval COMPILED=$(shell echo $$(expr $(COMPILED) + 1)))
	@CURRENT_PERCENT=$$(expr $(COMPILED) \* 100 / $(TOTAL_FILES)); \
	printf "\033[K$(YELLOW)[%3d%%] Compiling: $<$(RESET)\r" $$CURRENT_PERCENT
endef

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #
all: $(NAME)

$(NAME): $(OBJS)
	@printf "\033[K$(BOLD)$(LIGHT_BLUE)Compiling $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "\r\033[K$(BOLD)$(LIGHT_BLUE)$(NAME) created successfully!$(RESET)\n"

# Compile rule for srcs/*.c -> objs/*.o
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@$(progress)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile rule for srcs/utils/*.c -> objs/utils/*.o
$(OBJS_DIR)/utils/%.o: $(UTILS_DIR)/%.c
	@$(progress)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/init/%.o: $(INIT_DIR)/%.c
	@$(progress)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/simulation/%.o: $(SIM_DIR)/%.c
	@$(progress)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@printf "\033[K$(BOLD)$(LIGHT_BLUE)Cleaning object files...$(RESET)"
	@$(RM) $(OBJS_DIR)
	@printf "\r\033[K$(BOLD)$(LIGHT_BLUE)Objects cleaned!$(RESET)\n"

fclean:
	@printf "\033[K$(BOLD)$(LIGHT_BLUE)Removing $(NAME)...$(RESET)"
	@$(RM) $(NAME) $(OBJS_DIR)
	@printf "\r\033[K$(BOLD)$(LIGHT_BLUE)Full clean complete!$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re

run: $(NAME)
	./$(NAME) 5 800 200 200

valgrind: $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

.PHONY: run valgrind


