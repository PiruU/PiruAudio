
# PiruAudio - Copyright (C) 2018 P. Bernardi
#
# See the LICENSE.txt file for license information.


CC   = g++
INC  = -I../../portaudio/include -I../Includes
LIB  = -L../../portaudio/lib/.libs
LDFLAGS = -lwinmm -lportaudio
OPT     = -O3

SRC  = $(wildcard ../Sources/*.cpp)
OBJS = $(SRC:.cpp=.o)

tests :
	make ../Tests/TestFuzz.exe
	make ../Tests/TestDelay.exe
	make ../Tests/TestVibrato.exe
	make ../Tests/TestMultipleEffects.exe

%.exe : %.o $(OBJS)
	$(CC) -o $@ $^ $(LIB) $(LDFLAGS) $(OPT)

%.o : %.cpp
	$(CC) $(INC) -o $@ -c $< $(LIB) $(LDFLAGS) $(OPT)
clean :
	rm -f *.exe *.o *~ *.swp
	rm -f ../Tests/*.exe ../Tests/*.o ../Tests/*~ ../Tests/*.swp
	rm -f ../Sources/*.exe ../Sources/*.o ../Sources/*~ ../Sources/*.swp
	rm -f ../Includes/*.exe ../Includes/*.o ../Includes/*~ ../Includes/*.swp

