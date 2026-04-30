# Variables
NAME	=	push_swap
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f

SRC = push_swap.c \
	  push_swap_utils.c \
	  push_swap_stacks.c \
	  push_swap_sort_utils.c \
	  push_swap_sort_small.c \
	  push_swap_parse.c \
	  push_swap_movements_swap_push.c \
	  push_swap_movements_reverse.c \
	  push_swap_movements_push_rotate.c \
	  push_swap_greedy_utils.c \
	  push_swap_greedy_sort.c \

OBJ = $(SRC:.c=.o)
HEADERS = push_swap.h

LIBDIR = libft
LIB = $(LIBDIR)/libft.a

# Target principal
all: $(LIB) $(NAME)

# Regla para compilar ejecutable, enlazando la librería
$(NAME): $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBDIR) -lft -o $(NAME)

# Compilar cada .c a .o (si cambia el .h, también recompila)
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para compilar la librería externa usando su Makefile
$(LIB):
	$(MAKE) -C $(LIBDIR)

# Limpiar archivos objeto
clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(LIBDIR) clean

# Limpiar objetos y ejecutable
fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBDIR) fclean

# Recompilación completa
re: fclean all

.PHONY: all clean fclean re