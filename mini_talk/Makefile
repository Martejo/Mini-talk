SRCS_SERVER = srcs/server.c
SRCS_CLIENT = srcs/client.c


OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)


NAME_SERVER = server
NAME_CLIENT = client


# ... (autres variables)

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER)
	@$(CC) $(CFLAGS) -Iinclude -Ilibft $(OBJS_SERVER) -o $(NAME_SERVER) -Llibft -lft

$(NAME_CLIENT): $(OBJS_CLIENT)
	@$(CC) $(CFLAGS) -Iinclude -Ilibft $(OBJS_CLIENT) -o $(NAME_CLIENT) -Llibft -lft

%.o: %.c include/minitalk.h
	@$(CC) $(CFLAGS) -Iinclude -Ilibft -c $< -o $@

# Règle 'clean' pour nettoyer les fichiers objets 

clean:
	@$(RM) $(OBJS_SERVER) $(OBJS_CLIENT)

fclean: clean
	@$(RM) $(NAME_SERVER) $(NAME_CLIENT)

re: fclean all

.PHONY: clean fclean re all
