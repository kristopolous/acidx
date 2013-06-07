acidx: acidx.o
install:
	make
	mv acidx /usr/local/bin
clean:
	rm -f *.o acidx core
