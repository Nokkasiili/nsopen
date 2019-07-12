CC = clang
CFLAGS = -Wall -lmagic -fPIE -pie


nsopen: main.c config.h
	$(CC) $(CFLAGS) -o nsopen main.c

debug:
	$(CC) -g $(CFLAGS) -o nsopen main.c

clean:
	rm nsopen
