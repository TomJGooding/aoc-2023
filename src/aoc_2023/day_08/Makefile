OBJECTS = solutions.o
CFLAGS = -g -Wall -Wextra -Werror -O3
LDLIBS =

.PHONY: solve
solve: main.o
	./main.o

.PHONY: test
test: test_solutions.o
	./test_solutions.o

.PHONY: clean
clean:
	rm solutions.o main.o test_solutions.o

main.o: main.c $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) main.c -o main.o $(LDLIBS)

test_solutions.o: test_solutions.c $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) test_solutions.c -o test_solutions.o $(LDLIBS)
