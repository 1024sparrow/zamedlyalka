all:
	mkdir bin 2> /dev/null  && cp plot.plt bin/ || echo -n
	gcc main.c process.c -o bin/model -lm
clean:
	rm -r bin
