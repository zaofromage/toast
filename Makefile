build:
	gcc -Wall -std=c99 ./src/*.c -lSDL2 -lSDL2_ttf -o toast

run:
	./toast -t bonjour -p topleft

clean:
	rm toast
