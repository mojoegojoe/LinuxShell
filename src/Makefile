COMP= gcc
CFLAGS= -Wall
## -no-pie -nostdlib
OUT=mysh
OBJS=main.o init.o io.o parser.o

$(OUT): main.o init.o io.o parser.o 
	$(COMP) $(CFLAGS) -o $(OUT) $(OBJS)

main.o: main.c
	$(COMP) $(CFLAGS) -c main.c -o main.o

init.o: init.c
	$(COMP) $(CFLAGS) -c init.c -o init.o

parser.o: parser.c
	$(COMP) $(CFLAGS) -c parser.c -o parser.o

io.o: io.c
	$(COMP) $(CFLAGS) -c io.c -o io.o

.PHONY: clean
clean:
	rm -rf *.o $(OUT)