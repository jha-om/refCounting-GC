ref: main.c ref.c ref.h
	gcc -std=c17 main.c ref.c -o ref -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror

clean:
	rm -f ref
