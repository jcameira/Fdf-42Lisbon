NAME			=	libgnl.a

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
AR				=	ar rcs
RM				=	rm -rf

SRCS			=	get_next_line_bonus.c get_next_line_utils_bonus.c

OBJ_DIR			=	../../objects
OBJS			=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o:		%.c
					@$(CC) $(CFLAGS) -c $< -o $@

all:				$(NAME)

${NAME}:			$(OBJ_DIR) ${OBJS}
					@${AR} ${NAME} ${OBJS}

$(OBJ_DIR):
					@mkdir -p ${OBJ_DIR}

clean:
					@${RM} ${OBJS_DIR}

fclean:				clean
					@${RM} ${NAME}

re:					fclean all

.PHONY:				all bonus clean fclean re