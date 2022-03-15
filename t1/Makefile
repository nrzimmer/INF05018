zip:
	$(RM) -v q?.zip
	make -C Needleman-Wunsch/q1 format
	zip q1.zip Needleman-Wunsch/q1/src/main.c Needleman-Wunsch/src/nw.? Needleman-Wunsch/q1/*.md Needleman-Wunsch/q1/Makefile Needleman-Wunsch/q1/obj Needleman-Wunsch/q1/bin
	make -C Needleman-Wunsch/q2 format
	zip q2.zip Needleman-Wunsch/q2/src/main.c Needleman-Wunsch/src/nw.? Needleman-Wunsch/q2/*.md Needleman-Wunsch/q2/Makefile Needleman-Wunsch/q2/obj Needleman-Wunsch/q2/bin
	make -C q3 format
	cd q3 && zip ../q3.zip src/*.c src/*.h *.md Makefile obj bin
