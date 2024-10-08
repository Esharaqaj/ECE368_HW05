
# VARIABLES
CC=gcc
CFLAGS=-g -std=c11 -Wall -Wshadow -Wvla -Werror -pedantic
HW_NUMBER=05
HW_NAME=hw$(HW_NUMBER)
FILE_NAME=$(HW_NAME).c
HEADER_FILE=$(HW_NAME).h
TEXT_FILE=$(HW_NAME)_results.txt
INPUT_FILE=$(HW_NAME)_input.txt
SOURCE_FILES=$(FILE_NAME) 
EXECUTABLE=a4
EXECUTABLE_GCOV=$(EXECUTABLE)_gcov
ALL_EXECUTABLES=-o $(EXECUTABLE) $(SOURCE_FILES) $(CFLAGS)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

#RULES
$(EXECUTABLE): $(FILE_NAME) 
	$(CC) $(ALL_EXECUTABLES) 

# .PHONY TARGET
.PHONY:
test: $(EXECUTABLE)
	./$(EXECUTABLE)
test_to_file: $(EXECUTABLE)
	./$(EXECUTABLE)>$(TEXT_FILE)
input_test: $(EXECUTABLE)
	./$(EXECUTABLE) $(INPUT_FILE)
gdb: $(EXECUTABLE)
	gdb $(EXECUTABLE)
clean:
	rm -f $(TEXT_FILE) $(EXECUTABLE)
valgrind: $(EXECUTABLE)
	$(VAL) ./$(EXECUTABLE) $(INPUT_FILE)