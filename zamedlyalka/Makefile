all:
	compile src/pro
	gcc compiled/main.c src/sound.c src/wav.c src/dsp.c src/sinus_gen.c src/average.c -o ../bin/zamedlyalka -lasound -lm
clean:
	rm -rf *.tmp
