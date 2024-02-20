NAME 				=	fdf

CC					=	clang
CFLAGS				=	-Wall -Wextra -Werror
SANITIZE			=	-g -fsanitize=address,undefined
RANDOM_MALLOC		=	-Xlinker --wrap=malloc
AR					=	ar rcs
RM					=	rm -rf

SRCS				=	color_control_utils.c color_utils.c color.c dda.c \
						draw_map.c draw_menu.c fdf_utils.c fdf.c fit_window.c \
						ft_ftoa.c ft_round.c ft_strhextol.c inits.c \
						key_press.c key_release.c limit_utils.c \
						map_control_utils.c map_keyboard_movement.c \
						map_mouse_movement.c matrix_operations.c \
						memory_handle.c menu_frame_info.c menu_utils.c menu.c \
						mouse_press.c mouse_release.c parser_utils.c parser.c \
						projections.c render_frame.c scale_utils.c \
						velocity_control_utils.c #malloc.c
SRCS_PATH			=	srcs/

MAIN				=	$(SRCS_PATH)fdf.c

OBJ_DIR				=	objects/
OBJS				=	$(SRCS:%.c=$(OBJ_DIR)%.o)
ALL_OBJS			=	$(OBJ_DIR)*.o

MLX_PATH			=	complete_lib/mlx_linux/
MLX					=	$(MLX_PATH)mlx_linux.a
LIBFT_PATH			=	complete_lib/libft/
LIBFT				=	$(LIBFT_PATH)libft.a
FT_PRINTF_PATH		=	complete_lib/ft_printf/
FT_PRINTF			=	$(FT_PRINTF_PATH)libprintf.a
GNL_PATH			=	complete_lib/get_next_line/
GNL					=	$(GNL_PATH)libgnl.a
PERSONAL_LIBS		=	-lft -lgnl -lftprintf
OTHER_LIBS			=	-lmlx -lXext -lX11 -lm -lz

$(OBJ_DIR)%.o:		$(SRCS_PATH)%.c
					@$(CC) $(CFLAGS) -c $< -o $@  && printf "## Compiled $<\r"

all:				$(NAME)

$(NAME):			$(OBJ_DIR) $(OBJS) $(MLX) $(LIBFT) $(GNL) $(FT_PRINTF)
					@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_PATH) -L$(GNL_PATH) -L$(FT_PRINTF_PATH) -L$(MLX_PATH) $(PERSONAL_LIBS) $(OTHER_LIBS) -o $(NAME)
					@echo "## Linking complete"

$(MLX):
					@make -s -C $(MLX_PATH) all

$(LIBFT):
					@make -s -C $(LIBFT_PATH) all

$(GNL):
					@make -s -C $(GNL_PATH) all

$(FT_PRINTF):
					@make -s -C $(FT_PRINTF_PATH) all

$(OBJ_DIR):
					@mkdir -p $(OBJ_DIR)

clean:
					@$(RM) $(OBJ_DIR)

fclean:				clean
					@$(RM) $(NAME)
					@$(RM) $(MLX)
					@$(RM) $(LIBFT)
					@$(RM) $(GNL)
					@$(RM) $(FT_PRINTF)
					@$(RM) $(OBJ_DIR)

re:					fclean all

.PHONY:				all bonus clean fclean re

#define progress_bar
#awk "BEGIN { printf \"Progress: [\"; for(i=0;i<$(1);i++) printf \"=\"; printf \">%3d%%\r\",$(1)*2; }"
#endef

progress-bar:
	@progress=0; \
		total_steps=$(shell echo $(words $(SRCS)) | bc); \
		for step in $(SRCS); do \
			$(MAKE) -s $(OBJ_DIR)$${step%.c}.o; \
			progress=$$(($$progress + 1)); \
			percent=$$(($$progress * 100 / $$total_steps)); \
			printf "\rBuilding objects... [%-50s] %d%%" "$$(printf '#%.0s' {1..$$(($$progress * 50 / $$total_steps))})" "$$percent"; \
		done; \
		printf "\n"