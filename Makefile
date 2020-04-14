CXX_SRC       := $(wildcard src/*.cpp)
RES           := $(wildcard res/*.rc)
OBJECTS       := $(subst .cpp,.o,$(CXX_SRC)) $(subst .rc,.o,$(RES))

# -I"your-directory" add include directory (files .h) (HEADERS)
INCLUDE_DIRS  := -Iinclude 

# -L"your-directory" add lib directory (files .a .dll) (LIBRARIES)
LIB_DIRS      := -Llib

# -l"filename without lib prefix and .a extension" add libraries to use (libfile.a / libfile.dll)
LIBS          := -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

pong: $(OBJECTS)
	g++ $^ -o $@ $(INCLUDE_DIRS) $(LIB_DIRS) $(LIBS) -W -Wall
%.o: %.cpp
	g++ -c $^ -o $@ $(INCLUDE_DIRS) -W -Wall

%.o: %.rc
	windres $^ -o $@

clean:
	del *.o *.exe /s