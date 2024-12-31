CC = cc
FLAG = -Wall -Wextra -Werror
C_NAME = client
S_NAME = server
OBJ = server.o client.o

all: $(C_NAME) $(S_NAME)

$(C_NAME):
	$(CC) $(FLAG) $(C_NAME).c -o $(C_NAME)

$(S_NAME):
	$(CC) $(FLAG) $(S_NAME).c -o $(S_NAME)

bonus:
	$(CC) $(FLAG) $(C_NAME).c -o $(C_NAME)
	$(CC) $(FLAG) $(S_NAME).c -o $(S_NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf client server

re: fclean all

.PHONY: all clean fclean bonus
