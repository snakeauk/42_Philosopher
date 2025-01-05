NAME		=	philo

# commands
CC			=	cc
CFLAGS		=	-g# -Wall -Wextra -Werror
CFLAGS		+=	-pthread
RM			=	rm -rf
MAKEFLAGS	+=	--no-print-directory

# srcs
SRCS_DIR	=	./srcs
UTILS_DIR	=	$(SRCS_DIR)/utils

SRCS_COMMON	=	$(wildcard $(SRCS_DIR)/*.c)
BUILTIN_SRCS=	$(wildcard $(UTILS_DIR)/*.c)
SRCS		=	$(SRCS_COMMON) $(BUILTIN_SRCS)

# object
OBJS_DIR	=	./objs
OBJS		=	$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# includes
INCLUDES	=	-I ./includes -I $(LIBFT_DIR)/includes -I $(OS_DIR)/includes

# font color
RESET		=	\033[0m
BOLD		=	\033[1m
LIGHT_BLUE	=	\033[94m
YELLOW		=	\033[93m

# extra rule
TOTAL_FILES := $(words $(OBJS) $(SERVER_OBJS))
CURRENT_FILE := 0

# rule
define progress
	@CURRENT_PERCENT=$$(expr $(CURRENT_FILE) \* 100 / $(TOTAL_FILES)); \
	printf "$(YELLOW)Progress: %3d%% (%d/%d)$(RESET)\r" $$CURRENT_PERCENT $(CURRENT_FILE) $(TOTAL_FILES)
endef

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	@echo "$(BOLD)$(LIGHT_BLUE)Compiling $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(BOLD)$(LIGHT_BLUE)$(NAME) created successfully!$(RESET)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(progress)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/utils

clean:
	@echo "$(BOLD)$(LIGHT_BLUE)Cleaning objects...$(RESET)"
	@$(RM) $(OBJS) $(OBJS_DIR)
	@echo "$(BOLD)$(LIGHT_BLUE)Objects cleaned!$(RESET)"

fclean:
	@echo "$(BOLD)$(LIGHT_BLUE)Full clean...$(RESET)"
	@$(RM) $(OBJS) $(OBJS_DIR) $(NAME)
	@echo "$(BOLD)$(LIGHT_BLUE)Full clean complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
