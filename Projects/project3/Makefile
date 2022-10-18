CC = gcc
0;136;0cCFLAGS = -ansi -pedantic-errors -Wall -fstack-protector-all -Werror -Wshadow

all: public01.x public02.x public03.x public04.x public05.x \
	public06.x public07.x public08.x public09.x public10.x

test6.x: test6.o list.o
	$(CC) test6.o list.o -o test6.x

test5.x: test5.o list.o
	$(CC) test5.o list.o -o test5.x

test4.x: test4.o list.o
	$(CC) test4.o list.o -o test4.x

test3.x: test3.o list.o
	$(CC) test3.o list.o -o test3.x

test2.x: test2.o list.o
	$(CC) test2.o list.o -o test2.x

test1.x: test1.o list.o
	$(CC) test1.o list.o -o test1.x

public10.x: public10.o list.o
	$(CC) public10.o list.o -o public10.x

public09.x: public09.o list.o
	$(CC) public09.o list.o -o public09.x

public08.x: public08.o list.o
	$(CC) public08.o list.o -o public08.x

public07.x: public07.o list.o
	$(CC) public07.o list.o -o public07.x

public06.x: public06.o list.o
	$(CC) public06.o list.o -o public06.x

public05.x: public05.o list.o
	$(CC) public05.o list.o -o public05.x

public04.x: public04.o list.o
	$(CC) public04.o list.o -o public04.x

public03.x: public03.o list.o
	$(CC) public03.o list.o -o public03.x

public02.x: public02.o list.o
	$(CC) public02.o list.o -o public02.x

public01.x: public01.o list.o
	$(CC) public01.o list.o -o public01.x

test6.o: test6.c list.h
	$(CC) $(CFLAGS) -c test6.c

test5.o: test5.c list.h
	$(CC) $(CFLAGS) -c test5.c

test4.o: test4.c list.h
	$(CC) $(CFLAGS) -c test4.c

test3.o: test3.c list.h
	$(CC) $(CFLAGS) -c test3.c

test2.o: test2.c list.h
	$(CC) $(CFLAGS) -c test2.c

test1.o: test1.c list.h
	$(CC) $(CFLAGS) -c test1.c

public10.o: public10.c list.h
	$(CC) $(CFLAGS) -c public10.c

public09.o: public09.c list.h
	$(CC) $(CFLAGS) -c public09.c

public08.o: public08.c list.h
	$(CC) $(CFLAGS) -c public08.c

public07.o: public07.c list.h
	$(CC) $(CFLAGS) -c public07.c

public06.o: public06.c list.h
	$(CC) $(CFLAGS) -c public06.c

public05.o: public05.c list.h
	$(CC) $(CFLAGS) -c public05.c

public04.o: public04.c list.h
	$(CC) $(CFLAGS) -c public04.c

public03.o: public03.c list.h
	$(CC) $(CFLAGS) -c public03.c

public02.o: public02.c list.h
	$(CC) $(CFLAGS) -c public02.c

public01.o: public01.c list.h
	$(CC) $(CFLAGS) -c public01.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

clean:
	rm -f *.x *.o
