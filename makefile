acidx: acidx.o
install:
	make
	mv acidx /usr/local/bin
	@[ -f /usr/local/bin/acidxbright ] && rm /usr/local/bin/acidxbright 
	ln -s /usr/local/bin/acidx /usr/local/bin/acidxbright
clean:
	rm -f *.o acidx core
