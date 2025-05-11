
TARGET = Smash_N_Kill


CC = gcc
CFLAGS = -Wall -g -Ilib

LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf


SRC = Smash_N_Kill.c lib/fonctions.c lib/special_attacks.c lib/buttons-coord.c

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ) $(TARGET)
