CC = gcc -std=c99 -DLIST
CFlAGS= -c -Wall -Wextra

LDFLAGS = -I./libs/headers -I./binary_tree -I./libs

SRCS = binary_tree/binary_tree.h libs/KGetLine.c libs/MyString.c binary_tree/Tree.c binary_tree/Node.c binary_tree/key_and_info.c binary_tree/iterator.c binary_tree/file_input.c libs/FGetLine.c

OBJS = $(SRCS:.c=.o)

EXE = binary_tree.a

all: $(SRCS) $(EXE)

$(EXE): $(OBJS)
	ar -r $@ $(OBJS)
	#$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LIBS)
	# rm -rf $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $< -c $(LDFLAGS)

clean:
	rm -rf $(OBJS) $(EXE)
