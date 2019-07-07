CFLAGS=-O2 -Wall
OBJS=stamp.o

stamp: $(OBJS)
	$(CC) -o stamp $(OBJS)

.PHONY: clean
clean:
	rm -f stamp $(OBJS)
