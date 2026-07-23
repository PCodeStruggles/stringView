main: ./bin/tests
	./bin/tests

./bin:
	mkdir -p ./bin

./bin/unity.o: ./bin ./unity/unity.c ./unity/unity.h
	gcc -Wall -Wextra -DUNITY_INCLUDE_DOUBLE -c ./unity/unity.c -o ./bin/unity.o

./bin/tests: ./bin/unity.o ./tests/tests.c ./sv.h
	gcc -Wall -Wextra -Wno-discarded-qualifiers -DUNITY_DOUBLE_PRECISION=1e-12 -g ./bin/unity.o ./tests/tests.c -o ./bin/tests

clean:
	rm ./bin/tests
