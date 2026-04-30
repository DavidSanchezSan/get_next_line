NAME	=	libftprintf.a

CC		= 	cc

CFLAGS	=	-Wall -Wextra -Werror

SRC		=	ft_printf.c \
			put_char_nbr_digit.c \
			put_str_hex_ptr.c \

OBJ	= $(SRC:.c=.o)

# "All" as the default target to build the library:
all: $(NAME)

#Rules to create a static library:
$(NAME): $(OBJ) $(LIBFT)
	ar -rcs $(NAME) $(OBJ)

# ar rcs $@ $^ is a possible command to create the static library.
# r: Insert object files into the archive.
# c: Create the archive if it doesn’t already exist.
# s: Create an index for the library (optional, but helps with linking).
# $@ refers to the target (libft.a), and $^ refers to the list of object files ($(OBJ)).

#Compile .c into .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# $< This reffers the input file.
# $@ This reffers the output file.

#Clean the object files:
clean:
	$(RM) $(OBJ)

#Clean all the generated files:
fclean: clean
	$(RM) $(NAME) $(LIBFT)

#Clean all the generated files and then compile the project:
re: fclean all

#Default rule:
.PHONY: all clean fclean re
#We use PHONY to ensure that make ALWAYS execute the rules, even if there are files called clean, fclean or re...

#make to build the library (libft.a).
#clean to remove object files.
#fclean to remove object files and the library.
#re to clean and rebuild the entire project.