CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -fstack-protector-all -Werror -Wshadow -g

all: public01.x public02.x public03.x public04.x public05.x \
	public06.x public07.x public08.x public09.x public10.x 

public10.x: public10.o driver.o unix.o
	$(CC) public10.o driver.o unix.o -o public10.x

public09.x: public09.o driver.o unix.o
	$(CC) public09.o driver.o unix.o -g -o public09.x

public08.x: public08.o unix.o
	$(CC) public08.o unix.o -o public08.x

public07.x: public07.o unix.o
	$(CC) public07.o unix.o -o public07.x

public06.x: public06.o unix.o
	$(CC) public06.o unix.o -o public06.x

public05.x: public05.o memory-checking.o driver.o unix.o
	$(CC) public05.o memory-checking.o driver.o unix.o -o public05.x

public04.x: public04.o memory-checking.o unix.o
	$(CC) public04.o memory-checking.o unix.o -o public04.x

public03.x: public03.o memory-checking.o unix.o
	$(CC) public03.o memory-checking.o unix.o -o public03.x

public02.x: public02.o unix.o
	$(CC) public02.o unix.o -o public02.x

public01.x: public01.o driver.o unix.o
	$(CC) public01.o driver.o unix.o -o public01.x

public10.o: public10.c unix.h
	$(CC) $(CFLAGS) -c public10.c

public09.o: public09.c unix.h
	$(CC) $(CFLAGS) -c public09.c

public08.o: public08.c unix.h
	$(CC) $(CFLAGS) -c public08.c

public07.o: public07.c unix.h
	$(CC) $(CFLAGS) -c public07.c

public06.o: public06.c unix.h
	$(CC) $(CFLAGS) -c public06.c

public05.o: public05.c unix.h
	$(CC) $(CFLAGS) -c public05.c

public04.o: public04.c unix.h
	$(CC) $(CFLAGS) -c public04.c

public03.o: public03.c unix.h
	$(CC) $(CFLAGS) -c public03.c

public02.o: public02.c unix.h
	$(CC) $(CFLAGS) -c public02.c

public01.o: public01.c unix.h
	$(CC) $(CFLAGS) -c public01.c

unix.o: unix.c unix.h
	$(CC) $(CFLAGS) -c unix.c

clean:
	rm -f *.x  public*.o unix.o
