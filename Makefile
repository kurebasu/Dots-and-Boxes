#####################################
#Makefile							#
#author: Said Krebbers (s1381164)	#
#last edit date: March 22 2019		#
#####################################

INC_DIR = ./include
SRC_DIR = ./src
SOURCES = $(shell find $(SRC_DIR)/ -name 'main.cc')
OBJECTS = $(SOURCES:.c=.o)
TARGET  = programma
CC 		= g++


.PHONY: all clean
all:$(TARGET)
clean:
	rm -f $(TARGET)
rebuild: clean all

$(TARGET): $(OBJECTS)
	$(CC)  -o $@ $^
%.o: %.c
	$(CC) -o $@ -c $<
