CXX=g++

SDL_FRAMEWORK=-F. -framework SDL2
#SDL_FRAMEWORK=-framework SDL2
SDL_INCLUDE=-I./SDL2.framework/Versions/A/Headers

CFLAGS=-c $(SDL_INCLUDE)
LFLAGS=$(SDL_FRAMEWORK) -o

Els: main.o 
	$(CXX) $(LFLAGS) $@ $^

main.o: main.cpp
	$(CXX) $(CFLAGS) $^

clean:
	rm -rf *.o Els
