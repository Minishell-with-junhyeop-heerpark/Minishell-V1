NAME = minishell

SRC_DIR = ./srcs
BONUS_DIR = ./src_bonus

SRC	= $(SRC_DIR)/cmd_list.c \
		$(SRC_DIR)/error.c \
		$(SRC_DIR)/main.c \
		$(SRC_DIR)/parse.c \
		$(SRC_DIR)/split_space.c \
		$(SRC_DIR)/utils.c \
		$(SRC_DIR)/get_fd.c \
		$(SRC_DIR)/get_fd2.c \
		$(SRC_DIR)/here_doc.c \
		$(SRC_DIR)/here_doc2.c \
		$(SRC_DIR)/exe_parsing.c \
		$(SRC_DIR)/pipe_control.c \
		$(SRC_DIR)/exe_utils.c \
		$(SRC_DIR)/processes_exe.c \
		$(SRC_DIR)/list_to_process.c \
		$(SRC_DIR)/list_to_process_utils1.c \
		$(SRC_DIR)/list_to_process_utils2.c \
		$(SRC_DIR)/list_to_process_utils3.c \
		$(SRC_DIR)/envpwdcd.c \
		$(SRC_DIR)/builtin.c \
		$(SRC_DIR)/list_control.c \
		$(SRC_DIR)/env_control.c \
		$(SRC_DIR)/file_exe.c \
		$(SRC_DIR)/ft_echo.c \
		$(SRC_DIR)/signal.c \
		$(SRC_DIR)/ft_exit.c \
		$(SRC_DIR)/add_token.c \
		$(SRC_DIR)/ft_export.c \
		$(SRC_DIR)/free.c \
		$(SRC_DIR)/utils2.c \
		$(SRC_DIR)/utils3.c \
		$(SRC_DIR)/signal2.c \
		$(SRC_DIR)/ft_export2.c \
		$(SRC_DIR)/ft_export3.c \
		$(SRC_DIR)/ft_cd.c \
		$(SRC_DIR)/wait_process.c \
		$(SRC_DIR)/redir_error.c

LIBDIR = ./libft/
LIBNAME = ft
LIB = $(LIBDIR)lib$(LIBNAME).a
INCDIRS = ./inc

OBJS = $(SRC:.c=.o)
OBJS_BONUS = $(SRC_BONUS:.c=.o)

CC = cc
MAKE = make
RM = rm -f
CFLAGS = -Wall -Wextra -Werror $(foreach D, $(INCDIRS), -I$(D))
ARFLAGS = rs

#READFLAGS = -lreadline -I/Users/junhyeop/.brew/opt/readline/include -L/Users/junhyeop/.brew/opt/readline/lib #jh cluster
#READFLAGS = -lreadline -I/opt/homebrew/opt/readline/include -L/opt/homebrew/opt/readline/lib #heerpark notebook
READFLAGS = -lreadline -I/Users/heerpark/.brew/opt/readline/include -L/Users/heerpark/.brew/opt/readline/lib #heerpark cluster


all: $(NAME)

%.o: %.c $(foreach D, $(INCDIRS), $(D)*.h)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(LIB) $(OBJS)
		$(CC) -o $(NAME) $(READFLAGS) $(OBJS) -L$(LIBDIR) -l$(LIBNAME)

$(LIB):
	$(MAKE) -C $(LIBDIR) all
	
clean:
	$(MAKE) -C $(LIBDIR) clean
	${RM} $(SRC_DIR)/*.o 

fclean: clean
	$(MAKE) -C $(LIBDIR) fclean
	${RM} $(NAME) 

re: fclean all

.PHONY: all clean fclean re bonus