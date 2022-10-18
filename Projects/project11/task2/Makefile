all: harness
CFLAGS=-g -O0 -w

harness: harness.c important.c
	$(CC) -o $@ $(CFLAGS) $^

clean:
	rm -f harness
