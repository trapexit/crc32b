all: crc32b

CFLAGS = -O2

DEPS = crc32b.h
OBJS = main.o crc32b.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

crc32b: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -vf $(OBJS) crc32b
