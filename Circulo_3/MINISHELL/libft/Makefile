# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egarcia2 <egarcia2@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 15:32:55 by egarcia2          #+#    #+#              #
#    Updated: 2025/10/13 19:48:55 by egarcia2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Nombre de mi librería estática
NAME = libft.a
#compilador
CC = cc
#Flags de compilacion
CFLAGS = -Wall -Wextra -Werror
#Archivos fuente
SRCS = ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	./ft_printf/ft_printf.c \
	./ft_printf/ft_print_char.c \
	./ft_printf/ft_print_str.c \
	./ft_printf/ft_print_hex.c \
	./ft_printf/ft_print_nbr.c \
	./ft_printf/ft_print_ptr.c \
	./ft_printf/ft_print_unsigned_nbr.c
	
SRCS_BONUS = ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c

#Archivos objeto
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

#Regla principal
all: $(NAME)

#Construcción de la librería
$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

#Compilación de archivos fuente
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

#Regla para compilar el bonus y agegarlo a la librería
bonus: $(OBJS) $(OBJS_BONUS)
	ar -rcs $(NAME) $(OBJS) $(OBJS_BONUS)

#Limpiar los archivos temporales generados (.o)
clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

#Volver a compilar todo desde cero
re: fclean all

#Phony targets (especifica quee all y clean no son archivos sino nombres de reglas)
.PHONY: all clean fclean re