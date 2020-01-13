CC=gcc
FLAG=-Wall
AR=ar
fPIC=-fPIC
all:frequency   

frequency:TRIE.c
	$(CC) $(FLAG) TRIE.c -g -o frequency

.PHONY: clean all

clean:
	rm -f *.o *.a  frequency