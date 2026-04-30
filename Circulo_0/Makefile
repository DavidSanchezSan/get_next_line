NAME	=	libft.a
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
SRC = ft_atoi.c \
	  ft_bzero.c \
	  ft_calloc.c \
	  ft_isalnum.c \
	  ft_isalpha.c \
	  ft_isascii.c \
	  ft_isdigit.c \
	  ft_isprint.c \
	  ft_itoa.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_memcpy.c \
	  ft_memmove.c \
	  ft_memset.c \
	  ft_putchar_fd.c \
	  ft_putendl_fd.c \
	  ft_putnbr_fd.c \
	  ft_putstr_fd.c \
	  ft_split.c \
	  ft_strchr.c \
	  ft_strdup.c \
	  ft_striteri.c \
	  ft_strjoin.c \
	  ft_strlcat.c \
	  ft_strlcpy.c \
	  ft_strlen.c \
	  ft_strmapi.c \
	  ft_strncmp.c \
	  ft_strnstr.c \
	  ft_strrchr.c \
	  ft_strtrim.c \
	  ft_substr.c \
	  ft_tolower.c \
	  ft_toupper.c \

SRC_BONUS = ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c \

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)


# "All" as the default target to build the library:
all: $(NAME)

#Rules to create a static library:
$(NAME): $(OBJ)
	ar -rcs $@ $^

bonus:  $(OBJ) $(OBJ_BONUS)
	ar -rcs $(NAME) $^

# ar rcs $@ $^ is the command to create the static library.
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
	$(RM) $(OBJ) $(OBJ_BONUS)

#Clean all the generated files:
fclean: clean
	$(RM) $(NAME)

#Clean all the generated files and then compile the project:
re: fclean all

#Default rule:
.PHONY: all clean fclean re bonus
#We use PHONY to ensure that make ALWAYS execute the rules, even if there are files called clean, fclean or re...

#The command to create the library will be make.
#The command to clean up the files created during the compilation is
#fclean.

#make to build the library (libft.a).
#clean to remove object files.
#fclean to remove object files and the library.
#re to clean and rebuild the entire project.