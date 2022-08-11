LIBS  = -lm
CFLAGS = -Wall

OBJ = edb.o    \
      fila.o     \
      pilha.o    \
      tipos.o   \
      main.o

SRCS = $(OBJ:%.o=%.c)

main: $(SRCS)
	gcc -o $@  $(CFLAGS) $(LIBS) $(SRCS)