SHARED_DIR := ../../bf-shared
NAME := petscii_convert

SOURCES := $(SHARED_DIR)/Image.cpp $(SHARED_DIR)/timer.cpp $(SHARED_DIR)/Ditherer.cpp dct.cpp
INCLUDES := -I$(SHARED_DIR)

#all:
#	g++ -o $(NAME) -std=c++11 $(SOURCES)

petscii_convert: main.cpp $(SOURCES)
	g++ -o $(NAME) -std=c++11 $(INCLUDES) $^ -lpthread

make_glyph_images: make_glyph_images.cpp $(SOURCES)
	g++ -o make_glyph_images -std=c++11 $(INCLUDES) $^ -lpthread