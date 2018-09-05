all:
	mkdir bin 2> /dev/null || echo -n
	cp plot.plt bin/
	gcc main.c process.c sinus_gen.c -o bin/model -lm
clean:
	rm -r bin
