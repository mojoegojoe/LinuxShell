COMP= gcc
CFLAGS= -Wall
## -no-pie -nostdlib
OUT=out
OBJS=main.o io/readline.o

$(OUT): main.o readline.o
	$(COMP) $(CFLAGS) -o $(OUT) $(OBJS)
main.o: main.c
	$(COMP) $(CFLAGS) -c main.c -o main.o
readline.o: io/readline.c
	$(COMP) $(CFLAGS) -c io/readline.c -o io/readline.o

.PHONY: clean
clean:
	rm -rf *.o $(OUT)
