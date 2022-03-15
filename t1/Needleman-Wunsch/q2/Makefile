
CC=gcc
CFLAGS=-g -Wall
SRC=src
LIBSRC=../src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
SRCS+=$(wildcard $(LIBSRC)/*.c)
HEADERS=$(wildcard $(SRC)/*.h)
HEADERS+=$(wildcard $(LIBSRC)/*.h)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BINDIR=bin
BIN=$(BINDIR)/main
ZIPNAME=q2.zip

all: $(BINDIR) $(BIN)

$(BINDIR):
	mkdir $(BINDIR)

$(OBJ):
	mkdir $(OBJ)

$(BIN): $(OBJ) $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/%.o: $(LIBSRC)/%.c $(LIBSRC)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/%.o: $(LIBSRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r -v $(OBJ)/* $(BINDIR)/* $(ZIPNAME)

cleanup:
	$(RM) -r -v $(SRC)/*.*~*~

zip:
	$(RM) $(ZIPNAME)
	zip $(ZIPNAME) $(OBJ) $(BINDIR) $(SRCS) $(HEADERS) Makefile *.md

run: all
	./$(BIN)

debug: CFLAGS += -DDEBUG
debug: clean
debug: all

format:
	VERSION_CONTROL=numbered VERSION_WIDTH=2 indent $(SRCS) $(HEADERS)