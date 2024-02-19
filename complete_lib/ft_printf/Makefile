NAME			=	libftprintf.a

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
AR				=	ar rcs
RM				=	rm -rf

SRCS			=	flag_checks.c flag_utils.c print_char.c print_nbr.c \
				 	print_str.c ft_printf.c long_itoa.c print_hex.c xtoa.c \
 					print_unsigned.c utoa.c print_ptr.c long_xtoa.c

OBJ_DIR			=	../../objects
OBJS			=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBFT_PATH		=	../libft
LIBFT			=	$(LIBFT_PATH)/libft.a

$(OBJ_DIR)/%.o:		%.c
					@$(CC) $(CFLAGS) -c $< -o $@

all:				$(NAME)

$(NAME):			$(LIBFT) $(OBJ_DIR) $(OBJS)
					@cp	$(LIBFT) $(NAME)
					@$(AR) $(NAME) $(OBJS)

$(LIBFT):
					@make -C $(LIBFT_PATH) all

$(OBJ_DIR):
					@mkdir -p $(OBJ_DIR)

clean:
					@make -C $(LIBFT_PATH) clean
					@$(RM) $(OBJ_DIR)

fclean:				clean
					@make -C $(LIBFT_PATH) fclean
					@$(RM) $(NAME)

re:					fclean all

.PHONY:				all bonus clean fclean re