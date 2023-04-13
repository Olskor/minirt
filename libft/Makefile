NAME		= libft.a
INCLUDE		= ./
SRC_DIR		= src/
OBJ_DIR		= obj/
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I
RM			= rm -f
AR			= ar rcs

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SRC_FILES	=	ft_isalnum ft_isprint ft_memcmp  ft_putchar_fd ft_split \
				ft_strlcat ft_strncmp ft_substr ft_atoi ft_isalpha \
				ft_itoa ft_memcpy  ft_putendl_fd ft_strchr  ft_strlcpy \
				ft_strnstr ft_tolower ft_bzero   ft_isascii ft_memcpy \
				ft_memmove ft_putnbr_fd  ft_strdup  ft_strlen  ft_strrchr \
				ft_toupper ft_calloc  ft_isdigit ft_memchr  ft_memset  \
				ft_putstr_fd  ft_strjoin ft_strmapi ft_strtrim ft_striteri

BONUS_FILES =	ft_lstadd_back_bonus ft_lstadd_front_bonus ft_lstclear_bonus \
				ft_lstdelone_bonus ft_lstiter_bonus ft_lstlast_bonus \
				ft_lstmap_bonus ft_lstnew_bonus ft_lstsize_bonus

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
BONUS 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(BONUS_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
BONUS_OBJ 	= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(BONUS_FILES)))

OBJF		=	.cache_exists

all: 		$(NAME)

$(NAME):	$(OBJ)
			@$(AR) $(NAME) $(OBJ)
			@echo "$(GREEN)libft compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

bonus:		$(BONUS_OBJ)
			@$(AR) $(NAME) $(BONUS_OBJ)
			@echo "$(GREEN)libft bonus compiled!$(DEF_COLOR)"

clean:
			@$(RM) -rf $(OBJ_DIR)
			@echo "$(BLUE)libft object files cleaned!$(DEF_COLOR)"

fclean:		clean
			@$(RM) -f $(NAME)
			@echo "$(CYAN)libft executable files cleaned!$(DEF_COLOR)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for libft!$(DEF_COLOR)"

norm:
			@norminette $(SRC) $(INCLUDE) | grep -v Norme -B1 || true

.PHONY:		all clean fclean re norm
