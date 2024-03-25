CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

HEADER = minitalk.h

SERVER = server
CLIENT = client

SV_SRCS = server.c
SV_OBJS = $(SV_SRCS:.c=.o)

CLIENT_SRCS = client.c utils.c
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus

SV_BONUS_SRCS = server_bonus.c server_utils_bonus.c
SV_BONUS_OBJS = $(SV_BONUS_SRCS:.c=.o)

CLIENT_BONUS_SRCS = client_bonus.c client_utils_bonus.c
CLIENT_BONUS_OBJS = $(CLIENT_BONUS_SRCS:.c=.o)

all: $(SERVER) $(CLIENT)

$(SERVER): $(SV_OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(SV_OBJS) -o server
$(CLIENT): $(CLIENT_OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) -o client
	
$(SERVER_BONUS): $(SV_BONUS_OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(SV_BONUS_OBJS) -o server_bonus
$(CLIENT_BONUS): $(CLIENT_BONUS_OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(CLIENT_BONUS_OBJS) -o client_bonus

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(SV_OBJS) $(CLIENT_OBJS)
	$(RM) $(SV_BONUS_OBJS) $(CLIENT_BONUS_OBJS) 
fclean: clean
	$(RM) $(SERVER) $(CLIENT)
	$(RM) $(SERVER_BONUS) $(CLIENT_BONUS)

re: fclean all

bonus: $(SERVER_BONUS) $(CLIENT_BONUS)

.PHONY: clean