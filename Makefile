# Compiler and flags
CC = gcc
CFLAGS = -Wall -O2
GXXFLAGS = -std=c++11 -Ibf-shared

SRC_DIR = src
BIN_DIR = bin

# PET GPIO sender programs
PET_SENDER_SRC = $(SRC_DIR)/pet_sender.c
PET_SENDER_BIN = $(BIN_DIR)/pet_sender

FRAME_SENDER_SRC = $(SRC_DIR)/frame_sender_udp.c
FRAME_SENDER_BIN = $(BIN_DIR)/frame_sender_udp

all: bin/petpix bin/petscii_timed_sender bin/petpixPlayer bin/convert_one_video bin/petscii_convert \
     $(PET_SENDER_BIN) $(FRAME_SENDER_BIN)

clean:
	rm -f $(BIN_DIR)/*

bin/petpix: src/petpix.h src/petpix.cpp src/timer.cpp
	g++ -o bin/petpix src/petpix.cpp src/timer.cpp -lwiringPi

bin/client.prg: src/pet_client/petpix_client.c
	cc65/bin/cl65 -t pet src/pet_client/petpix_client.c -o bin/client.prg

bin/petpix40.prg: src/pet_client/petpix_client_40.c
	cc65/bin/cl65 -t pet src/pet_client/petpix_client_40.c -o bin/petpix40.prg

bin/petpix80.prg: src/pet_client/petpix_client_80.c
	cc65/bin/cl65 -t pet src/pet_client/petpix_client_80.c -o bin/petpix80.prg

bin/ptest.prg: src/pet_client/ptest.c
	cc65/bin/cl65 -t pet src/pet_client/ptest.c -o bin/ptest.prg

bin/cfast.prg: src/pet_client/petpix_client_fast.c
	cc65/bin/cl65 -t pet src/pet_client/petpix_client_fast.c -o bin/cfast.prg

bin/petscii_convert: src/petscii_convert/main.cpp src/petscii_convert/dct.cpp bf-shared/Image.cpp bf-shared/timer.cpp bf-shared/Ditherer.cpp
	g++ -o bin/petscii_convert $(GXXFLAGS) $^ -lpthread

bin/udp_receiver: src/udp_receiver.cpp
	g++ -o bin/udp_receiver src/udp_receiver.cpp

bin/udp_sender: src/udp_sender.cpp
	g++ -o bin/udp_sender src/udp_sender.cpp

bin/petscii_timed_sender: src/petscii_timed_sender.cpp bf-shared/timer.cpp
	g++ -o bin/petscii_timed_sender -Ibf-shared $^

bin/convert_one_video: src/convert_one_video.cpp
	g++ -o bin/convert_one_video $^

bin/interleave: src/interleave.cpp
	g++ -o bin/interleave $^

bin/petpixPlayer: src/petpixPlayer.cpp bf-shared/timer.cpp
	g++ -o bin/petpixPlayer -Ibf-shared $^

$(PET_SENDER_BIN): $(PET_SENDER_SRC)
	$(CC) $(CFLAGS) -o $@ $^

$(FRAME_SENDER_BIN): $(FRAME_SENDER_SRC)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: stream stream80

stream: bin/petpix
	nc -l -k 9600 | bin/petpix -d 5

stream80: bin/petpix
	nc -l -k 9600 | bin/petpix -d 5 -c 80
