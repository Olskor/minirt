NAME		= minirt
INCLUDE		= includes
LIBFT		= libft
LIB			= libs/
SRC_DIR		= src/
OBJ_DIR		= obj/
CC			= gcc
CFLAGS		= -g -I
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

WIDTH = 1920
HEIGHT = 1080

SRC_FILES	=	main position_handler get_next_line vector vector1 renderer input_handler value color
LIBS_FILES	=	libft libmlx

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
LIBS 		= 	$(addprefix $(LIB), $(addsuffix .a, $(LIBS_FILES)))


OBJF		=	.cache_exists

all:		whomadeit $(NAME)

$(NAME):	$(OBJ)
			@make -C $(LIBFT) --no-print-directory
			@cp libft/libft.a libs/libft.a
			@$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) $(LIBS) -lXext -lX11 -lm -lbsd -o $(NAME)
			@echo "$(GREEN)fdf Compiled successfully$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCLUDE) -D WIDTH=$(WIDTH) -D HEIGHT=$(HEIGHT) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

clean:
			@$(RM) -rf $(OBJ_DIR)
			@make clean -C $(LIBFT) --no-print-directory
			@echo "$(BLUE)ft_printf object files cleaned!$(DEF_COLOR)"

fclean:		clean
			@$(RM) -f $(NAME)
			@$(RM) -f $(LIBFT)/libft.a
			@echo "$(CYAN)minirt executable files cleaned!$(DEF_COLOR)"
			@echo "$(CYAN)libft executable files cleaned!$(DEF_COLOR)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for minirt!$(DEF_COLOR)"

norm:
			@norminette $(SRC) $(INCLUDE) $(LIBFT) | grep -v Norme -B1 || true

whomadeit:
			@echo "$(RED)this programm was made by jauffret if the evaluated person is not jauffret, he's a cheater$(DEF_COLOR)"

bonus:		all

.PHONY:		all clean fclean re norm
