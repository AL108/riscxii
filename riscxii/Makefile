TARGET = vm_riskxvii

CC = gcc

CFLAGS     = -c -Wall -Wvla -Werror -O0 -g -std=c11 --coverage
ASAN_FLAGS = -fsanitize=address
LDFLAGS = -lgcov

SOURCE_DIR = source_files
OBJECT_DIR = object_files

# RUN_ARG=testing/test_programs/mi_and_src/basic_heap_test1/basic_heap_test1.mi
# RUN_ARG=/home/alien/Downloads/printing_h.mi
# RUN_ARG=/home/alien/Downloads/shift.mi
# RUN_ARG=/home/alien/Desktop/learn/uni/vm-riskxvii/testing/test_programs/mi_and_src/add/add.mi
RUN_ARG=/home/alien/Desktop/learn/uni/vm-riskxvii/testing/test_programs/hb3_request_too_big/hb3_request_too_big.mi
# RUN_ARG=/home/alien/Desktop/learn/uni/vm-riskxvii/testing/test_programs/mi_and_src/basic_heap_test1/basic_heap_test1.mi

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