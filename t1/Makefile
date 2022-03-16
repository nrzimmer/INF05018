CC=gcc
CFLAGS=-g -Wall
SRC=src
NW=$(SRC)/needleman-wunsch
SW=$(SRC)/smith-waterman
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
NWLIB=$(wildcard $(NW)/*.c)
NWLIB+=$(wildcard $(NW)/*.h)
SWLIB=$(wildcard $(SW)/*.c)
SWLIB+=$(wildcard $(SW)/*.h)
BINDIR=bin
Q1=$(BINDIR)/q1
Q2=$(BINDIR)/q2
Q3=$(BINDIR)/q3
ZIPFLAGS=-r -o -T -FS -9

all: $(BINDIR) $(Q1) $(Q2) $(Q3)

$(Q1): $(OBJ) $(OBJ)/nw.o $(OBJ)/q1.o
	$(CC) $(CFLAGS) $(OBJ)/nw.o $(OBJ)/q1.o -o $(Q1)

$(Q2): $(OBJ) $(OBJ)/nw.o $(OBJ)/q2.o
	$(CC) $(CFLAGS) $(OBJ)/nw.o $(OBJ)/q2.o -o $(Q2)

$(Q3): $(OBJ) $(OBJ)/sw.o $(OBJ)/q3.o
	$(CC) $(CFLAGS) $(OBJ)/sw.o $(OBJ)/q3.o -o $(Q3)

$(OBJ)/%.o: $(SW)/%.c $(SW)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/%.o: $(NW)/%.c $(NW)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR):
	mkdir $(BINDIR)

$(OBJ):
	mkdir $(OBJ)

clean:
	$(RM) -r -v $(OBJ)/* $(BINDIR)/* q?.zip

cleanup:
	$(RM) -r -v $(SRC)/*.*~*~

debug: CFLAGS += -DDEBUG
debug: clean
debug: all

format:
	VERSION_CONTROL=numbered VERSION_WIDTH=2 indent $(SRCS) $(NWLIB) $(SWLIB)

.SILENT: q1.zip q2.zip q3.zip

zip: q1.zip q2.zip q3.zip

q1.zip: Makefile.q1 Q1.md $(NWLIB) $(SRC)/q1.c
	mkdir -p zip/$(NW)
	cp Makefile.q1 zip/Makefile
	cp Q1.md zip
	cp $(NWLIB) zip/$(NW)
	cp $(SRC)/q1.c zip/$(SRC)
	cd zip; zip $(ZIPFLAGS) ../$@ *
	$(RM) -r zip

q2.zip: Makefile.q2 Q2.md $(NWLIB) $(SRC)/q2.c
	mkdir -p zip/$(NW)
	cp Makefile.q2 zip/Makefile
	cp Q2.md zip
	cp $(NWLIB) zip/$(NW)
	cp $(SRC)/q2.c zip/$(SRC)
	cd zip; zip $(ZIPFLAGS) ../$@ *
	$(RM) -r zip

q3.zip: Makefile.q3 Q3.md $(SWLIB) $(SRC)/q3.c
	mkdir -p zip/$(SW)
	cp Makefile.q3 zip/Makefile
	cp Q3.md zip
	cp $(SWLIB) zip/$(SW)
	cp $(SRC)/q3.c zip/$(SRC)
	cd zip; zip $(ZIPFLAGS) ../$@ *
	$(RM) -r zip
