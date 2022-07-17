SHARED_DIR := ../../bf-shared
NAME := petscii_convert

SOURCES := $(SHARED_DIR)/Image.cpp $(SHARED_DIR)/timer.cpp dct.cpp
INCLUDES := -I$(SHARED_DIR)

#all:
#	g++ -o $(NAME) -std=c++11 $(SOURCES)

petscii_convert: main.cpp $(SOURCES)
	g++ -o $(NAME) -std=c++11 $(INCLUDES) $^ -lpthread