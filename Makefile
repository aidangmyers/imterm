
compile:
	gcc imterm.c -o executable-imterm -lncurses

run:
	make compile
	./executable-imterm

