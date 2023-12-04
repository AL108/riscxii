TARGET = vm_riskxvii

CC = gcc

CFLAGS     = -c -Wall -Wvla -Werror -O0 -g -std=c11 --coverage
ASAN_FLAGS = -fsanitize=address

SOURCE_DIR = source_files
OBJECT_DIR = object_files

RUN_ARG=./testing/test_programs/mi_and_src/basic_heap_test1/basic_heap_test1.mi

SOURCE_FILES = $(wildcard $(SOURCE_DIR)/*.c)
OBJECT_FILES = $(patsubst $(SOURCE_DIR)/%.c, $(OBJECT_DIR)/%.o, $(SOURCE_FILES))

all: $(TARGET)

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(ASAN_FLAGS) $(CFLAGS) $< -o $@

$(TARGET): $(OBJECT_FILES)
	$(CC) $(ASAN_FLAGS) -o $@ $^ $(LDFLAGS)

run: $(TARGET)
	@./$(TARGET) $(RUN_ARG)

test:
	sh ./testing/run_tests.sh

clean:
	rm -f $(OBJECT_FILES) $(TARGET)
	rm -f object_files/*.gcno object_files/*.gcda