CC = cc
CFLAGS = -Wextra -Werror -std=c17

SRC = $(wildcard src/*.c)
TEST_SRC = $(wildcard tests/*.c)

APP_SRC = $(SRC)
LIB_SRC = $(filter-out src/main.c,$(SRC))

APP_OBJ = $(APP_SRC:src/%.c=build/%.o)
LIB_OBJ = $(LIB_SRC:src/%.c=build/%.o)
TEST_OBJ = $(TEST_SRC:tests/%.c=build/tests/%.o)

APP = build/app
TEST = build/test

.PHONY: build test clean

build: $(APP)

test: $(TEST)
	./$(TEST)

$(APP): $(APP_OBJ)
	mkdir -p $(@D)
	$(CC) $(APP_OBJ) -o $@

$(TEST): $(LIB_OBJ) $(TEST_OBJ)
	mkdir -p $(@D)
	$(CC) $(LIB_OBJ) $(TEST_OBJ) -o $@

build/%.o: src/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

build/tests/%.o: tests/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -Iinclude -Itests -c $< -o $@

clean:
	rm -rf build