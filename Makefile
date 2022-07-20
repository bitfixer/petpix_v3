
bin/petpix: src/petpix.h src/petpix.cpp src/timer.cpp
	g++ -o bin/petpix src/petpix.cpp src/timer.cpp -lwiringPi

bin/client.prg: src/pet_client/petpix_client.c
	cc65/bin/cl65 -t pet src/pet_client/petpix_client.c -o bin/client.prg

bin/cfast.prg: src/pet_client/petpix_client_fast.c
	cc65/bin/cl65 -t pet src/pet_client/petpix_client_fast.c -o bin/cfast.prg

bin/petscii_convert: src/petscii_convert/main.cpp src/petscii_convert/dct.cpp bf-shared/Image.cpp bf-shared/timer.cpp bf-shared/Ditherer.cpp
	g++ -o bin/petscii_convert -std=c++11 -Ibf-shared $^ -lpthread