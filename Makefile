CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -pedantic -g
LDFLAGS	=
LIBS	=	-lm -lcurses
TARGET	=	snake
SRCDIR	=	./src

all: $(TARGET)

$(TARGET): $(SRCDIR)/game.c
	$(CC) $(CFLAGS) $(LIBS) -o $(TARGET) $(SRCDIR)/game.c

clean:
	$(RM) $(TARGET)
