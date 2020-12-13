.DEFAULT_GOAL := default

CC?=gcc
CFLAGS?=-Wall
DEBUGFLAG=-g
SOURCES=main.c word_count.c
# comment the following out if you are providing your own sort_words
LIBRARIES=wc_sort.o
BINARIES=words

%: %.c
	$(CC) $(CFLAGS) $(LIBRARIES) -o $@ $^

clean:
	rm -f $(BINARIES)

executable:
	$(CC) $(CFLAGS) $(SOURCES) $(LIBRARIES) -o $(BINARIES)

debug:
	$(CC) $(DEBUGFLAG) $(SOURCES) $(LIBRARIES) -o $(BINARIES)



default: executable
