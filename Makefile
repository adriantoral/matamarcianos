SRC= $(wildcard *.c)
OBJFILES= $(SRC:.c=.o)
COMPILER= g++
PROGRAMNAME= asciiInvaders.exe
all: $(OBJFILES)
	$(COMPILER) -g $(OBJFILES) -o $(PROGRAMNAME)
%.o: %.c
	$(COMPILER) -g -c $< -o $@
clean:
	rm $(OBJFILES)

