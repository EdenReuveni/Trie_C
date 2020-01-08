all:frequency frequency_r  

frequency:
	gcc -o frequency TRIE.C 
frequency_r:
	gcc -o frequency_r  TRIE1.c 

.PHONY: clean all

clean:
	rm -f *.o *.a  frequency_r frequency