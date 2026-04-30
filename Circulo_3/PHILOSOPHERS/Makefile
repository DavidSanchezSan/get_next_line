NAME = philo

# Compilador y flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

# Archivos fuente
SRCS = main.c\
	   utils_string.c\
	   utils_convert.c\
	   utils_time.c\
	   parsing.c\
	   parsing_utils.c\
	   print.c\
	   init.c\
	   cleanup.c\
	   philosophers.c\
	   philo_checks.c\
	   philo_actions.c\
	   threads.c\
	   monitor.c\

# Archivos objeto
OBJS = $(SRCS:.c=.o)

# Regla principal: compilar todo
all: $(NAME)

# Linkear ejecutable desde objetos
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compilar .c a .o
%.o: %.c philosophers.h
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos objeto
clean:
	$(RM) $(OBJS)

# Limpiar ejecutable y objetos
fclean: clean
	$(RM) $(NAME)

# Recompilar desde cero
re: fclean all
