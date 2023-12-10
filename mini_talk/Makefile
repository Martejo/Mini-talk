SRCS_SERVER = srcs/serveur.c
SRCS_CLIENT = srcs/client.c
SRCS_CLIENT_BONUS = srcs/client_bonus.c
SRCS_SERVER_BONUS = srcs/serveur_bonus.c 

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER_B = $(SRCS_SERVER_BONUS:.c=.o)
OBJS_CLIENT_B = $(SRCS_CLIENT_BONUS:.c=.o)

NAME_SERVER = serveur
NAME_CLIENT = client
NAME_SERVER_BONUS = serveur_bonus
NAME_CLIENT_BONUS = client_bonus

# ... (autres variables)

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER)
	@$(CC) $(CFLAGS) -Iinclude -Ilibft $(OBJS_SERVER) -o $(NAME_SERVER) -Llibft -lft

$(NAME_CLIENT): $(OBJS_CLIENT)
	@$(CC) $(CFLAGS) -Iinclude -Ilibft $(OBJS_CLIENT) -o $(NAME_CLIENT) -Llibft -lft

%.o: %.c include/minitalk.h
	@$(CC) $(CFLAGS) -Iinclude -Ilibft -c $< -o $@

bonus: $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

$(NAME_SERVER_BONUS): $(OBJS_SERVER_B)
	@$(CC) $(CFLAGS) -Iinclude -Ilibft $(OBJS_SERVER_B) -o $(NAME_SERVER_BONUS) -Llibft -lft

$(NAME_CLIENT_BONUS): $(OBJS_CLIENT_B)
	@$(CC) $(CFLAGS) -Iinclude -Ilibft $(OBJS_CLIENT_B) -o $(NAME_CLIENT_BONUS) -Llibft -lft

# Règle 'clean' pour nettoyer les fichiers objets 

clean:
	@$(RM) $(OBJS_SERVER) $(OBJS_CLIENT)

fclean: clean
	@$(RM) $(NAME_SERVER) $(NAME_CLIENT)

re: fclean all
