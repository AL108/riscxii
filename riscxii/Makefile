

TARGET = vm_riskxii

CC = gcc

CFLAGS     = -c -Wall -Wvla -Werror -O0 -g -std=c11 --coverage
ASAN_FLAGS = -fsanitize=address
LDFLAGS = -lgcov

SOURCE_DIR = source_files
OBJECT_DIR = object_files

RUN_ARG=testing/sample_programs/add_2_numbers/add_2_numbers.mi

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
	# rm -f object_files/*.gcno object_files/*.gcda ./*.gcov
	# @sh ./testing/build_test_programs.sh
	sh ./testing/run_tests.sh

clean:
	rm -f $(OBJECT_FILES) $(TARGET)
	rm -f object_files/*.gcno object_files/*.gcda ./*.gcov