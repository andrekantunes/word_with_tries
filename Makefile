# -*- MakeFile -*-

all: indexer

indexer: word_with_tries.c
	clang word_with_tries.c -o indexer

clean:
	rm indexer
