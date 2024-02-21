NAME 				=	fdf

CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -I $(INCLUDES)
SANITIZE			=	-g -fsanitize=address,undefined
RANDOM_MALLOC		=	-Xlinker --wrap=malloc
AR					=	ar rcs
RM					=	rm -rf

SRCS				=	color_control_utils.c color_utils.c color.c dda.c \
						draw_map.c draw_menu.c exit_button.c fdf_utils.c \
						fdf.c fit_window.c ft_ftoa.c ft_round.c \
						ft_strhextol.c inits.c key_press.c key_release.c \
						limit_utils.c map_control_utils.c \
						map_keyboard_movement.c map_mouse_movement.c \
						matrix_operations.c memory_handle.c menu_frame_info.c \
						menu_utils.c menu.c mouse_press.c mouse_release.c \
						parser_utils.c parser.c projections.c render_frame.c \
						scale_utils.c velocity_control_utils.c #malloc.c
SRCS_PATH			=	srcs/

OBJ_DIR				=	objects/
OBJS				=	$(SRCS:%.c=$(OBJ_DIR)%.o)
ALL_OBJS			=	$(OBJ_DIR)*.o

INCLUDES			=	includes/

MLX_PATH			=	complete_lib/mlx_linux/
MLX					=	$(MLX_PATH)libmlx_Linux.a
LIBFT_PATH			=	complete_lib/libft/
LIBFT				=	$(LIBFT_PATH)libft.a
FT_PRINTF_PATH		=	complete_lib/ft_printf/
FT_PRINTF			=	$(FT_PRINTF_PATH)libftprintf.a
GNL_PATH			=	complete_lib/get_next_line/
GNL					=	$(GNL_PATH)libgnl.a
PERSONAL_LIBS		=	-lft -lgnl -lftprintf
OTHER_LIBS			=	-lmlx -lXext -lX11 -lm -lz

TOTAL_SRCS          =   $(words $(SRCS))
TOTAL_OBJS          =   $(words $(wildcard $(OBJ_DIR)*))
FILES				=	0

$(OBJ_DIR)%.o:		$(SRCS_PATH)%.c
					@$(CC) $(CFLAGS) -I /usr/local/include -c $< -o $@ && \
					$(eval FILES=$(shell echo $$(($(FILES) + 1)))) \
					$(call PRINT_PROGRESS,$(TOTAL_SRCS),$(GRN),$(YELLOW)Compiling$(DEFAULT) $@)

all:				$(NAME)

$(NAME):			$(OBJ_DIR) $(LIBFT) $(GNL) $(FT_PRINTF) $(MLX) $(OBJS)
					@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_PATH) -L$(GNL_PATH) -L$(FT_PRINTF_PATH) -L$(MLX_PATH) $(PERSONAL_LIBS) $(OTHER_LIBS) -o $(NAME)
					@echo "\033[2F\033[0K$(CYAN)$(NAME)$(DEFAULT) successfully created\033[E"

sanitize:			$(OBJ_DIR) $(LIBFT) $(GNL) $(FT_PRINTF) $(MLX) $(OBJS)
					@$(CC) $(CFLAGS) $(SANITIZE) $(OBJS) -L$(LIBFT_PATH) -L$(GNL_PATH) -L$(FT_PRINTF_PATH) -L$(MLX_PATH) $(PERSONAL_LIBS) $(OTHER_LIBS) -o $(NAME)
					@echo "\033[2F\033[0K$(CYAN)$(NAME)$(DEFAULT) successfully created\033[E"

random_m:			$(OBJ_DIR) $(LIBFT) $(GNL) $(FT_PRINTF) $(MLX) $(OBJS)
					@$(CC) $(CFLAGS) $(SANITIZE) $(RANDOM_MALLOC) $(OBJS) -L$(LIBFT_PATH) -L$(GNL_PATH) -L$(FT_PRINTF_PATH) -L$(MLX_PATH) $(PERSONAL_LIBS) $(OTHER_LIBS) -o $(NAME)
					@echo "\033[2F\033[0K$(CYAN)$(NAME)$(DEFAULT) successfully created\033[E"

$(MLX):
					@chmod 777 $(MLX_PATH)configure
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
					@$(foreach file,$(wildcard $(OBJ_DIR)*), \
						$(eval FILES=$(shell echo $$(($(FILES) + 1)))) \
						$(call PRINT_PROGRESS,$(TOTAL_OBJS),$(RED),$(YELLOW)Deleting$(DEFAULT) $(file)); \
						$(RM) $(file); \
					)
					@$(RM) $(OBJ_DIR)
					$(eval FILES=0)

fclean:				clean
					@$(RM) $(OBJ_DIR)
					@echo "$(PURPLE)$(OBJ_DIR)$(DEFAULT) deleted"
					@$(RM) $(LIBFT)
					@echo "$(PURPLE)$(LIBFT)$(DEFAULT) deleted"
					@$(RM) $(GNL)
					@echo "$(PURPLE)$(GNL)$(DEFAULT) deleted"
					@$(RM) $(FT_PRINTF)
					@echo "$(PURPLE)$(FT_PRINTF)$(DEFAULT) deleted"
					@$(RM) $(MLX)
					@echo "$(PURPLE)$(MLX)$(DEFAULT) deleted"
					@$(RM) $(NAME)
					@echo "$(PURPLE)$(NAME)$(DEFAULT) deleted"

re:					fclean all

.PHONY:				all bonus clean fclean re

define PRINT_PROGRESS
    if [ "$(FILES)" -eq "1" ]; then \
        printf "\033[0K$(3)\n["; \
    else \
        printf "\033[0K\033[1F\033[0K$(3)\n["; \
    fi
    @for i in `seq 1 $(shell expr $(FILES) \* 70 / $(1))`; do \
        printf "$(2)=\033[0m"; \
    done
    @for i in `seq 1 $(shell expr 70 - $(FILES) \* 70 / $(1))`; do \
        printf " "; \
    done
    @printf "] $(shell echo $$(($(FILES) * 100 / $(1))))%%"
	if [ "$(FILES)" -eq "$(1)" ]; then \
        printf "\n"; \
	fi
endef

CYAN				=	\033[36m
PURPLE				=	\033[35m
YELLOW				=	\033[33m
GRN					=	\033[32m
RED					=	\033[31m
DEFAULT				=	\033[0m