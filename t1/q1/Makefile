
CC=gcc
CFLAGS=-g -Wall
SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
HEADERS=$(wildcard $(SRC)/*.h)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BINDIR=bin
BIN=$(BINDIR)/main
ZIPNAME=q1.zip

all: $(BIN) 

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r -v $(OBJ)/* $(BINDIR)/* $(ZIPNAME)

cleanup:
	$(RM) -r -v $(SRC)/*.*~*~

zip:
	$(RM) $(ZIPNAME)
	zip $(ZIPNAME) $(OBJ) $(BINDIR) $(SRCS) $(HEADERS) Makefile *.md

run: $(BIN)
	./$(BIN)

debug: CFLAGS += -DDEBUG
debug: clean
debug: all

format:
	VERSION_CONTROL=numbered VERSION_WIDTH=2 indent $(SRCS) $(HEADERS)