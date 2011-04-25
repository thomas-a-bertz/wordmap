wordmap1: wordmap1.cpp
	g++ -ansi -pedantic -Wall -Werror -o $@ $?

wordmap0: wordmap0.cpp
	g++ -ansi -pedantic -Wall -Werror -o $@ $?


.PHONY: clean
clean:
	rm -rf wordmap0 wordmap1

