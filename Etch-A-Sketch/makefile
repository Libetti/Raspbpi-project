CC	= gcc
OBJ	= main.o
INCL	=
LIBPATH	= 
LDFLAGS	= $(LIBPATH) -lsense -lm
CFLAGS	= -g -ansi -pedantic -Wall
TARGET	= Etch-A-Sketch

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS) 

clean:
	rm -f $(OBJ) $(TARGET)
