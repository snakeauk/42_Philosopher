NAME		=	philo

# commands
CC			=	cc
CFLAGS		=	-g# -Wall -Wextra -Werror
RM			=	rm -rf
MAKEFLAGS	+=	--no-print-directory

# srcs
SRCS_DIR	=	./srcs
BUILTIN_DIR	=	$(SRCS_DIR)/builtin
LEXER_DIR	=	$(SRCS_DIR)/lexer

SRCS_COMMON	=	$(wildcard $(SRCS_DIR)/*.c)
BUILTIN_SRCS=	$(wildcard $(BUILTIN_DIR)/*.c)
LEXER_SRCS	=	$(wildcard $(LEXER_DIR)/*.c)
SRCS		=	$(SRCS_COMMON) $(BUILTIN_SRCS) $(LEXER_SRCS)

# object
OBJS	=	$(SRCS:.c=.o)

# includes
INCLUDES	=	-I ./includes -I $(LIBFT_DIR)/includes -I $(OS_DIR)/includes

# OS differences
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	OS_DIR		=	$(LIBFT_DIR)/mac
	INCLUDES	+=	-I/opt/homebrew/opt/readline/include
	LDFLAGS		+=	-L/opt/homebrew/opt/readline/lib -lreadline
else
	OS_DIR		=	$(LIBFT_DIR)/linux
endif


# font color
RESET		=	\033[0m
BOLD		=	\033[1m
LIGHT_BLUE	=	\033[94m
YELLOW		=	\033[93m

# extra rule
TOTAL_FILES := $(words $(OBJS) $(SERVER_OBJS))
CURRENT_FILE := 0

define progress
	@CURRENT_PERCENT=$$(expr $(CURRENT_FILE) \* 100 / $(TOTAL_FILES)); \
	printf "$(YELLOW)Progress: %3d%% (%d/%d)$(RESET)\r" $$CURRENT_PERCENT $(CURRENT_FILE) $(TOTAL_FILES); \
	$(eval CURRENT_FILE=$$(($(CURRENT_FILE)+1)))
endef

# rule
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(BOLD)$(LIGHT_BLUE)Compiling $(NAME)...$(RESET)"
	@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
	@echo "$(BOLD)$(LIGHT_BLUE)$(NAME) created successfully!$(RESET)"

%.o: %.c
	@$(eval CURRENT_FILE=$(shell expr $(CURRENT_FILE) + 1))
	@CURRENT_PERCENT=$$(expr $(CURRENT_FILE) \* 100 / $(TOTAL_FILES)); \
	printf "$(YELLOW)Progress: %3d%% (%d/%d)$(RESET)\r" $$CURRENT_PERCENT $(CURRENT_FILE) $(TOTAL_FILES); \
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(BOLD)$(LIGHT_BLUE)Cleaning objects...$(RESET)"
	@$(RM) $(OBJS)
	@echo "$(BOLD)$(LIGHT_BLUE)Objects cleaned!$(RESET)"

fclean:
	@echo "$(BOLD)$(LIGHT_BLUE)Full clean...$(RESET)"
	@$(RM) $(OBJS) $(NAME)
	@echo "$(BOLD)$(LIGHT_BLUE)Full clean complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
