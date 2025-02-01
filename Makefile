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
UTILS_SRCS	=	$(wildcard $(UTILS_DIR)/*.c)
MAN_SRCS	=	$(SRCS_DIR)/check.c \
				$(SRCS_DIR)/free.c \
				$(SRCS_DIR)/init_arg.c \
				$(SRCS_DIR)/init_mutex.c \
				$(SRCS_DIR)/init_table.c \
				$(SRCS_DIR)/main.c \
				$(SRCS_DIR)/monitor.c \
				$(SRCS_DIR)/philo.c \
				$(SRCS_DIR)/simulation.c
SRCS		=	$(UTILS_SRCS) $(MAN_SRCS)

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
	printf "\r\033[K$(YELLOW)[%3d%%] Compiling: $<$(RESET)" $$CURRENT_PERCENT
endef

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #
all: $(NAME)

$(NAME): $(OBJS)
	@echo "\r\033[K$(BOLD)$(LIGHT_BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\r\033[K$(BOLD)$(LIGHT_BLUE)$(NAME) created successfully!$(RESET)"

# Compile rule for srcs/*.c -> objs/*.o
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(progress)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile rule for srcs/utils/*.c -> objs/utils/*.o
$(OBJS_DIR)/utils/%.o: $(UTILS_DIR)/%.c
	@$(progress)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


clean:
	@echo "\r\033[K$(BOLD)$(LIGHT_BLUE)Cleaning object files...$(RESET)"
	@$(RM) $(OBJS_DIR)
	@echo "\r\033[K$(BOLD)$(LIGHT_BLUE)Objects cleaned!$(RESET)"

fclean:
	@echo "\r\033[K$(BOLD)$(LIGHT_BLUE)Removing $(NAME)...$(RESET)"
	@$(RM) $(NAME) $(OBJS_DIR)
	@echo "\r\033[K$(BOLD)$(LIGHT_BLUE)Full clean complete!$(RESET)"

re: fclean all

run: $(NAME)
	@echo "\r\033[KRunning ./$(NAME) ..."
	@./$(NAME)

valgrind: $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

.PHONY: all clean fclean re run valgrind
