NAME 				=	fdf

CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -fsanitize=address
AR					=	ar rcs
RM					=	rm -rf

SRCS				=	fdf.c fdf_utils.c inits.c parser.c draw_map.c \
						matrix_operations.c prespectives.c key_controls.c \
						color.c memory_handle.c menu.c ftoa.c ft_strhextol.c
SRCS_PATH			=	srcs/

MAIN				=	$(SRCS_PATH)fdf.c

OBJ_DIR				=	objects/
OBJS				=	$(SRCS:%.c=$(OBJ_DIR)%.o)
ALL_OBJS			=	$(OBJ_DIR)*.o

MLX_PATH			=	complete_lib/mlx_linux/
MLX					=	$(MLX_PATH)mlx_linux.a
LIBFT_PATH			=	complete_lib/libft/
LIBFT				=	$(LIBFT_PATH)libft.a
GNL_PATH			=	complete_lib/get_next_line/
GNL					=	$(GNL_PATH)libgnl.a

$(OBJ_DIR)%.o:		$(SRCS_PATH)%.c
					@$(CC) $(CFLAGS) -c $< -o $@

all:				$(NAME)

$(NAME):			$(OBJ_DIR) $(OBJS) $(MLX) $(LIBFT) $(GNL)
					@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_PATH) -lft -L$(GNL_PATH) -lgnl -L$(MLX_PATH) -lmlx -lXext -lX11 -lm -lz -o $(NAME)

$(MLX):
					@make -s -C $(MLX_PATH) all

$(LIBFT):
					@make -s -C $(LIBFT_PATH) all

$(GNL):
					@make -s -C $(GNL_PATH) all

$(OBJ_DIR):
					@mkdir -p $(OBJ_DIR)

clean:
					@$(RM) $(OBJ_DIR)

fclean:				clean
					@$(RM) $(NAME)
					@$(RM) $(MLX)
					@$(RM) $(LIBFT)
					@$(RM) $(GNL)
					@$(RM) $(OBJ_DIR)

re:					fclean all

.PHONY:				all bonus clean fclean re