CC = gcc 
FLAGS = -I. 
DEPS = framebuffer.h 
OBJ = main.c framebuffer.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ %< $(FLAGS) 
binclock: $(OBJ)
	$(CC) -o $@ $^ $(FLAGS)
