# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/19 16:36:23 by egarcia2          #+#    #+#              #
#    Updated: 2025/12/12 17:21:29 by dasanche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#program name
NAME = minishell

#compilation flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

#program directories
INCLUDE_DIR = include
LIBFT_DIR = libft
READLINE = -lreadline -lncurses
SRC_DIR = src
BUILTIN_DIR = src/builtin
ENV_DIR = src/enviroment
PARSER_DIR = src/parser
TOKENIZER_DIR = src/tokenizer
PIPES_DIR = src/pipes
SIGNALS_DIR = src/signals
REDIR_DIR = src/redirections

#source files
SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/shell_continuation.c \
	$(SRC_DIR)/shell_utils.c \
	$(REDIR_DIR)/redirections.c \
	$(REDIR_DIR)/redirections_utils.c \
	$(REDIR_DIR)/heredoc_redirections.c \
	$(ENV_DIR)/enviroment_variables_utils.c \
	$(ENV_DIR)/enviroment_variables.c \
	$(ENV_DIR)/enviroment_path_utils.c \
	$(ENV_DIR)/expansion_helpers.c \
	$(ENV_DIR)/expansion_process.c \
	$(TOKENIZER_DIR)/tokenizer_init.c \
	$(TOKENIZER_DIR)/tokenizer_utils.c \
	$(TOKENIZER_DIR)/tokenizer_advance.c \
	$(TOKENIZER_DIR)/tokenizer_add.c \
	$(TOKENIZER_DIR)/tokenizer_add_utils.c \
	$(PARSER_DIR)/command_free.c \
	$(PARSER_DIR)/command_init.c \
	$(PARSER_DIR)/command_utils.c \
	$(PARSER_DIR)/parser_helpers.c \
	$(PARSER_DIR)/parser.c \
	$(PARSER_DIR)/redirect_handlers.c \
	$(PARSER_DIR)/redirect_file_operations.c \
	$(BUILTIN_DIR)/builtin_utils.c \
	$(BUILTIN_DIR)/ft_cd.c \
	$(BUILTIN_DIR)/ft_echo.c \
	$(BUILTIN_DIR)/ft_env.c \
	$(BUILTIN_DIR)/ft_exit.c \
	$(BUILTIN_DIR)/ft_export.c \
	$(BUILTIN_DIR)/ft_pwd.c \
	$(BUILTIN_DIR)/ft_unset.c \
	$(SIGNALS_DIR)/signals_utils.c \
	$(SIGNALS_DIR)/signals.c \
	$(PIPES_DIR)/pipe_executor.c \
	$(PIPES_DIR)/pipe_helpers.c \
	$(PIPES_DIR)/pipe_builtin.c \
	$(PIPES_DIR)/pipe_external.c \
	$(PIPES_DIR)/pipe_process.c \
	$(PIPES_DIR)/pipe_utils.c \

#libt configuration
LIBFT = $(LIBFT_DIR)/libft.a

#includes
INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_DIR)

#object files
OBJS = $(SRCS:.c=.o)

#main rule
all: $(LIBFT) $(NAME)

#rule for libft compilation
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

#Rule for program compilation with libft.a
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)

#object compilation
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

#clean temporary objects
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	
#clean all
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

#recompile
re: fclean all

#phony targets
.PHONY: all clean fclean re
