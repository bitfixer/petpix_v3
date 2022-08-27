
bin/petpix: src/petpix.h src/petpix.cpp src/timer.cpp
	g++ -o bin/petpix src/petpix.cpp src/timer.cpp -lwiringPi

bin/client.prg: src/pet_client/petpix_client.c
	cc65/bin/cl65 -t pet src/pet_client/petpix_client.c -o bin/client.prg

bin/petpix40.prg: src/pet_client/petpix_client_40.c
	cc65/bin/cl65 -t pet src/pet_client/petpix_client_40.c -o bin/petpix40.prg

bin/petpix80.prg: src/pet_client/petpix_client_80.c
	cc65/bin/cl65 -t pet src/pet_client/petpix_client_80.c -o bin/petpix80.prg

bin/cfast.prg: src/pet_client/petpix_client_fast.c
	cc65/bin/cl65 -t pet src/pet_client/petpix_client_fast.c -o bin/cfast.prg

bin/petscii_convert: src/petscii_convert/main.cpp src/petscii_convert/dct.cpp bf-shared/Image.cpp bf-shared/timer.cpp bf-shared/Ditherer.cpp
	g++ -o bin/petscii_convert -std=c++11 -Ibf-shared $^ -lpthread

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

PHONY: stream
stream: bin/petpix
	nc -l -k 9600 | bin/petpix -d 5

PHONY: stream80
stream80: bin/petpix
	nc -l -k 9600 | bin/petpix -d 5 -c 80