# Makefile pour la production des fichiers objets et de l'executable
#Les headers sont dans le dossier headers
#Les sources sont dans le dossier sources
#Les objets seront crées dans le dossier obj qui sera crée automatiquement si il n'existe pas
#L'executable sera crée dans le dossier bin qui sera crée automatiquement si il n'existe pas
#Pour compiler il suffit de taper make dans le terminal

# Variables
CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lm
EXEC = prog
SRC = $(wildcard sources/*.c)
OBJ = $(SRC:.c=.o)
OBJDIR = obj
OBJ := $(addprefix $(OBJDIR)/, $(notdir $(OBJ)))
HEADERS = $(wildcard headers/*.h)
BINDIR = bin

# Règles
all: $(EXEC)

$(EXEC): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CC) -o $(BINDIR)/$@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: sources/%.c $(HEADERS)
	@mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS)


# supprime les dossiers obj et bin
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# supprime les dossiers obj et bin et recompile
re: clean all

test: re
	./$(BINDIR)/$(EXEC) < hhhh | display
