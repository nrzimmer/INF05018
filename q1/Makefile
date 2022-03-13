
CC=gcc
CFLAGS=-g -Wall
SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
HEADERS=$(wildcard $(SRC)/*.h)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BINDIR=bin
BIN=$(BINDIR)/q1
ZIPNAME=q1.zip

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ)/* $(BINDIR)/* $(ZIPNAME)

zip:
	$(RM) $(ZIPNAME)
	zip $(ZIPNAME) $(OBJ) $(BINDIR) $(SRCS) $(HEADERS) Makefile

run: $(BIN)
	./$(BIN)