# Nome del file eseguibile
TARGET = program

# Compilatore
CC = gcc

# File sorgenti
SRC = main1.c image.c filters.c hough.c

# File oggetto
OBJ = $(SRC:.c=.o)

# Regola principale (default)
all: $(TARGET)

# Regola per la compilazione dell'eseguibile
$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) -lm

# Regola per compilare i file .c in .o
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@
